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
	require_once($path_to_root . 'lib/functions_event.php');

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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Upload Robot Page',
		'PB_DESCRIPTION'	=> 'Upload a robot for an event on the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, event, race, competition, team, robot, upload',
		'ROOTPATH'			=> $path_to_root
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		$page->set_var(array(
			'PS_USERNAME'			=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'		=> $_SESSION['usergroup'],
			'PS_IPADSRESS'			=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'			=> $path_to_root . 'index.php',
			'PC_EVENTVIEWPAGE'		=> $path_to_root . 'events/event_view.php'
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

		$page->set_file('PAGE_CONTENT_T', 'event_submit_robot.ihtml');
		// Define the block template for a table row.
		$page->set_block("PAGE_CONTENT_T", "row", "rows");

		$sql = "SELECT t.teamid AS teamid, t.name AS name, r.robot_submission_start AS rs, " .
			   "r.robot_submission_end AS re, e.name AS eventname " .
			   "FROM $event_team_table et, $team_tablename t, $event_tablename e, " .
			   "$race_tablename r WHERE et.teamid=t.teamid AND e.eventid=$eventid_for_db AND " .
			   "et.eventid=e.eventid AND t.owner=" . quoteString(intval($_SESSION['uid'])) . " " .
			   "AND r.eventid=e.eventid AND r.raceid=$raceid_for_db";
		$result = mysql_query($sql);

		$results = 0;
		$toggle = intval(0);
		$page->set_var(array(
			'PC_RACE_ID'	=> $raceid,
			'PC_EVENT_ID'	=> $eventid,
			'PC_EVENT_NAME'	=> 'event'
		));
		while ($myrow = mysql_fetch_array($result)) {

			$teamid = intval($myrow['teamid']);
			$page->set_var(array(
				'PC_TEAM_ID'	=> $teamid,
				'PC_TEAM_NAME'	=> htmlentities($myrow['name']),
				'PC_EVENT_NAME'	=> $myrow['eventname'],
				'PC_COLOR'		=> ($toggle == 0) ? COLOR_TB1 : COLOR_TB2
			));

			$path = getcwd() . '/' . $path_to_root . 'robots/' . $eventid . '/' . $teamid . '.tar.bz2';
			if (file_exists($path)) {
				$mtime = date("Y-m-d H:i:s", filemtime($path));
				$size = filesize($path);
			} else {
				$mtime = 'error';
				$size = 'error';
			}

			$page->set_var(array(
				'PC_FILE_SIZE'	=> $size,
				'PC_FILE_MTIME'	=> $mtime
			));

			$page->parse("rows", "row", true);
			$toggle = ($toggle == 0) ? 1 : 0;
			$results++;
		}

		if ($results == 0) {
			$page->set_var("rows", "");
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
