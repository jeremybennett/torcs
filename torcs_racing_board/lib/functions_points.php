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

	// The pointssystems are identified by the index, do not change the order!
	// TODO: move into getPointSystems
	$pointsystems = array(
		'No points',
		'Endurance championship'
	);


	// Get the description string of the point system.
	function getPointSystems()
	{
		global $pointsystems;
		return $pointsystems;
	}


	// Get the pointsystem of an event.
	function getEventPointSystemId($raceid, &$race_tablename, &$event_tablename)
	{
		$retval = -1;
		$raceid_for_db = quoteString($raceid);
		$sql = "SELECT pointsystem FROM $race_tablename r, $event_tablename e WHERE " .
			   "r.eventid=e.eventid AND r.raceid=$raceid_for_db";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
			$retval = $myrow['pointsystem'];
		}
		return $retval;
	}


	// Compute the driver points from the rank(s).
	function computePoints($pointsystem_id, &$ranks_array)
	{
		if ($pointsystem_id == 0) {
			return 0;
		} else if ($pointsystem_id == 1) {
			return compute_EC_Points($ranks_array);
		}
	}


	// Compute points given for the submission.
	function computeSubmissionPoints($pointsystem_id)
	{
		if ($pointsystem_id == 0) {
			return 0;
		} else if ($pointsystem_id == 1) {
			return 2;
		}
	}


	// Compute points for the endurance championship (rules 4.).
	function compute_EC_Points(&$ranks_array) {
		$points = array(0, 20, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
		$i = 0;
		$p = 0;
		while (isset($ranks_array[$i])) {
			if (isset($points[$ranks_array[$i]])) {
				$p = $p + $points[$ranks_array[$i]];
			}
			$i++;
		}
		if ($i > 0) {
			return $p/$i;
		} else {
			return 0;
		}
	}

?>
