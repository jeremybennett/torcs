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

	function hasUserSubmittedRaceresult(&$submitted_tablename, $raceid_for_db, $uid_for_db)
	{
		$sql = "SELECT * FROM $submitted_tablename s WHERE s.raceid=$raceid_for_db AND " .
			   "s.submitterid=$uid_for_db";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) == 0) {
			return FALSE;
		} else {
			return TRUE;
		}
	}


	function hasUserTeamOnEvent(&$event_team_table, &$team_tablename, $eventid_for_db, $uid_for_db)
	{
		$sql = "SELECT COUNT(*) AS count FROM $event_team_table et, $team_tablename t WHERE " .
			   "t.teamid=et.teamid AND et.eventid=$eventid_for_db AND " .
			   "t.owner=$uid_for_db";
		$result = mysql_query($sql);
		$myrow = mysql_fetch_array($result);
		if ($myrow['count'] > 0) {
			return TRUE;
		} else {
			return FALSE;
		}
	}


	// Check the time, are we in the download phase of the race?
	// TODO: Make better semantics of times, perhaps remove racing phase.
	function isSubmissionPhase(&$race_tablename, $raceid_for_db, $eventid_for_db, &$trackid)
	{
		$sql = "SELECT r.robot_submission_end AS rose, r.result_submission_end AS rese, r.trackid AS trackid " .
			   "FROM $race_tablename r WHERE r.raceid=$raceid_for_db AND r.eventid=$eventid_for_db";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
			$ct = time();
			$time1 = strtotime($myrow['rose']) - $ct;
			$time2 = strtotime($myrow['rese']) - $ct;
			if ($time1 <= 0 && $time2 >= 0) {
				$trackid = $myrow['trackid'];
				return TRUE;
			} else {
				return FALSE;
			}
		}
		return FALSE;
	}

?>
