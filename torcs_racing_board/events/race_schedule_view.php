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
	$race_tablename = $db_prefix . TBL_RACE;
	$track_tablename = $db_prefix . TBL_TRACK;

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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board View Schedule Page',
		'PB_DESCRIPTION'	=> 'View schedule for an event on the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, event, race, competition, view, schedule',
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

	if (isset($_GET['viewscheduleid'])) {
		$rulesid = intval(removeMagicQuotes($_GET['viewscheduleid']));

		$sql = "SELECT * FROM $event_tablename WHERE eventid=" . quoteString($rulesid);
		$eresult = mysql_query($sql);

		$sql = "SELECT t.name AS name, t.trackid AS trackid, r.robot_submission_start AS rbs, " .
			   "r.robot_submission_end AS rbe, r.result_submission_start AS res, " .
			   "r.result_submission_end AS ree " .
			   "FROM $race_tablename r, $track_tablename t WHERE r.trackid=t.trackid AND " .
			   "r.eventid=" . quoteString($rulesid) . " ORDER BY r.robot_submission_start ASC";
		$result = mysql_query($sql);

		if ($emyrow = mysql_fetch_array($eresult)) {
			$page->set_file('PAGE_CONTENT_T', 'race_schedule_view.ihtml');
			$page->set_block("PAGE_CONTENT_T", "row", "rows");
			$page->set_var(array(
				'PC_EVENT_NAME'		=> htmlentities($emyrow['name'])
			));

			$results = 0;
			$ct = time();
			while ($myrow = mysql_fetch_array($result)) {

				$time1 = strtotime($myrow['rbs']) - $ct;
				$time2 = strtotime($myrow['rbe']) - $ct;
				$time3 = strtotime($myrow['res']) - $ct;
				$time4 = strtotime($myrow['ree']) - $ct;

				$c0 = $c1 = $c2 = $c3 = COLOR_TB1;

				if ($time4 < 0) {
					//
				} elseif ($time3 < 0) {
					// Result submission.
					$c3 = '#e8a8a8';
				} elseif ($time2 < 0) {
					// Run the race.
					$c3 = $c2 = '#e8c8a8';
				} elseif ($time1 < 0) {
					// Robot submission.
					$c1 = $c2 = $c3 = '#e8e8a8';
				} else {
					// Race is in the future.
					$c0 = $c1 = $c2 = $c3 = '#a8e8a8';
				}

				$page->set_var(array(
					'PC_TRACK_ID'					=> $myrow['trackid'],
					'PC_TRACK_NAME'					=> $myrow['name'],
					'PC_RACE_ROBOT_SUBMIT_START'	=> htmlentities($myrow['rbs']),
					'PC_RACE_ROBOT_SUBMIT_END'		=> htmlentities($myrow['rbe']),
					'PC_RACE_RESULT_SUBMIT_START'	=> htmlentities($myrow['res']),
					'PC_RACE_RESULT_SUBMIT_END'		=> htmlentities($myrow['ree']),
					'PC_COLOR'						=> $c0,
					'PC_STATE_COLOR1'				=> $c1,
					'PC_STATE_COLOR2'				=> $c2,
					'PC_STATE_COLOR3'				=> $c3,
				));
				$page->parse("rows", "row", true);
				$results++;
			}

			if ($results == 0) {
				$page->set_var("rows", "");
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
