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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Result Submission Confirm Page',
		'PB_DESCRIPTION'	=> 'Could not run the race for an event on the TORCS racing board',
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

	// Coud not run the race.
	if (isset($_POST['no_race_result_submit']) && isset($_POST['event_id']) &&
		isset($_POST['race_id']) && $_SESSION['usergroup'] == 'racer')
	{
		$eventid = intval(removeMagicQuotes($_POST['event_id']));
		$eventid_for_db = quoteString($eventid);
		$raceid = intval(removeMagicQuotes($_POST['race_id']));
		$raceid_for_db = quoteString($raceid);
		$uid_for_db = quoteString(intval($_SESSION['uid']));

		// Check if the racer has a team in this event.
		$sql = "SELECT * FROM $event_team_table et, $team_tablename t WHERE " .
			   "t.teamid=et.teamid AND et.eventid=$eventid_for_db AND " .
			   "t.owner=$uid_for_db";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) > 0) {
			// The racer has a team, therefore permittet to upload results.
			// Check the time, are we in the submission phase of the race?
			// TODO: Make better semantics of times, perhaps remove racing phase.
			$sql = "SELECT r.robot_submission_end AS rose, r.result_submission_end AS rese, r.trackid AS trackid " .
				   "FROM $race_tablename r WHERE r.raceid=$raceid_for_db AND r.eventid=$eventid_for_db";
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				$ct = time();
				$time1 = strtotime($myrow['rose']) - $ct;
				$time2 = strtotime($myrow['rese']) - $ct;
				if ($time1 <= 0 && $time2 >= 0) {
					// Phase ok and the user has a team.
					// Check if already submitted.
					$sql = "SELECT * FROM $submitted_tablename s WHERE s.raceid=$raceid_for_db AND " .
						   "s.submitterid=$uid_for_db";
					$result = mysql_query($sql);
					if (mysql_num_rows($result) == 0) {
						if (isset($_POST['no_race_result'])) {
							$val = removeMagicQuotes($_POST['no_race_result']);
							if ($val == 'failed') {
								$page->set_file('PAGE_CONTENT_T', 'event_result_not_submitted_ok.ihtml');
								$sql = "INSERT INTO $submitted_tablename (raceid, submitterid, runrace) " .
									   "VALUES ($raceid_for_db, $uid_for_db, 'failed')";
								$result = mysql_query($sql);
							}
						} else {
							$page->set_file('PAGE_CONTENT_T', 'event_result_not_submitted.ihtml');
						}
					}
				}
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
