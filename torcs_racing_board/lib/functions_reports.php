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



	// Is the result submission phase over?
	function isRacePhaseDone($raceid, &$race_tablename)
	{
		$retval = false;
		$raceid_for_db = quoteString($raceid);
		$sql = "SELECT result_submission_end FROM $race_tablename WHERE raceid=$raceid_for_db";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
			$ct = time();
			$time = strtotime($myrow['result_submission_end']) - $ct;
			//echo $time . "   ";
			if ($time < 0) {
				$retval = true;
			}
		}
		return $retval;
	}


	// Are the reports already up to date?
	function isReportAvailable($raceid, &$race_tablename)
	{
		$retval = true;
		$raceid_for_db = quoteString($raceid);
		$sql = "SELECT r.report_updated FROM $race_tablename r WHERE r.raceid=$raceid_for_db";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
			if ($myrow['report_updated'] == 'no') {
				$retval = false;
			}
		}
		return $retval;
	}

	// Create start list.
	function getStartList(
		$raceid,
		&$driver_tablename,
		&$event_team_table,
		&$race_tablename
	)
	{
		$retval = array();
		$raceid_for_db = quoteString($raceid);
		$sql = "SELECT d.driverid AS driverid FROM " .
			   "$driver_tablename d, $event_team_table et, $race_tablename r WHERE " .
			   "d.teamid=et.teamid AND et.eventid=r.eventid AND r.raceid=$raceid_for_db ORDER BY d.name";
		$result = mysql_query($sql);
		$i = 0;
		while ($myrow = mysql_fetch_array($result)) {
			$retval[$i] = $myrow['driverid'];
			$i++;
		}
		return $retval;
	}


	// Create team start list.
	function getTeamStartList(
		$raceid,
		&$event_team_table,
		&$race_tablename
	)
	{
		$retval = array();
		$raceid_for_db = quoteString($raceid);
		$sql = "SELECT et.teamid AS teamid FROM " .
			   "$event_team_table et, $race_tablename r WHERE " .
			   "et.eventid=r.eventid AND r.raceid=$raceid_for_db";
		$result = mysql_query($sql);
		$i = 0;
		while ($myrow = mysql_fetch_array($result)) {
			$retval[$i] = $myrow['teamid'];
			$i++;
		}
		return $retval;
	}


	// Get number of good submissions (number of expected data rows per driver and race).
	function getSubmissions($raceid, &$submitted_tablename)
	{
		$retval = array();
		$raceid_for_db = quoteString($raceid);
		$sql = "SELECT runrace, COUNT(*) AS count FROM " .
			   "$submitted_tablename s WHERE " .
			   "raceid=$raceid_for_db GROUP BY runrace";
		$result = mysql_query($sql);
		while ($myrow = mysql_fetch_array($result)) {
			$retval[$myrow['runrace']] = $myrow['count'];
		}
		if (!isset($retval['ok'])) {
			$retval['ok'] = 0;
		}
		if (!isset($retval['failed'])) {
			$retval['failed'] = 0;
		}
		return $retval;
	}


	// Check if we got enough results to create a final result (rules 6.2.3.).
	function enoughSubmissions($d)
	{
		$retval = false;
		if (($d['failed'] + $d['ok']) > 0) {
			$ratio = $d['failed']/($d['failed'] + $d['ok']);
			if ($ratio <= 0.5) {
				$retval = true;
			}
		}
		return $retval;
	}


	// Compute the median of a named column.
	function getMedian($medianbase, $medianrange, &$rawdata, $colname, $rows)
	{
		$col = array();
		for ($k = 0; $k < $rows; $k++) {
			if (isset($rawdata[$k][$colname])) {
				$col[$k] = $rawdata[$k][$colname];
			} else {
				$col[$k] = 0;
			}
		}
		sort($col, SORT_NUMERIC);

		$median = 0;
		for ($k = $medianbase; $k < $medianrange+$medianbase; $k++) {
			$median += $col[$k];
		}
		if ($medianrange > 0) {
			return $median/$medianrange;
		} else {
			return 0;
		}

	}


	// Update all reports.
	// Assumes that the time has already been checked.
	function updateReports(
		$raceid,
		$eventid,
		&$driver_tablename,
		&$team_tablename,
		&$event_tablename,
		&$event_team_table,
		&$race_tablename,
		&$submitted_tablename,
		&$rawresult_tablename,
		&$race_report_driver_table,
		&$race_report_team_table,
		&$event_report_driver_table,
		&$event_report_team_table,
		&$track_tablename
	)
	{
		if (isReportAvailable($raceid, $race_tablename)) {
			return;
		} else {
			$sql = "LOCK TABLES $race_tablename WRITE, " .
				   "$race_tablename AS r WRITE, " .
				   "$driver_tablename WRITE, " .
				   "$driver_tablename AS d WRITE, " .
				   "$track_tablename WRITE, " .
				   "$track_tablename AS t WRITE, " .
				   "$team_tablename WRITE, " .
				   "$team_tablename AS t WRITE, " .
				   "$event_tablename WRITE, " .
				   "$event_tablename AS e WRITE, " .
				   "$event_team_table WRITE, " .
				   "$event_team_table AS et WRITE, " .
				   "$submitted_tablename WRITE, " .
				   "$submitted_tablename AS s WRITE, " .
				   "$rawresult_tablename WRITE, " .
				   "$race_report_driver_table WRITE, " .
				   "$race_report_driver_table AS rd WRITE, " .
				   "$race_report_team_table WRITE, " .
				   "$race_report_team_table AS tr WRITE, " .
				   "$event_report_driver_table WRITE, " .
				   "$event_report_team_table WRITE";
			$result = mysql_query($sql);
			// Check again if report is already available.
			// Relies on the assumption that the old reports are available
			// TODO:cron job on server.
			if (!isReportAvailable($raceid, $race_tablename)) {
				// Not available, create reports.
				$pointsystem_id = getEventPointSystemId($raceid, $race_tablename, $event_tablename);
				$d = getSubmissions($raceid, $submitted_tablename);
				if (enoughSubmissions($d)) {
					// Ok, enough submissions, the race is valid.
					updateDriverRaceReport(
						$raceid,
						$pointsystem_id,
						$d,
						$driver_tablename,
						$event_team_table,
						$race_tablename,
						$submitted_tablename,
						$rawresult_tablename,
						$event_tablename,
						$race_report_driver_table
					);
					updateTeamRaceReport(
						$raceid,
						$pointsystem_id,
						$driver_tablename,
						$event_team_table,
						$race_tablename,
						$submitted_tablename,
						$rawresult_tablename,
						$event_tablename,
						$race_report_driver_table,
						$race_report_team_table,
						$team_tablename
					);
					updateEventReports(
						$raceid,
						$eventid,
						$race_report_driver_table,
						$race_report_team_table,
						$event_report_driver_table,
						$event_report_team_table
					);
					updateTeamStats(
						$raceid,
						$eventid,
						$driver_tablename,
						$race_tablename,
						$race_report_driver_table,
						$race_report_team_table,
						$team_tablename,
						$track_tablename
					);
				}
				// Finally mark as "reports created".
				$sql = "UPDATE $race_tablename SET report_updated='yes' WHERE raceid=" . quoteString($raceid);
				$result = mysql_query($sql);
			}
			$sql = "UNLOCK TABLES";
			$result = mysql_query($sql);
		}
	}


	// Update the driver report.
	function updateDriverRaceReport(
		$raceid,
		$pointsystem_id,
		&$d,
		&$driver_tablename,
		&$event_team_table,
		&$race_tablename,
		&$submitted_tablename,
		&$rawresult_tablename,
		&$event_tablename,
		&$race_report_driver_table
	)
	{
		$raceid_for_db = quoteString($raceid);
		// List with the id's of the drivers.
		$startlist = getStartList($raceid, $driver_tablename, $event_team_table, $race_tablename);
		// Number of expected submissions per driver (can be less because of driver problem).
		$rows_ok = $d['ok'];
		$rows_failed = $d['failed'];

		$i = 0;
		while (isset($startlist[$i])) {
			$rawdata = array();
			$ranks = array();
			// Odd or even?
			$medianbase = 0;
			$medianrange = 0;
			if (($rows_ok % 2) > 0) {
				// Odd.
				$medianbase = intval($rows_ok/2);
				$medianrange = 1;
			} else {
				// Even.
				$medianbase = intval($rows_ok/2) - 1;
				$medianrange = 2;
			}

			$sql = "SELECT * FROM $rawresult_tablename WHERE " .
				"raceid=$raceid_for_db AND driverid=" . quoteString($startlist[$i]) .
				"ORDER BY race_rank ASC";
			$result = mysql_query($sql);
			$j = 0;
			$carid = 0;
			while ($myrow = mysql_fetch_array($result)) {
				$rawdata[$j] = $myrow;
				$carid = $myrow['carid'];
				$j++;
			}

			$j = 0;
			for ($k = $medianbase; $k < $medianrange+$medianbase; $k++) {
				if (isset($rawdata[$k]['race_rank'])) {
					$ranks[$j] = $rawdata[$k]['race_rank'];
				} else {
					$ranks[$j] = 0;
				}
				$j++;
			}

			$m_points = computePoints($pointsystem_id, $ranks);
			$m_quali_laptime = getMedian($medianbase, $medianrange, $rawdata, 'quali_laptime', $rows_ok);
			$m_quali_rank = getMedian($medianbase, $medianrange, $rawdata, 'quali_rank', $rows_ok);
			$m_race_laptime = getMedian($medianbase, $medianrange, $rawdata, 'race_laptime', $rows_ok);
			$m_race_rank = getMedian($medianbase, $medianrange, $rawdata, 'race_rank', $rows_ok);
			$m_race_laps = getMedian($medianbase, $medianrange, $rawdata, 'race_laps', $rows_ok);
			$m_race_topspeed = getMedian($medianbase, $medianrange, $rawdata, 'race_topspeed', $rows_ok);
			$m_race_damage = getMedian($medianbase, $medianrange, $rawdata, 'race_damage', $rows_ok);
			$m_race_pitstops = getMedian($medianbase, $medianrange, $rawdata, 'race_pitstops', $rows_ok);
			$m_race_time = getMedian($medianbase, $medianrange, $rawdata, 'race_time', $rows_ok);

			$sql = "INSERT INTO $race_report_driver_table (raceid, driverid, carid, points, " .
				"quali_laptime, quali_rank, race_laptime, race_rank, race_laps, race_topspeed, " .
				"race_damage, race_pitstops, race_time) VALUES( $raceid_for_db, " .
				quoteString($startlist[$i]) . ", " .
				quoteString($carid) . ", " .
				quoteString($m_points) . ", " .
				quoteString($m_quali_laptime) . ", " .
				quoteString($m_quali_rank) . ", " .
				quoteString($m_race_laptime) . ", " .
				quoteString($m_race_rank) . ", " .
				quoteString($m_race_laps) . ", " .
				quoteString($m_race_topspeed) . ", " .
				quoteString($m_race_damage) . ", " .
				quoteString($m_race_pitstops) . ", " .
				quoteString($m_race_time) . ")";
			$result = mysql_query($sql);
			$i++;
		}
	}


	// Update the team report.
	function updateTeamRaceReport(
		$raceid,
		$pointsystem_id,
		&$driver_tablename,
		&$event_team_table,
		&$race_tablename,
		&$submitted_tablename,
		&$rawresult_tablename,
		&$event_tablename,
		&$race_report_driver_table,
		&$race_report_team_table,
		&$team_tablename
	)
	{
		$raceid_for_db = quoteString($raceid);
		// List with the id's of the teams.
		$teamlist =  getTeamStartList($raceid, $event_team_table, $race_tablename);
		$i = 0;
		// First update the drivers points.
		while (isset($teamlist[$i])) {
			// Get points from drivers.
			$sql = "SELECT SUM(rd.points) AS points FROM $race_report_driver_table rd, $driver_tablename d WHERE rd.raceid=$raceid_for_db " .
				   "AND rd.driverid=d.driverid AND d.teamid=" . quoteString($teamlist[$i]);
			$result = mysql_query($sql);
			// Update drivers points.
			if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
				$sql = "INSERT INTO $race_report_team_table (raceid, teamid, points) " .
					   "VALUES($raceid_for_db, " . quoteString($teamlist[$i]) .  ", " .
					   quoteString($myrow['points']) . ")";
				$result = mysql_query($sql);
			}
			$i++;
		}

		// Now look for submission points.
		// Query the team owners.
		$sql = "SELECT DISTINCT t.owner, et.eventid FROM $event_team_table et, $team_tablename t , $race_tablename r WHERE " .
			   "r.eventid=et.eventid AND r.raceid=$raceid_for_db AND et.teamid=t.teamid";
		$result = mysql_query($sql);
		while ($myrow = mysql_fetch_array($result)) {
			$owner_for_db = quoteSTring($myrow['owner']);
			// Check if the user has submitted for this race.
			$sql = "SELECT * FROM $submitted_tablename s WHERE s.raceid=$raceid_for_db AND s.submitterid=$owner_for_db " .
				   "AND s.runrace='ok'";
			$pointlegi = mysql_query($sql);
			if (mysql_num_rows($pointlegi) == 1) {
				// Yes, has submitted, 2 points for the weakest team.
				// Find the weakest team.
				$eventid_for_db = quoteSTring($myrow['eventid']);
				$sql = "SELECT SUM(tr.points) AS points, tr.teamid FROM $team_tablename t, $race_report_team_table tr, " .
					"$event_team_table et, $race_tablename r WHERE r.eventid=$eventid_for_db AND " .
					"t.teamid=tr.teamid AND t.owner=$owner_for_db AND tr.raceid=r.raceid AND " .
					"et.eventid=$eventid_for_db AND et.teamid=t.teamid GROUP BY t.teamid";
				$teams_points = mysql_query($sql);
				$min_teamid = 0;
				$min = 1000000;
				while ($prow = mysql_fetch_array($teams_points)) {
					if ($prow['points'] < $min) {
						$min = $prow['points'];
						$min_teamid = $prow['teamid'];
					}
				}

				// Add two points for the weaker team.
				$submission_points = computeSubmissionPoints($pointsystem_id);
				$sql = "UPDATE $race_report_team_table SET points=points+$submission_points WHERE teamid=" .
					   quoteString($min_teamid) . " AND raceid=$raceid_for_db";
				$addpoints = mysql_query($sql);
			}
		}
	}


	function updateEventReports(
		$raceid,
		$eventid,
		&$race_report_driver_table,
		&$race_report_team_table,
		&$event_report_driver_table,
		&$event_report_team_table
	)
	{
		// Update driver report.
		$raceid_for_db = quoteString($raceid);
		$eventid_for_db = quoteSTring($eventid);

		$sql = "SELECT * FROM $race_report_driver_table rd WHERE rd.raceid=$raceid_for_db";
		$result = mysql_query($sql);
		while ($myrow = mysql_fetch_array($result)) {
			// Update standings.
			$driverid_for_db = quoteString($myrow['driverid']);
			$points_for_db = quoteString($myrow['points']);
			$sql = "UPDATE $event_report_driver_table SET points=points+$points_for_db " .
				   "WHERE eventid=$eventid_for_db AND driverid=$driverid_for_db";
			$driver_update = mysql_query($sql);
			if (mysql_affected_rows() == 0) {
				$sql = "INSERT INTO $event_report_driver_table (eventid, driverid, points) " .
					   "VALUES($eventid_for_db, $driverid_for_db, $points_for_db)";
				mysql_query($sql);
			}
		}

		// Update team report.
		$sql = "SELECT * FROM $race_report_team_table tr WHERE tr.raceid=$raceid_for_db";
		$result = mysql_query($sql);
		while ($myrow = mysql_fetch_array($result)) {
			// Update standings.
			$teamid_for_db = quoteString($myrow['teamid']);
			$points_for_db = quoteString($myrow['points']);
			$sql = "UPDATE $event_report_team_table SET points=points+$points_for_db " .
				   "WHERE eventid=$eventid_for_db AND teamid=$teamid_for_db";
			$team_update = mysql_query($sql);
			if (mysql_affected_rows() == 0) {
				$sql = "INSERT INTO $event_report_team_table (eventid, teamid, points) " .
					   "VALUES($eventid_for_db, $teamid_for_db, $points_for_db)";
				mysql_query($sql);
			}
		}
	}


	function updateTeamStats(
		$raceid,
		$eventid,
		&$driver_tablename,
		&$race_tablename,
		&$race_report_driver_table,
		&$race_report_team_table,
		&$team_tablename,
		&$track_tablename
	)
	{
		$raceid_for_db = quoteString($raceid);
		$length_km = 0.0;
		$sql = "SELECT * FROM $race_tablename r, $track_tablename t WHERE " .
			   "r.raceid=$raceid_for_db AND r.trackid=t.trackid";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
			$length_km = $myrow['length']/1000.0;
		}

		// Update drivers and teams.
		$sql = "SELECT rd.driverid, d.teamid, rd.points, rd.race_laps FROM $race_report_driver_table rd, " .
			   "$driver_tablename d WHERE " .
			   "rd.raceid=$raceid_for_db AND d.driverid=rd.driverid";
		$result = mysql_query($sql);
		while ($myrow = mysql_fetch_array($result)) {
			// Update statistics.
			$dist_for_db = quoteString($length_km*$myrow['race_laps']);
			$races = 0;
			if ($myrow['race_laps'] > 0) {
				$races = 1;
			}
			$races_for_db = quoteString($races);
			$driverid_for_db = quoteString($myrow['driverid']);
			$points_for_db = quoteString($myrow['points']);
			$sql = "UPDATE $driver_tablename SET points=points+$points_for_db, races=races+$races_for_db, " .
				   "distance=distance+$dist_for_db WHERE driverid=$driverid_for_db";
			mysql_query($sql);

			$teamid_for_db = quoteString($myrow['teamid']);
			$sql = "UPDATE $team_tablename SET distance=distance+$dist_for_db WHERE teamid=$teamid_for_db";
			mysql_query($sql);
		}

		// Update the rest of the team data.
		$sql = "SELECT * FROM $race_report_team_table tr WHERE tr.raceid=$raceid_for_db";
		$result = mysql_query($sql);
		while ($myrow = mysql_fetch_array($result)) {
			// Update standings.
			$teamid_for_db = quoteString($myrow['teamid']);
			$points_for_db = quoteString($myrow['points']);
			$sql = "UPDATE $team_tablename SET points=points+$points_for_db, races=races+1 " .
				   "WHERE teamid=$teamid_for_db";
			mysql_query($sql);
		}
	}


	function secondsToTime($sec)
	{
		$cs = $sec - floor($sec);
		$cs = intval(round(100.0*$cs));
		$s = ($sec % 60);
		$m = floor(($sec%3600)/60);
		$h = floor($sec/3600);
		return sprintf("%d:%02d:%02d.%02d", $h, $m, $s, $cs);
	}

	function secondsToLaptime($sec)
	{
		$cs = $sec - floor($sec);
		$cs = intval(round(1000.0*$cs));
		$s = ($sec % 60);
		$m = floor(($sec%3600)/60);
		return sprintf("%d:%02d.%03d", $m, $s, $cs);
	}


	function speedToKMH($ms)
	{
		return sprintf("%.1f", $ms*3.6);
	}

?>
