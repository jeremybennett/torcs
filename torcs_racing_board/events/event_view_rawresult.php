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
	$driver_tablename = $db_prefix . TBL_DRIVER;
	$submitted_tablename = $db_prefix . TBL_RESULTSUBMITTED;
	$car_tablename = $db_prefix . TBL_CAR;
	$rawresult_tablename = $db_prefix . TBL_RAWRESULT;
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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board View Result Submissions Page',
		'PB_DESCRIPTION'	=> 'View submitted results of a race on the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, event, race, competition, view, results',
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
				$page->set_file('PAGE_CONTENT_T', 'event_view_rawresult.ihtml');
				$page->set_var(array(
					'PC_EVENT_NAME'		=> htmlentities($myrow['eventname']),
					'PC_TRACK_NAME'		=> htmlentities($myrow['trackname']),
					'PC_EVENT_ID'		=> $myrow['eventid'],
					'PC_RACE_ID'		=> $raceid
				));

				$submit_ok = 0;
				$submit_not_ok = 0;
				$submitters = array();
				$submitters_id = array();
				$non_submitters = array();
				$non_submitters_id = array();

				// Get number of good and failed submissions.
				$sql = "SELECT s.runrace, s.submitterid, u.username FROM " .
					"$submitted_tablename s, $user_tablename u WHERE " .
					"raceid=$raceid_for_db AND u.id=s.submitterid ORDER BY u.username ASC";
				$result = mysql_query($sql);
				$i = 0;
				while ($myrow = mysql_fetch_array($result)) {
					if ($myrow['runrace'] == 'ok') {
						$submitters[$submit_ok] = $myrow['username'];
						$submitters_id[$submit_ok] = $myrow['submitterid'];
						$submit_ok++;
					} else if ($myrow['runrace'] == 'failed') {
						$non_submitters[$submit_not_ok] = $myrow['username'];
						$non_submitters_id[$submit_not_ok] = $myrow['submitterid'];
						$submit_not_ok++;
					}
					$i++;
				}

				$page->set_var(array(
					'PC_SUBMISSIONS_OK'			=> $submit_ok,
					'PC_SUBMISSIONS_NOT_OK'		=> $submit_not_ok
				));
				$page->set_block('PAGE_CONTENT_T', 'submittor', 'submittors');
				$sep = '';
				for ($i = 0; $i < $submit_ok; $i++) {
					$page->set_var(array(
						'PC_SEP'				=> $sep,
						'PC_SUBMITTOR_NAME'		=> $submitters[$i],
						'PC_SUBMITTOR_ID'		=> $submitters_id[$i]
					));
					$page->parse('submittors', 'submittor', true);
					$sep = ', ';
				}
				if ($i == 0) {
					$page->set_var("submittors", "None");
				}

				$page->set_block('PAGE_CONTENT_T', 'nonsubmittor', 'nonsubmittors');
				$sep = '';
				for ($i = 0; $i < $submit_not_ok; $i++) {
					$page->set_var(array(
						'PC_SEP'					=> $sep,
						'PC_NON_SUBMITTOR_NAME'		=> $non_submitters[$i],
						'PC_NON_SUBMITTOR_ID'		=> $non_submitters_id[$i]
					));
					$page->parse('nonsubmittors', 'nonsubmittor', true);
					$sep = ', ';
				}
				if ($i == 0) {
					$page->set_var("nonsubmittors", "None");
				}

				// TODO: number of allowed submitters and list of them.

				// Get all the raw data.
				$rows = array();
				$sql = "SELECT d.name, raw.driverid, u.username, raw.submitterid, raw.teamid, t.name AS tname, raw.carid, " .
					"raw.quali_laptime, raw.quali_rank, raw.race_laptime, raw.race_rank, raw.race_laps, " .
					"raw.race_topspeed, raw.race_damage, raw.race_pitstops, raw.race_time " .
					"FROM $rawresult_tablename raw, $driver_tablename d, $team_tablename t, " .
					"$user_tablename u WHERE " .
					"raw.teamid=t.teamid AND raw.driverid=d.driverid AND raw.raceid=$raceid_for_db " .
					"AND raw.submitterid=u.id ORDER BY raw.driverid ASC, u.username ASC";
				$result = mysql_query($sql);

				// Reorganize data, the "order by" in the above queries is important, do not remove it!
				$driverid = -1;
				$drivername = '';
				$teamid = -1;
				$teamname = '';
				$i = 0;
				$j = 0;

				// TODO: Improve the code, there must be a nicer solution.

				while ($myrow = mysql_fetch_array($result)) {
					if (($i % $submit_ok) == 0) {
						$driverid = $myrow['driverid'];
						$drivername = htmlentities($myrow['name']);
						$teamid = $myrow['teamid'];
						$teamname = htmlentities($myrow['tname']);
					}

					while ($submitters[$j] != $myrow['username'] || ($myrow['driverid'] != $driverid)) {
						// Insert empty row (case if user excluded this/those driver/s from the race).
						$rows[$i]['name'] = $drivername;
						$rows[$i]['driverid'] = $driverid;
						$rows[$i]['teamid'] = $teamid;
						$rows[$i]['tname'] = $teamname;

						$rows[$i]['submitterid'] = htmlentities($submitters_id[$j]);
						$rows[$i]['username'] = htmlentities($submitters[$j]);
						$rows[$i]['quali_laptime'] = '-';
						$rows[$i]['quali_rank'] = '-';
						$rows[$i]['race_laptime'] = '-';
						$rows[$i]['race_rank'] = '-';
						$rows[$i]['race_laps'] = '-';
						$rows[$i]['race_topspeed'] = '-';
						$rows[$i]['race_damage'] = '-';
						$rows[$i]['race_pitstops'] = '-';
						$rows[$i]['race_time'] = '-';
						$j = ($j + 1) % $submit_ok;
						$i++;
						if (($i % $submit_ok) == 0) {
							$driverid = $myrow['driverid'];
							$drivername = htmlentities($myrow['name']);
							$teamid = $myrow['teamid'];
							$teamname = htmlentities($myrow['tname']);
						}
					}

					$rows[$i]['name'] = $drivername;
					$rows[$i]['driverid'] = $driverid;
					$rows[$i]['teamid'] = $teamid;
					$rows[$i]['tname'] = $teamname;

					$rows[$i]['submitterid'] = htmlentities($myrow['submitterid']);
					$rows[$i]['username'] = htmlentities($myrow['username']);
					$rows[$i]['quali_laptime'] = $myrow['quali_laptime'];
					$rows[$i]['quali_rank'] = $myrow['quali_rank'];
					$rows[$i]['race_laptime'] = $myrow['race_laptime'];
					$rows[$i]['race_rank'] = $myrow['race_rank'];
					$rows[$i]['race_laps'] = $myrow['race_laps'];
					$rows[$i]['race_topspeed'] = $myrow['race_topspeed'];
					$rows[$i]['race_damage'] = $myrow['race_damage'];
					$rows[$i]['race_pitstops'] = $myrow['race_pitstops'];
					$rows[$i]['race_time'] = $myrow['race_time'];
					$j = ($j + 1) % $submit_ok;
					$i++;
				}

				// Fill the last missing rows (necessary if a driver is excluded which comes after the last
				// selected row).
				while (($i % $submit_ok) != 0) {
					$rows[$i]['name'] = $drivername;
					$rows[$i]['driverid'] = $driverid;
					$rows[$i]['teamid'] = $teamid;
					$rows[$i]['tname'] = $teamname;

					$rows[$i]['submitterid'] = htmlentities($submitters_id[$j]);
					$rows[$i]['username'] = htmlentities($submitters[$j]);
					$rows[$i]['quali_laptime'] = '-';
					$rows[$i]['quali_rank'] = '-';
					$rows[$i]['race_laptime'] = '-';
					$rows[$i]['race_rank'] = '-';
					$rows[$i]['race_laps'] = '-';
					$rows[$i]['race_topspeed'] = '-';
					$rows[$i]['race_damage'] = '-';
					$rows[$i]['race_pitstops'] = '-';
					$rows[$i]['race_time'] = '-';
					$j = ($j + 1) % $submit_ok;
					$i++;
				}
				$nb_rows = $i;

				$page->set_block('PAGE_CONTENT_T', 'driver', 'drivers');
				$page->set_block('driver', 'data', 'datarows');

				for ($i = 0; $i < $nb_rows; $i++) {
					$page->set_var(array(
						'PC_SUBMITTER_NAME'		=> $rows[$i]['username'],
						'PC_SUBMITTER_ID'		=> $rows[$i]['submitterid'],
						'PC_DRIVER_NAME'		=> $rows[$i]['name'],
						'PC_TEAM_NAME'			=> $rows[$i]['tname'],
						'PC_TEAM_ID'			=> $rows[$i]['teamid'],
						'PC_RACE_LAPTIME'		=> $rows[$i]['race_laptime'],
						'PC_RACE_RANK'			=> $rows[$i]['race_rank'],
						'PC_RACE_LAPS'			=> $rows[$i]['race_laps'],
						'PC_RACE_TOPSPEED'		=> $rows[$i]['race_topspeed'],
						'PC_RACE_DAMAGE'		=> $rows[$i]['race_damage'],
						'PC_RACE_PITSTOPS'		=> $rows[$i]['race_pitstops'],
						'PC_RACE_TIME'			=> $rows[$i]['race_time'],
						'PC_QUALI_LAPTIME'		=> $rows[$i]['quali_laptime'],
						'PC_QUALI_RANK'			=> $rows[$i]['quali_rank']
					));
					$page->parse('datarows', 'data', true);
					if ((($i+1) % $submit_ok) == 0) {
						$page->parse('drivers', 'driver', true);
						$page->set_var('datarows', '');

					}
				}
				if ($i == 0) {
					$page->set_var("drivers", "");
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
