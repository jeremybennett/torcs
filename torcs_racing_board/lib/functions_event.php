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

	function checkEventInput()
	{
		$formerrors = intval(0);

		// Check name.
		$formerrors += checkPostString('event_name', MIN_USERNAME_LENGTH, 40);

		// Check times.
		// TODO: Check ordering.
		$formerrors += checkPostDateTime('event_signin_start');
		$formerrors += checkPostDateTime('event_signin_end');
		$formerrors += checkPostDateTime('event_start');
		$formerrors += checkPostDateTime('event_end');

		// Check maximum number of teams.
		$formerrors += checkPostInt('event_maxteams', 2, TEAMS_PER_EVENT);

		// Check pointsystem.
		$formerrors += checkPostInt('event_pointsystem', 0, 100);

		// Check cars.
		if (!isset($_POST['event_cars']) || count($_POST['event_cars']) < 1) {
			$formerrors += 1;
		}

		// Check rules.
		$formerrors += checkPostFile('event_rules', 50000, 'text/html');

		return $formerrors;
	}


	function commitEventInput($event_tablename, $event_car_table, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin') {
			$name_for_db = quoteString(removeMagicQuotes($_POST['event_name']));
			$desc_for_db = isset($_POST['event_description']) ? quoteString(removeMagicQuotes($_POST['event_description'])) : "''";
			$signin_start_for_db = quoteString(removeMagicQuotes($_POST['event_signin_start']));
			$signin_end_for_db = quoteString(removeMagicQuotes($_POST['event_signin_end']));
			$start_for_db = quoteString(removeMagicQuotes($_POST['event_start']));
			$end_for_db = quoteString(removeMagicQuotes($_POST['event_end']));
			$maxteams_for_db = quoteString(intval(removeMagicQuotes($_POST['event_maxteams'])));
			$points_for_db = quoteString(intval(removeMagicQuotes($_POST['event_pointsystem'])));

			// Commit data.
			$sql = "INSERT INTO $event_tablename " .
				"(name, description, signin_start, signin_end, startdate, enddate, maxteams, pointsystem) VALUES " .
				"($name_for_db, $desc_for_db, $signin_start_for_db, $signin_end_for_db, " .
				"$start_for_db, $end_for_db, $maxteams_for_db, $points_for_db)";
			mysql_query($sql);

			// Commit cars.
			// TODO: Check if cars really exist.
			if (mysql_affected_rows() > 0) {
				$sql = "SELECT LAST_INSERT_ID() AS lastid";
				$result = mysql_query($sql);
				if ($myrow = mysql_fetch_array($result)) {
					$eventid = $myrow['lastid'];
					for ($i = 0; $i < count($_POST['event_cars']); $i++) {
						$carid_for_db = quoteString(intval(removeMagicQuotes($_POST['event_cars'][$i])));
						$sql = "INSERT INTO $event_car_table " .
							"(carid, eventid) VALUES " .
							"($carid_for_db, $eventid)";
						mysql_query($sql);
					}

					// Store rules.
					$file = $_FILES['event_rules'];
					if (is_uploaded_file($file['tmp_name'])) {
						$path = getcwd() . '/' . $path_to_root . 'rules/' . $eventid . '.html';
						move_uploaded_file($file['tmp_name'], $path);
					}
				}
			}
		}
	}


	function updateEventInput($event_tablename, $event_car_table, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin' && isset($_POST['event_id'])) {

			$eventid = intval(removeMagicQuotes($_POST['event_id']));
			$eventid_for_db = quoteString($eventid);
			$name_for_db = quoteString(removeMagicQuotes($_POST['event_name']));
			$desc_for_db = isset($_POST['event_description']) ? quoteString(removeMagicQuotes($_POST['event_description'])) : "''";
			$signin_start_for_db = quoteString(removeMagicQuotes($_POST['event_signin_start']));
			$signin_end_for_db = quoteString(removeMagicQuotes($_POST['event_signin_end']));
			$start_for_db = quoteString(removeMagicQuotes($_POST['event_start']));
			$end_for_db = quoteString(removeMagicQuotes($_POST['event_end']));
			$maxteams_for_db = quoteString(intval(removeMagicQuotes($_POST['event_maxteams'])));
			$points_for_db = quoteString(intval(removeMagicQuotes($_POST['event_pointsystem'])));

			$sql = "UPDATE $event_tablename SET " .
				   "name=$name_for_db, description=$desc_for_db, signin_start=$signin_start_for_db, " .
				   "signin_end=$signin_end_for_db, startdate=$start_for_db, enddate=$end_for_db, " .
				   "maxteams=$maxteams_for_db, pointsystem=$points_for_db " .
				   "WHERE eventid=$eventid_for_db";
			mysql_query($sql);

			if (mysql_affected_rows() > 0 || mysql_errno() == 0) {
				// Update was ok, update cars, start with deleting the old entries.
				$sql = "DELETE FROM $event_car_table WHERE eventid=" . $eventid_for_db;
				mysql_query($sql);
				// Now store the new ones.
				for ($i = 0; $i < count($_POST['event_cars']); $i++) {
					$carid_for_db = quoteString(intval(removeMagicQuotes($_POST['event_cars'][$i])));
					$sql = "INSERT INTO $event_car_table " .
						   "(carid, eventid) VALUES " .
						   "($carid_for_db, $eventid_for_db)";
					mysql_query($sql);
				}

				// Delete the old rules.
				$path = getcwd() . '/' . $path_to_root . 'rules/' . $eventid . '.html';
				if (file_exists($path)) {
					unlink($path);
				}
				$file = $_FILES['event_rules'];
				if (is_uploaded_file($file['tmp_name'])) {
					move_uploaded_file($file['tmp_name'], $path);
				}
			}
		}
	}


	function deleteEvent(
		&$event_tablename,
		&$event_report_driver_table,
		&$event_report_team_table,
		&$event_car_table,
		&$event_team_table,
		&$race_tablename,
		&$race_report_driver_table,
		&$race_report_team_table,
		&$rawresult_tablename,
		&$submitted_tablename,
		&$path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin' &&
			isset($_GET['deleteeventid']))
		{
			$id = intval(removeMagicQuotes($_GET['deleteeventid']));
			$id_for_db = quoteString($id);
			// Delete races.
			$sql = "SELECT raceid FROM $race_tablename WHERE eventid=" . $id_for_db;
			$result = mysql_query($sql);
			while ($myrow = mysql_fetch_array($result)) {
				$raceid_for_db = quoteString(intval($myrow['raceid']));
				// TODO: Merge with deleterace.
				// TODO: shorten with array.
				// Delete rawresult.
				$sql = "DELETE FROM $rawresult_tablename WHERE raceid=" . $raceid_for_db;
				mysql_query($sql);
				// Delete resultsubmitted.
				$sql = "DELETE FROM $submitted_tablename WHERE raceid=" . $raceid_for_db;
				mysql_query($sql);
				// Delete race_report_team.
				$sql = "DELETE FROM $race_report_team_table WHERE raceid=" . $raceid_for_db;
				mysql_query($sql);
				// Delete race_report_driver.
				$sql = "DELETE FROM $race_report_driver_table WHERE raceid=" . $raceid_for_db;
				mysql_query($sql);
				// Delete race.
				$sql = "DELETE FROM $race_tablename WHERE raceid=" . $raceid_for_db;
				mysql_query($sql);
			}

			// Delete event_car.
			$sql = "DELETE FROM $event_car_table WHERE eventid=" . $id_for_db;
			mysql_query($sql);

			// Remove robot files.
			$sql = "SELECT teamid FROM $event_team_table WHERE eventid=" . $id_for_db;
			$result = mysql_query($sql);
			$dir = getcwd() . '/' . $path_to_root . 'robots/' . $id;
			while ($myrow = mysql_fetch_array($result)) {
				// Remove robot file.
				$path = $dir . '/' . $myrow['teamid'] . '.tar.bz2';
				if (file_exists($path)) {
					unlink($path);
				}
			}
			// Remove Event-Robot directory.
			if (file_exists($dir)) {
				rmdir($dir);
			}

			// Delete rule file.
			$dir = getcwd() . '/' . $path_to_root . 'rules/' . $id . '.html';
			if (file_exists($dir)) {
				unlink($path);
			}

			// TODO: shorten with array.
			// Delete event_team.
			$sql = "DELETE FROM $event_team_table WHERE eventid=" . $id_for_db;
			mysql_query($sql);
			// Delete event_report_driver.
			$sql = "DELETE FROM $event_report_driver_table WHERE eventid=" . $id_for_db;
			mysql_query($sql);
			// Delete event_report_team.
			$sql = "DELETE FROM $event_report_team_table WHERE eventid=" . $id_for_db;
			mysql_query($sql);
			// Delete event.
			$sql = "DELETE FROM $event_tablename WHERE eventid=" . $id_for_db;
			mysql_query($sql);
		}
	}


	function checkRaceInput()
	{
		$formerrors = intval(0);

		$formerrors += checkPostInt('event_id', 0, 10000);
		$formerrors += checkPostInt('race_track', 0, 10000);
		$formerrors += checkPostDateTime('race_robot_sub_start');
		$formerrors += checkPostDateTime('race_robot_sub_end');
		$formerrors += checkPostDateTime('race_result_sub_start');
		$formerrors += checkPostDateTime('race_result_sub_end');

		return $formerrors;
	}


	function commitRaceInput($race_tablename, $event_tablename, $track_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin') {
			$eventid_for_db = quoteString(intval(removeMagicQuotes($_POST['event_id'])));
			$trackid_for_db = quoteString(intval(removeMagicQuotes($_POST['race_track'])));
			$date_rob_start = quoteString(removeMagicQuotes($_POST['race_robot_sub_start']));
			$date_rob_end = quoteString(removeMagicQuotes($_POST['race_robot_sub_end']));
			$date_res_start = quoteString(removeMagicQuotes($_POST['race_result_sub_start']));
			$date_res_end = quoteString(removeMagicQuotes($_POST['race_result_sub_end']));

			if (existsEntry($event_tablename, 'eventid', $eventid_for_db) &&
				existsEntry($track_tablename, 'trackid', $trackid_for_db))
			{
				// Commit data.
				$sql = "INSERT INTO $race_tablename " .
				"(eventid, trackid, robot_submission_start, robot_submission_end, " .
				"result_submission_start, result_submission_end) VALUES " .
				"($eventid_for_db, $trackid_for_db, $date_rob_start, $date_rob_end, " .
				"$date_res_start, $date_res_end)";
				mysql_query($sql);
			}
		}
	}


	function updateRaceInput($race_tablename, $event_tablename, $track_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin' && isset($_POST['race_id'])) {
			$raceid_for_db = quoteString(intval(removeMagicQuotes($_POST['race_id'])));
			$trackid_for_db = quoteString(intval(removeMagicQuotes($_POST['race_track'])));
			$date_rob_start = quoteString(removeMagicQuotes($_POST['race_robot_sub_start']));
			$date_rob_end = quoteString(removeMagicQuotes($_POST['race_robot_sub_end']));
			$date_res_start = quoteString(removeMagicQuotes($_POST['race_result_sub_start']));
			$date_res_end = quoteString(removeMagicQuotes($_POST['race_result_sub_end']));

			if (existsEntry($track_tablename, 'trackid', $trackid_for_db)) {
				$sql = "UPDATE $race_tablename SET trackid=$trackid_for_db, " .
					   "robot_submission_start=$date_rob_start, robot_submission_end=$date_rob_end, " .
					   "result_submission_start=$date_res_start, result_submission_end=$date_res_end " .
					   "WHERE raceid=$raceid_for_db";
				mysql_query($sql);
			}
		}
	}

	function deleteRace(
		&$race_tablename,
		&$race_report_driver_table,
		&$race_report_team_table,
		&$rawresult_tablename,
		&$submitted_tablename
	)
	{
		if ($_SESSION['usergroup'] == 'admin' && isset($_GET['deleteraceid'])) {
			$raceid_for_db = quoteString(intval(removeMagicQuotes($_GET['deleteraceid'])));
			// Delete rawresult.
			$sql = "DELETE FROM $rawresult_tablename WHERE raceid=" . $raceid_for_db;
			mysql_query($sql);
			// Delete resultsubmitted.
			$sql = "DELETE FROM $submitted_tablename WHERE raceid=" . $raceid_for_db;
			mysql_query($sql);
			// Delete race_report_team.
			$sql = "DELETE FROM $race_report_team_table WHERE raceid=" . $raceid_for_db;
			mysql_query($sql);
			// Delete race_report_driver.
			$sql = "DELETE FROM $race_report_driver_table WHERE raceid=" . $raceid_for_db;
			mysql_query($sql);
			// Delete race.
			$sql = "DELETE FROM $race_tablename WHERE raceid=" . $raceid_for_db;
			mysql_query($sql);
		}
	}


	function registerRobot($event_tablename, $event_team_table, $event_car_table, $team_tablename, $path_to_root)
	{
		$error = true;

		if ($_SESSION['usergroup'] == 'racer' &&
			isset($_POST['robot_package_submit']) &&
			isset($_POST['robot_teamid']) &&
			isset($_FILES['robot_package']) &&
			isset($_GET['vieweventid'])
		) {
			// Perhaps I have to remove the mime check... too many different things.
			if (checkPostFile('robot_package', ROBOT_MODULE_SIZE, 'application/x-bzip2') == 0 ||
				checkPostFile('robot_package', ROBOT_MODULE_SIZE, 'application/octet-stream') == 0 ||
				checkPostFile('robot_package', ROBOT_MODULE_SIZE, 'application/bzip2') == 0 ||
				checkPostFile('robot_package', ROBOT_MODULE_SIZE, 'application/x-tbz') == 0 ||
				checkPostFile('robot_package', ROBOT_MODULE_SIZE, 'application/x-bz2') == 0 ||
				checkPostFile('robot_package', ROBOT_MODULE_SIZE, 'application/x-bzip') == 0 ||
				checkPostFile('robot_package', ROBOT_MODULE_SIZE, 'application/x-compressed') == 0
			) {
				$eventid = intval(removeMagicQuotes($_GET['vieweventid']));
				$eventid_for_db = quoteString($eventid);
				$teamid = intval(removeMagicQuotes($_POST['robot_teamid']));
				$teamid_for_db = quoteString($teamid);

				// Check if there is space for another team.
				$sql = "SELECT maxteams FROM $event_tablename WHERE eventid=$eventid_for_db";
				$result = mysql_query($sql);
				if (mysql_num_rows($result) != 1) {
					return;
				}
				$myrow = mysql_fetch_array($result);
				$teams_max = $myrow['maxteams'];

				$sql = "SELECT COUNT(*) AS count FROM $event_team_table et, $team_tablename t WHERE et.eventid=" .
					   $eventid_for_db . " AND et.teamid=t.teamid";
				$result = mysql_query($sql);
				if (mysql_num_rows($result) != 1) {
					return;
				}
				$myrow = mysql_fetch_array($result);
				$teams_registered = $myrow['count'];
				$teams_left = intval($teams_max) - $teams_registered;
				if ($teams_left < 1) {
					return;
				}

				// Check owner, id's, event, car and user.
				$sql = "SELECT t.modulename AS modulename, e.signin_start AS start, e.signin_end AS end FROM " .
					   "$event_car_table ec, $event_tablename e, $team_tablename t LEFT JOIN " .
					   "$event_team_table et ON (t.teamid=et.teamid AND et.eventid=$eventid_for_db) WHERE " .
				       "ec.eventid=$eventid_for_db AND ec.carid=t.carid AND t.owner=" . quoteString(intval($_SESSION['uid'])) . " " .
					   "AND (et.eventid!=$eventid_for_db OR isnull(et.eventid)) AND e.eventid=$eventid_for_db AND t.teamid=$teamid_for_db";
				$result = mysql_query($sql);

				if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
					$ct = time();
					$time1 = strtotime($myrow['start']) - $ct;
					$time2 = strtotime($myrow['end']) - $ct;
					if (!($time1 <= 0 && $time2 >= 0)) {
						return;
					}

					// Everythink looks ok, register team.
					$sql = "INSERT INTO $event_team_table (teamid, eventid) " .
						   "VALUES ($teamid_for_db, $eventid_for_db)";
					$result = mysql_query($sql);
					if (mysql_affected_rows() == 1) {
						// Update ok.

						// Create directory for robots if not already available.
						$dir = getcwd() . '/' . $path_to_root . 'robots/' . $eventid;
						if (!file_exists($dir)) {
							mkdir($dir);
						}

						// Remove old file.
						$path = $dir . '/' . $teamid . '.tar.bz2';
						if (file_exists($path)) {
							unlink($path);
						}
						// Store new file.
						$file = $_FILES['robot_package'];
						if (is_uploaded_file($file['tmp_name'])) {
							move_uploaded_file($file['tmp_name'], $path);
						}
						$error =false;
					}
				}
			}
		}
		return $error;
	}


	function unregisterRobot($event_team_table, $event_tablename, $team_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'racer' &&
			isset($_GET['remteamid']) &&
			isset($_GET['vieweventid'])
		) {
			$eventid = intval(removeMagicQuotes($_GET['vieweventid']));
			$eventid_for_db = quoteString($eventid);
			$teamid = intval(removeMagicQuotes($_GET['remteamid']));
			$teamid_for_db = quoteString($teamid);

			// Check if team is owned by the user, and if we are in the right phase.
			$sql = "SELECT e.signin_start AS start, e.signin_end AS end FROM " .
				   "$event_team_table et, $event_tablename e, $team_tablename t WHERE " .
				   "et.eventid=$eventid_for_db AND et.eventid=e.eventid AND " .
				   "t.teamid=et.teamid AND t.teamid=$teamid_for_db AND " .
				   "t.owner=" . quoteString(intval($_SESSION['uid']));
			$result = mysql_query($sql);

			if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
				// Check time.
				$ct = time();
				$time1 = strtotime($myrow['start']) - $ct;
				$time2 = strtotime($myrow['end']) - $ct;
				if (!($time1 <= 0 && $time2 >= 0)) {
					return;
				}

				// Delete db entry.
				$sql = "DELETE FROM $event_team_table WHERE teamid=$teamid_for_db AND eventid=$eventid_for_db";
				$result = mysql_query($sql);
				if (mysql_affected_rows() == 1) {
					$path = getcwd() . '/' . $path_to_root . 'robots/' . $eventid . '/' . $teamid . '.tar.bz2';
					if (file_exists($path)) {
						unlink($path);
					}
				}
			}
		}
	}


	function updateRobot($event_tablename, $event_team_table, $team_tablename, $race_tablename, $path_to_root)
	{
		$error = true;

		if ($_SESSION['usergroup'] == 'racer' &&
			isset($_POST['robot_package_submit_update']) &&
			isset($_POST['robot_teamid']) &&
			isset($_POST['robot_raceid']) &&
			isset($_FILES['update_robot_package']) &&
			isset($_GET['vieweventid'])
		) {
			// Perhaps I have to remove the mime check... too many different things.
			if (checkPostFile('update_robot_package', ROBOT_MODULE_SIZE, 'application/x-bzip2') == 0 ||
				checkPostFile('update_robot_package', ROBOT_MODULE_SIZE, 'application/octet-stream') == 0 ||
				checkPostFile('update_robot_package', ROBOT_MODULE_SIZE, 'application/bzip2') == 0 ||
				checkPostFile('update_robot_package', ROBOT_MODULE_SIZE, 'application/x-tbz') == 0 ||
				checkPostFile('update_robot_package', ROBOT_MODULE_SIZE, 'application/x-bz2') == 0 ||
				checkPostFile('update_robot_package', ROBOT_MODULE_SIZE, 'application/x-bzip') == 0 ||
				checkPostFile('update_robot_package', ROBOT_MODULE_SIZE, 'application/x-compressed') == 0
			) {
				$eventid = intval(removeMagicQuotes($_GET['vieweventid']));
				$eventid_for_db = quoteString($eventid);
				$teamid = intval(removeMagicQuotes($_POST['robot_teamid']));
				$teamid_for_db = quoteString($teamid);
				$raceid = intval(removeMagicQuotes($_POST['robot_raceid']));
				$raceid_for_db = quoteString($raceid);

				$sql = "SELECT r.robot_submission_start AS rs, r.robot_submission_end AS re " .
					   "FROM $event_team_table et, $team_tablename t, $event_tablename e, " .
					   "$race_tablename r WHERE et.teamid=$teamid_for_db AND e.eventid=$eventid_for_db AND " .
					   "et.eventid=e.eventid AND t.owner=" . quoteString(intval($_SESSION['uid'])) . " " .
					   "AND r.eventid=e.eventid AND r.raceid=$raceid_for_db AND t.teamid=$teamid_for_db";
				$result = mysql_query($sql);

				if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
					$ct = time();
					$time1 = strtotime($myrow['rs']) - $ct;
					$time2 = strtotime($myrow['re']) - $ct;
					$path = getcwd() . '/' . $path_to_root . 'robots/' . $eventid . '/' . $teamid . '.tar.bz2';

					if (($time1 <= 0 && $time2 >= 0) && file_exists($path)) {
						// Remove old file.
						unlink($path);
						// Store new file.
						$file = $_FILES['update_robot_package'];
						if (is_uploaded_file($file['tmp_name'])) {
							move_uploaded_file($file['tmp_name'], $path);
							$error = false;
						}
					}
				}
			}
		}
		return $error;
	}

?>
