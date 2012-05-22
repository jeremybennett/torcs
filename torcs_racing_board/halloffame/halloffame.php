<?php

/*
	copyright   : (C) 2012 Bernhard Wymann
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
	$forum_tablename = $db_prefix . TBL_FORUM;
	$topic_tablename = $db_prefix . TBL_FORUM_TOPICDATA;
	$stats_hitcount_tablename = $db_prefix . TBL_HITCOUNT;
	$stats_sessioncount_tablename = $db_prefix . TBL_SESSIONCOUNT;
	$stats_tablename = $db_prefix . TBL_STATS;
	$loginlog_tablename = $db_prefix . TBL_LOGIN_LOG;

	$event_tablename = $db_prefix . TBL_EVENT;
	$race_tablename = $db_prefix . TBL_RACE;
	$track_tablename = $db_prefix . TBL_TRACK;
	$driver_tablename = $db_prefix . TBL_DRIVER;
	$car_tablename = $db_prefix . TBL_CAR;
	$team_tablename = $db_prefix . TBL_TEAM;
	$event_team_table = $db_prefix . TBL_EVENTTEAM;
	$race_report_driver_table = $db_prefix . TBL_RACE_REPORT_DRIVER;
	$race_report_team_table = $db_prefix . TBL_RACE_REPORT_TEAM;
	$event_report_driver_table = $db_prefix . TBL_EVENT_REPORT_DRIVER;
	$event_report_team_table = $db_prefix . TBL_EVENT_REPORT_TEAM;

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
		'PAGE_CONTENT_T'	=> 'halloffame.ihtml',
		'PAGE_FOOTER_T'		=> 'page_footer.ihtml',
		'PAGE_END_T'		=> 'page_end.ihtml'
	));

	// Set up page header.
	$page->set_var(array(
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Hall of Fame',
		'PB_DESCRIPTION'	=> 'Hall of Fame of the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, Board, Car, List, Hall, Fame',
		'ROOTPATH'			=> $path_to_root,
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		$page->set_var(array(
			'PS_USERNAME'		=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'	=> $_SESSION['usergroup'],
			'PS_IPADSRESS'		=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'		=> $path_to_root . 'index.php'
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

	// Define the block template for a table row.
	$page->set_block("PAGE_CONTENT_T", "teamrow", "teamrows");
	$page->set_block("PAGE_CONTENT_T", "driverrow", "driverrows");

	$sql = "SELECT ee.eventid, ee.name, vv.max, tt.name AS tname, tt.teamid FROM $team_tablename AS tt, " .
		"$event_tablename AS ee JOIN (SELECT e.eventid, MAX(r.points) AS max FROM " .
		"$event_tablename AS e, $event_report_team_table AS r WHERE e.enddate < CURDATE() " .
		"AND e.pointsystem > 0 AND r.eventid=e.eventid GROUP BY e.eventid) AS vv " .
		"ON (vv.eventid = ee.eventid), $event_report_team_table AS rr WHERE rr.points=vv.max " .
		"AND rr.eventid=ee.eventid AND rr.teamid=tt.teamid ORDER BY ee.eventid DESC";
	$result = mysql_query($sql);

	$results = 0;
	while ($myrow = mysql_fetch_array($result)) {
		$page->set_var(array(
			'PC_EVENTID'	=> $myrow['eventid'],
			'PC_EVENTNAME'	=> htmlentities($myrow['name']),
			'PC_POINTS'		=> $myrow['max'],
			'PC_TEAMID'		=> $myrow['teamid'],
			'PC_TEAMNAME'	=> htmlentities($myrow['tname'])
		));
		$page->parse("teamrows", "teamrow", true);
		$results++;
	}

	if ($results == 0) {
		$page->set_var("teamrows", "");
	}


	$sql = "SELECT ee.eventid, ee.name, vv.max, tt.name AS tname, tt.teamid FROM $driver_tablename AS tt, " .
		"$event_tablename AS ee JOIN (SELECT e.eventid, MAX(r.points) AS max FROM " .
		"$event_tablename AS e, $event_report_driver_table AS r WHERE e.enddate < CURDATE() " .
		"AND e.pointsystem > 0 AND r.eventid=e.eventid GROUP BY e.eventid) AS vv " .
		"ON (vv.eventid = ee.eventid), $event_report_driver_table AS rr WHERE rr.points=vv.max " .
		"AND rr.eventid=ee.eventid AND rr.driverid=tt.driverid ORDER BY ee.eventid DESC";
	$result = mysql_query($sql);

	$results = 0;
	while ($myrow = mysql_fetch_array($result)) {
		$page->set_var(array(
			'PC_EVENTID'	=> $myrow['eventid'],
			'PC_EVENTNAME'	=> htmlentities($myrow['name']),
			'PC_POINTS'		=> $myrow['max'],
			'PC_TEAMID'		=> $myrow['teamid'],
			'PC_DRIVERNAME'	=> htmlentities($myrow['tname'])
		));
		$page->parse("driverrows", "driverrow", true);
		$results++;
	}

	if ($results == 0) {
		$page->set_var("driverrows", "");
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
