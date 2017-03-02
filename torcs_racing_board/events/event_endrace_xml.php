<?php

/*
	copyright   : (C) 2017 Bernhard Wymann
	email       : berniw@bluewin.ch
	version     : $Id$

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
*/
	session_start();
	$path_to_root = '../';

	header('Content-type: text/xml');
	header('Content-Disposition: attachment; filename="endrace.xml"');

	require_once($path_to_root . 'secrets/configuration.php');
	require_once($path_to_root . 'lib/functions.php');
	require_once($path_to_root . 'lib/classes.php');
	require_once($path_to_root . 'lib/template.inc');
	require_once($path_to_root . 'lib/functions_event_check.php');

	$db = mysql_connect($db_host, $db_user, $db_passwd) or die;
	mysql_select_db($db_name, $db) or die;

	$stats_hitcount_tablename = $db_prefix . TBL_HITCOUNT;
	$stats_sessioncount_tablename = $db_prefix . TBL_SESSIONCOUNT;
	$stats_tablename = $db_prefix . TBL_STATS;

	$event_tablename = $db_prefix . TBL_EVENT;
	$event_team_table = $db_prefix . TBL_EVENTTEAM;
	$team_tablename = $db_prefix . TBL_TEAM;
	$race_tablename = $db_prefix . TBL_RACE;
	$track_tablename = $db_prefix . TBL_TRACK;
	$driver_tablename = $db_prefix . TBL_DRIVER;
		
	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// Create template instance for page layout.
	$page = new Template($path_to_root . 'templates', 'keep');

	// Define template file(s).
	$page->set_file(array(
		'page' => 'endrace.ixml'
	));

	if (isset($_GET['eventid']) && isset($_GET['raceid'])) {
		$eventid = intval(removeMagicQuotes($_GET['eventid']));
		$eventid_for_db = quoteString($eventid);
		$raceid = intval(removeMagicQuotes($_GET['raceid']));
		$raceid_for_db = quoteString($raceid);
		
		$trackid = 0;
		if (!isSubmissionPhase($race_tablename, $raceid_for_db, $eventid_for_db, $trackid)) {
			die;
		}
		
		$sql = "SELECT r.qualifyingseed AS qualifyingseed, r.raceseed AS raceseed FROM $race_tablename r WHERE r.raceid=$raceid_for_db AND r.eventid=$eventid_for_db";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) == 1) {
			$myrow = mysql_fetch_array($result);
			if (is_null($myrow['qualifyingseed'])) {
				$sql = "LOCK TABLES $race_tablename WRITE";
				$result = mysql_query($sql);
				
				$qseed = mt_rand()/mt_getrandmax();
				$rseed = mt_rand()/mt_getrandmax();
				
				$sql = "UPDATE $race_tablename SET qualifyingseed=$qseed, raceseed=$rseed WHERE raceid=$raceid_for_db AND eventid=$eventid_for_db";
				$result = mysql_query($sql);
			
				$sql = "UNLOCK TABLES";
				$result = mysql_query($sql);
			}
		} else {
			die;
		}
		
		// Get the track name
		$sql = "SELECT t.internalname AS internalname, t.type AS type, r.qualifyingseed AS qualifyingseed, r.raceseed AS raceseed FROM $race_tablename r, $track_tablename t WHERE r.raceid=$raceid_for_db AND r.eventid=$eventid_for_db AND r.trackid=t.trackid";
		
		$result = mysql_query($sql);
		if (mysql_num_rows($result) == 1) {
			// Ok
		} else {
			die;
		}
		
		$myrow = mysql_fetch_array($result);
		$page->set_var(array(
			'PC_TRACK_INTERNALNAME'		=> htmlentities($myrow['internalname']),
			'PC_TRACK_TYPE'				=> htmlentities($myrow['type']),
			'PC_RNG_SEED_Q'				=> htmlentities($myrow['qualifyingseed']),
			'PC_RNG_SEED_R'				=> htmlentities($myrow['raceseed'])
		));

		// Create start list.
		$page->set_block("page", "driverlist", "driverlistrows");
		$sql = "SELECT d.name AS name, t.modulename AS modulename FROM $driver_tablename d, $event_team_table et, $team_tablename t WHERE " .
			"d.teamid=et.teamid AND d.teamid=t.teamid AND et.eventid=$eventid_for_db ORDER BY d.name";
		$result = mysql_query($sql);
		$number = 1;
		while ($myrow = mysql_fetch_array($result)) {
			$page->set_var(array(
				'PC_DRIVER_NO'		=> $number,
				'PC_DRIVER_NAME'	=> $myrow['name'],
				'PC_DRIVER_MODULE'	=> $myrow['modulename']
			));
			$page->parse("driverlistrows", "driverlist", true);
			$number++;
		}
	}

	$page->parse('OUTPUT', 'page');

	$page->p('OUTPUT');
?>
