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
	require_once($path_to_root . 'lib/functions_points.php');
	require_once($path_to_root . 'lib/functions_reports.php');

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
	$driver_tablename = $db_prefix . TBL_DRIVER;
	$submitted_tablename = $db_prefix . TBL_RESULTSUBMITTED;
	$car_tablename = $db_prefix . TBL_CAR;
	$rawresult_tablename = $db_prefix . TBL_RAWRESULT;
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
		'PAGE_CONTENT_T'	=> 'admin_no_access.ihtml',
		'PAGE_FOOTER_T'		=> 'page_footer.ihtml',
		'PAGE_END_T'		=> 'page_end.ihtml'
	));

	// Set up page header.
	$page->set_var(array(
		'PB_PAGETITLE'		=> 'The TORCS Racing Board View Race Result Page',
		'PB_DESCRIPTION'	=> 'View race result on the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, event, race, competition, view, results, driver, team',
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

	if (isset($_GET['raceid'])) {
		$raceid = intval(removeMagicQuotes($_GET['raceid']));
		$raceid_for_db = quoteString($raceid);

		$sql = "SELECT e.name AS eventname, e.eventid AS eventid, t.name AS trackname, r.result_submission_end AS rse " .
			   "FROM $race_tablename r, $event_tablename e, $track_tablename t WHERE " .
			   "r.raceid=$raceid_for_db AND r.eventid=e.eventid AND r.trackid=t.trackid";
		$result = mysql_query($sql);

		if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
			// Check time.
			$ct = time();
			$time = strtotime($myrow['rse']) - $ct;
			if ($time < 0) {
				$eventid = $myrow['eventid'];
				// TODO: cron job
				updateReports(
					$raceid,
					$eventid,
					$driver_tablename,
					$team_tablename,
					$event_tablename,
					$event_team_table,
					$race_tablename,
					$submitted_tablename,
					$rawresult_tablename,
					$race_report_driver_table,
					$race_report_team_table,
					$event_report_driver_table,
					$event_report_team_table,
					$track_tablename
				);

				$d = getSubmissions($raceid, $submitted_tablename);
				if (enoughSubmissions($d)) {
					$page->set_file('PAGE_CONTENT_T', 'event_view_result.ihtml');
					$page->set_var(array(
						'PC_EVENT_NAME'		=> htmlentities($myrow['eventname']),
						'PC_TRACK_NAME'		=> htmlentities($myrow['trackname']),
						'PC_RACE_ID'		=> $raceid,
						'PC_EVENT_ID'		=> $eventid
					));

					$page->set_block('PAGE_CONTENT_T', 'driver', 'drivers');
					$sql = "SELECT d.name AS dname, t.teamid, t.name AS tname, rd.quali_laptime, rd.quali_rank, " .
						   "rd.race_laptime, rd.race_rank, rd.race_laps, rd.race_topspeed, rd.race_damage, " .
						   "rd.race_pitstops, rd.race_time, rd.points " .
						   "FROM $race_report_driver_table rd, $driver_tablename d, $team_tablename t " .
						   "WHERE rd.raceid=$raceid_for_db AND rd.driverid=d.driverid AND " .
						   "d.teamid=t.teamid ORDER BY rd.points DESC";
					$result = mysql_query($sql);

					$i = 1;
					$prevpoints = -1;
					$rank = 1;
					while ($myrow = mysql_fetch_array($result)) {
						if ($prevpoints == -1) {
							$prevpoints = $myrow['points'];
						} else if ($prevpoints != $myrow['points']) {
							$rank = $i;
							$prevpoints = $myrow['points'];
						}
						$page->set_var(array(
							'PC_RACE_DRIVER'		=> htmlentities($myrow['dname']),
							'PC_RACE_TEAM_ID'		=> $myrow['teamid'],
							'PC_RACE_LISTRANK'		=> $rank,
							'PC_RACE_POINTS'		=> $myrow['points'],
							'PC_RACE_RANK'			=> $myrow['race_rank'],
							'PC_RACE_LAPS'			=> $myrow['race_laps'],
							'PC_RACE_LAPTIME'		=> secondsToLaptime($myrow['race_laptime']),
							'PC_RACE_TOPSPEED'		=> speedToKMH($myrow['race_topspeed']),
							'PC_RACE_DAMAGE'		=> $myrow['race_damage'],
							'PC_RACE_PITSTOPS'		=> $myrow['race_pitstops'],
							'PC_RACE_TIME'			=> secondsToTime($myrow['race_time']),
							'PC_QUALI_LAPTIME'		=> secondsToLaptime($myrow['quali_laptime']),
							'PC_QUALI_RANK'			=> $myrow['quali_rank']
						));
						$page->parse('drivers', 'driver', true);
						$i++;
					}

					$page->set_block('PAGE_CONTENT_T', 'team', 'teams');
					$sql = "SELECT t.teamid, t.name AS tname, rt.points, u.username, u.id " .
						   "FROM $race_report_team_table rt, $team_tablename t, $user_tablename u " .
						   "WHERE rt.raceid=$raceid_for_db AND rt.teamid=t.teamid AND " .
						   "t.owner=u.id ORDER BY rt.points DESC";
					$result = mysql_query($sql);

					$i = 1;
					$prevpoints = -1;
					$rank = 1;
					while ($myrow = mysql_fetch_array($result)) {
						if ($prevpoints == -1) {
							$prevpoints = $myrow['points'];
						} else if ($prevpoints != $myrow['points']) {
							$rank = $i;
							$prevpoints = $myrow['points'];
						}
						$page->set_var(array(
							'PC_RACE_TEAM_NAME'		=> htmlentities($myrow['tname']),
							'PC_RACE_TEAM_ID'		=> $myrow['teamid'],
							'PC_RACE_LISTRANK'		=> $rank,
							'PC_RACE_POINTS'		=> $myrow['points']
						));
						$page->parse('teams', 'team', true);
						$i++;
					}
				} else {
					$page->set_file('PAGE_CONTENT_T', 'event_view_result_notok.ihtml');
					$page->set_var(array(
						'PC_EVENT_NAME'		=> htmlentities($myrow['eventname']),
						'PC_TRACK_NAME'		=> htmlentities($myrow['trackname']),
						'PC_RACE_ID'		=> $raceid,
						'PC_EVENT_ID'		=> $eventid
					));
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
