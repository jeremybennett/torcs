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

	$event_team_table = $db_prefix . TBL_EVENTTEAM;
	$team_tablename = $db_prefix . TBL_TEAM;
	$race_tablename = $db_prefix . TBL_RACE;

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks the login.
	$user = new User($db, $user_tablename, $loginlog_tablename);

	// TODO: download with automatec script/wget.
	// At the moment just involverd racers have access to the files of the event.
	if ($_SESSION['logged'] == TRUE &&
		$_SESSION['usergroup'] == 'racer' &&
		isset($_GET['eventid']) &&
		isset($_GET['teamid']) &&
		isset($_GET['raceid']))
	{
		$eventid = intval(removeMagicQuotes($_GET['eventid']));
		$eventid_for_db = quoteString($eventid);
		$raceid = intval(removeMagicQuotes($_GET['raceid']));
		$raceid_for_db = quoteString($raceid);
		$teamid = intval(removeMagicQuotes($_GET['teamid']));
		$teamid_for_db = quoteString($teamid);
		$uid_for_db = quoteString(intval($_SESSION['uid']));

		// Check team owner.
		$sql = "SELECT * FROM $event_team_table et, $team_tablename t WHERE " .
			   "t.teamid=et.teamid AND et.eventid=$eventid_for_db AND " .
			   "t.owner=$uid_for_db";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) > 0) {
			// check phase.
			$sql = "SELECT r.robot_submission_end AS rose, r.result_submission_end AS rese, r.trackid AS trackid " .
				"FROM $race_tablename r WHERE r.raceid=$raceid_for_db AND r.eventid=$eventid_for_db";
			$result = mysql_query($sql);
			if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
				$ct = time();
				$time1 = strtotime($myrow['rose']) - $ct;
				$time2 = strtotime($myrow['rese']) - $ct;
				if ($time1 <= 0 && $time2 >= 0) {
					// check if file exists.
					$path = getcwd() . '/' . $path_to_root . 'robots/' . $eventid . '/' . $teamid . '.tar.bz2';
					if (file_exists($path)) {
						//$mtime = date("Y-m-d H:i:s", filemtime($path));
						//$size = filesize($path);
						$sql = "SELECT t.modulename AS modulename " .
							   "FROM $team_tablename t WHERE t.teamid=$teamid_for_db";
						$result = mysql_query($sql);
						if ($myrow = mysql_fetch_array($result)) {
							$filename = $myrow['modulename'] . ".tar.bz2";
							header('Content-type: application/x-bzip2');
							header('Content-Disposition: attachment; filename="' . $filename . '"');
							readfile($path);
							return;
						}
					}

				}
			}
		}
	}

	// Something failed.
	header("HTTP/1.0 404 Not Found");
?>
