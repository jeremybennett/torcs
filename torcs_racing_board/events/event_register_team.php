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
	$event_car_table = $db_prefix . TBL_EVENT_CAR;
	$event_team_table = $db_prefix . TBL_EVENTTEAM;
	$team_tablename = $db_prefix . TBL_TEAM;

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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Register Team in Event Page',
		'PB_DESCRIPTION'	=> 'Register a team for an event on the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, event, race, competition, register, team',
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

	if (isset($_GET['eventid']) && isset($_GET['teamid']) && $_SESSION['usergroup'] == 'racer') {
		$eventid = intval(removeMagicQuotes($_GET['eventid']));
		$eventid_for_db = quoteString($eventid);
		$teamid = intval(removeMagicQuotes($_GET['teamid']));
		$teamid_for_db = quoteString($teamid);

		$sql = "SELECT t.name AS tname, e.name AS ename, t.modulename AS modulename FROM " .
			   "$event_car_table ec, $event_tablename e, $team_tablename t LEFT JOIN " .
			   "$event_team_table et ON (t.teamid=et.teamid AND et.eventid=$eventid_for_db) WHERE " .
			   "ec.eventid=$eventid_for_db AND ec.carid=t.carid AND t.owner=" . quoteString(intval($_SESSION['uid'])) . " " .
			   "AND (et.eventid!=$eventid_for_db OR isnull(et.eventid)) AND e.eventid=$eventid_for_db AND t.teamid=$teamid_for_db";
		$result = mysql_query($sql);

		if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
			$page->set_file('PAGE_CONTENT_T', 'event_register_team.ihtml');
			$page->set_var(array(
				'PC_EVENT_ID'				=> $eventid,
				'PC_EVENT_NAME'				=> htmlentities($myrow['ename']),
				'PC_TEAM_ID'				=> $teamid,
				'PC_TEAM_NAME'				=> htmlentities($myrow['tname']),
				'PC_TEAM_MODULE_NAME'		=> htmlentities($myrow['modulename']),
				'PC_ROBOTPACKAGE_SIZE'		=> ROBOT_MODULE_SIZE
			));
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
