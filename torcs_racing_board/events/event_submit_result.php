<?php

/*
	copyright   : (C) 2004 Bernhard Wymann
	email       : berniw@bluewin.ch
	version     : $Id$

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
*/

	session_start();
	$path_to_root = '../';
	require_once($path_to_root . 'secrets/configuration.php');
	require_once($path_to_root . 'lib/functions.php');
	require_once($path_to_root . 'lib/classes.php');
	require_once($path_to_root . 'lib/template.inc');
	require_once($path_to_root . 'lib/functions_event_check.php');

	if (!isset($_SESSION['uid']) ) {
		session_defaults();
	}

	$db = mysql_connect($db_host, $db_user, $db_passwd) or die;
	mysql_select_db($db_name, $db) or die;
	$user_tablename = $db_prefix . TBL_USERS;
	$stats_hitcount_tablename = $db_prefix . TBL_HITCOUNT;
	$stats_sessioncount_tablename = $db_prefix . TBL_SESSIONCOUNT;
	$stats_tablename = $db_prefix . TBL_STATS;
	$loginlog_tablename = $db_prefix . TBL_LOGIN_LOG;

	$event_tablename = $db_prefix . TBL_EVENT;
	$event_team_table = $db_prefix . TBL_EVENTTEAM;
	$team_tablename = $db_prefix . TBL_TEAM;
	$race_tablename = $db_prefix . TBL_RACE;
	$track_tablename = $db_prefix . TBL_TRACK;
	$driver_tablename = $db_prefix . TBL_DRIVER;
	$submitted_tablename = $db_prefix . TBL_RESULTSUBMITTED;

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks the login.
	$user = new User($db, $user_tablename, $loginlog_tablename);

	// Login?
	checkLogin($user);
	// Logout?
	checkLogout();

	if ($_SESSION['logged'] == TRUE) {
		// Login template for statusbar.
		$page_statusbar = 'page_statusbar_logged_in.ihtml';
	} else {
		// Status view template for statusbar.
		$page_statusbar = 'page_statusbar.ihtml';
	}

	// Create template instance for page layout.
	$page = new Template($path_to_root . 'templates', 'keep');

	// Define template file(s).
	$page->set_file(array(
		'page'				=> 'page.ihtml',
		'PAGE_BEGIN_T'		=> 'page_begin.ihtml',
		'PAGE_TITLEBAR_T'	=> 'page_titlebar.ihtml',
		'PAGE_STATUSBAR_T'	=> $page_statusbar,
		'PAGE_NAVIGATION_T'	=> 'page_navigation.ihtml',
		'PAGE_CONTENT_T'	=> 'admin_no_access.ihtml',
		'PAGE_FOOTER_T'		=> 'page_footer.ihtml',
		'PAGE_END_T'		=> 'page_end.ihtml'
	));

	// Set up page header.
	$page->set_var(array(
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Racing and Result Submission Page',
		'PB_DESCRIPTION'	=> 'Run a race and submit the results for an event on the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, event, race, competition, run, result, submit',
		'ROOTPATH'			=> $path_to_root
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		$page->set_var(array(
			'PS_USERNAME'			=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'		=> $_SESSION['usergroup'],
			'PS_IPADSRESS'			=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'			=> $path_to_root . 'index.php',
			'PC_EDITEVENTPAGE'		=> $_SERVER['PHP_SELF']
		));
	} else {
		// Variables if NOT logged in.
		$page->set_var(array(
			'PS_PASSWORD_SIZE'	=> MAX_USERNAME_LENGTH,
			'PS_USERNAME_SIZE'	=> MAX_USERNAME_LENGTH,
			'PS_LOGINPAGE'		=> $_SERVER['PHP_SELF'],
			'PS_HOSTNAME'		=> SERVER_NAME
		));
	}

	if (isset($_GET['eventid']) && isset($_GET['raceid']) && $_SESSION['usergroup'] == 'racer') {
		$eventid = intval(removeMagicQuotes($_GET['eventid']));
		$eventid_for_db = quoteString($eventid);
		$raceid = intval(removeMagicQuotes($_GET['raceid']));
		$raceid_for_db = quoteString($raceid);
		$uid_for_db = quoteString(intval($_SESSION['uid']));

		// Check if the racer has a team in this event.
		// Check the time, are we in the submission phase of the race?
		// Check if already submitted.
		$trackid = 0;
		if (hasUserTeamOnEvent($event_team_table, $team_tablename, $eventid_for_db, $uid_for_db) &&
			isSubmissionPhase($race_tablename, $raceid_for_db, $eventid_for_db, $trackid) &&
			!hasUserSubmittedRaceresult($submitted_tablename, $raceid_for_db, $uid_for_db))
		{
			$trackid_for_db = quoteString($trackid);
			$page->set_file('PAGE_CONTENT_T', 'event_submit_result.ihtml');

			$sql = "SELECT * FROM $track_tablename WHERE trackid=$trackid_for_db";
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_TRACK_NAME'		=> htmlentities($myrow['name']),
					'PC_TRACK_ID'		=> $trackid,
					'PC_EVENT_ID'		=> $eventid,
					'PC_RACE_ID'		=> $raceid,
					'PC_RESULT_SIZE'	=> ROBOT_RESULT_SIZE
				));
			}

			// Get event name.
			$sql = "SELECT * FROM $event_tablename WHERE eventid=$eventid_for_db";
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_EVENT_NAME'		=> htmlentities($myrow['name'])
				));
			}

			// Create robot file list.
			$toggle = intval(0);
			$page->set_block("PAGE_CONTENT_T", "filelist", "filelistrows");
			$sql = "SELECT t.name AS name, t.teamid AS teamid, t.modulename AS modulename " .
				"FROM $event_team_table et, $team_tablename t WHERE " .
				"t.teamid=et.teamid AND et.eventid=$eventid_for_db ORDER BY t.name";
			$result = mysql_query($sql);
			while ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_TEAM_ID'			=> $myrow['teamid'],
					'PC_TEAM_NAME'			=> htmlentities($myrow['name']),
					'PC_TEAM_MODULENAME'	=> htmlentities($myrow['modulename']) . ".tar.bz2",
					'PC_RACE_STATE_COLOR'	=> ($toggle == 0) ? COLOR_TB1 : COLOR_TB2
				));
				$page->parse("filelistrows", "filelist", true);
				$toggle = ($toggle == 0) ? 1 : 0;
			}

			// Create start list.
			$toggle = intval(0);
			$page->set_block("PAGE_CONTENT_T", "driverlist", "driverlistrows");
			$sql = "SELECT d.name AS name FROM $driver_tablename d, $event_team_table et WHERE " .
				"d.teamid=et.teamid AND et.eventid=$eventid_for_db ORDER BY d.name";
			$result = mysql_query($sql);
			$number = 1;
			$toggle = intval(0);
			while ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_DRIVER_NO'		=> $number,
					'PC_DRIVER_NAME'	=> $myrow['name'],
					'PC_RACE_STATE_COLOR'	=> ($toggle == 0) ? COLOR_TB1 : COLOR_TB2
				));
				$page->parse("driverlistrows", "driverlist", true);
				$toggle = ($toggle == 0) ? 1 : 0;
				$number++;
			}
		}
	}

	require_once($path_to_root . 'lib/functions_navigation.php');
	setupNavigationAndFooter($page, $stats_tablename, $stats_hitcount_tablename);

	$page->parse('PAGE_BEGIN', 'PAGE_BEGIN_T');
	$page->parse('PAGE_TITLEBAR', 'PAGE_TITLEBAR_T');
	$page->parse('PAGE_STATUSBAR', 'PAGE_STATUSBAR_T');
	$page->parse('PAGE_NAVIGATION', 'PAGE_NAVIGATION_T');
	$page->parse('PAGE_CONTENT', 'PAGE_CONTENT_T');
	$page->parse('PAGE_FOOTER', 'PAGE_FOOTER_T');
	$page->parse('PAGE_END', 'PAGE_END_T');

	$page->parse('OUTPUT', array(
		'PAGE_BEGIN',
		'PAGE_TITLEBAR',
		'PAGE_NAVIGATION',
		'PAGE_STATUSBAR',
		'PAGE_CONTENT',
		'PAGE_FOOTER',
		'PAGE_END',
		'page'
	));

	$page->p('OUTPUT');
?>
