<?php

/*
	copyright   : (C) 2004-2013 Bernhard Wymann
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

	$event_team_table = $db_prefix . TBL_EVENTTEAM;
	$team_tablename = $db_prefix . TBL_TEAM;
	$event_tablename = $db_prefix . TBL_EVENT;

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks the login.
	$user = new User($db, $user_tablename, $loginlog_tablename);

	// When the event is done everybody is allowed to download the robots.
	if (isset($_GET['eventid']) && isset($_GET['teamid'])) {
		$eventid = intval(removeMagicQuotes($_GET['eventid']));
		$teamid = intval(removeMagicQuotes($_GET['teamid']));
		$teamid_for_db = quoteString($teamid);

		// Check if event is done
		$done = isEventDone($event_tablename, $eventid);
		if ($done == TRUE) {
			// check if file exists.
			$path = getcwd() . '/' . $path_to_root . 'robots/' . $eventid . '/' . $teamid . '.tar.bz2';
			if (file_exists($path)) {
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

	// Something failed.
	header("HTTP/1.0 404 Not Found");
?>
