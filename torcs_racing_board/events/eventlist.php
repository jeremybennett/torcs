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
	$forum_tablename = $db_prefix . TBL_FORUM;
	$topic_tablename = $db_prefix . TBL_FORUM_TOPICDATA;
	$stats_hitcount_tablename = $db_prefix . TBL_HITCOUNT;
	$stats_sessioncount_tablename = $db_prefix . TBL_SESSIONCOUNT;
	$stats_tablename = $db_prefix . TBL_STATS;
	$loginlog_tablename = $db_prefix . TBL_LOGIN_LOG;

	$event_tablename = $db_prefix . TBL_EVENT;
	$event_car_table = $db_prefix . TBL_EVENT_CAR;
	$event_team_table = $db_prefix . TBL_EVENTTEAM;
	$race_tablename = $db_prefix . TBL_RACE;
	$submitted_tablename = $db_prefix . TBL_RESULTSUBMITTED;
	$race_report_driver_table = $db_prefix . TBL_RACE_REPORT_DRIVER;
	$race_report_team_table = $db_prefix . TBL_RACE_REPORT_TEAM;
	$rawresult_tablename = $db_prefix . TBL_RAWRESULT;
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

	$page_content = 'event_list.ihtml';

	if ($_SESSION['logged'] == TRUE) {
		// Login template for statusbar.
		$page_statusbar = 'page_statusbar_logged_in.ihtml';
		if ($_SESSION['usergroup'] == 'admin') {
			$page_content = 'admin_event_list.ihtml';
			deleteEvent(
				$event_tablename,
				$event_report_driver_table,
				$event_report_team_table,
				$event_car_table,
				$event_team_table,
				$race_tablename,
				$race_report_driver_table,
				$race_report_team_table,
				$rawresult_tablename,
				$submitted_tablename,
				$path_to_root
			);
		}
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
		'PAGE_CONTENT_T'	=> $page_content,
		'PAGE_FOOTER_T'		=> 'page_footer.ihtml',
		'PAGE_END_T'		=> 'page_end.ihtml'
	));

	// Set up page header.
	$page->set_var(array(
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Event (Competitions) List',
		'PB_DESCRIPTION'	=> 'Event (competition) list of the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, Board, Event, Competition, List',
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
	$page->set_block("PAGE_CONTENT_T", "row", "rows");

	// Query for the thread topics, set up variables, parse.
	if (isset($_GET['listfrom'])) {
		$listfrom = intval(removeMagicQuotes($_GET['listfrom']));
		$listfrom = ($listfrom < 0) ? 0 : $listfrom;
		$listfrom_for_db = $listfrom;
	} else {
		$listfrom = intval(0);
		$listfrom_for_db = $listfrom;
	}
	$listentries_for_db = quoteString(LISTENTRIES+1); // Select one more to check if there are more.

	$sql = "SELECT * FROM $event_tablename " .
		   "ORDER BY enddate DESC LIMIT $listfrom_for_db,$listentries_for_db";
	$result = mysql_query($sql);
	$more_rows = (mysql_num_rows($result) > LISTENTRIES);
	$page->set_var(array(
		'PC_LIST_NEXT_LINK'		=> ($more_rows === TRUE) ? $_SERVER['PHP_SELF'] . '?listfrom=' . ($listfrom+LISTENTRIES) : '',
		'PC_LIST_NEXT'			=> ($more_rows === TRUE) ? 'Forward' : '',
		'PC_LIST_PREV_LINK'		=> ($listfrom > 0) ? $_SERVER['PHP_SELF'] . '?listfrom=' . max($listfrom-LISTENTRIES, 0) : '',
		'PC_LIST_PREV'			=> ($listfrom > 0) ? 'Backward' : ''
	));


	$results = 0;
	$toggle = intval(0);
	while (($myrow = mysql_fetch_array($result)) && $results < LISTENTRIES) {
		$page->set_var(array(
			'PC_EVENT_ID'	=> $myrow['eventid'],
			'PC_NAME'		=> htmlentities($myrow['name']),
			'PC_COLOR'		=> ($toggle == 0) ? COLOR_TB1 : COLOR_TB2
		));
		$page->parse("rows", "row", true);
		$toggle = ($toggle == 0) ? 1 : 0;
		$results++;
	}

	if ($results == 0) {
		$page->set_var("rows", "");
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
