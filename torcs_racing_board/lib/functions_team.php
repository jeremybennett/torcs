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


	define('ERR_NAME_INPUT',			1 << 0);
	define('ERR_NAME_UNIQUE',			1 << 1);
	define('ERR_MODULENAME_INPUT',		1 << 2);
	define('ERR_MODULENAME_UNIQUE',		1 << 3);
	define('ERR_DRIVERNAME1_INPUT',		1 << 4);
	define('ERR_DRIVERNAME1_UNIQUE',	1 << 5);
	define('ERR_DRIVERNAME2_INPUT',		1 << 6);
	define('ERR_DRIVERNAME2_UNIQUE',	1 << 7);
	define('ERR_BASENUMBER_INPUT',		1 << 8);
	define('ERR_BASENUMBER_UNIQUE',		1 << 9);
	define('ERR_CAR_INPUT',				1 << 10);

	define('ERR_COMMIT',				1 << 31);

	function isTeamNameOk($error, &$msg) {
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_NAME_INPUT) {
			$msg .= "empty";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_NAME_UNIQUE) {
			$msg .= $sep . "already in use";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function isTeamModuleNameOk($error, &$msg) {
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_MODULENAME_INPUT) {
			$msg .= "empty";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_MODULENAME_UNIQUE) {
			$msg .= $sep . "already in use";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function isTeamDriver1Ok($error, &$msg) {
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_DRIVERNAME1_INPUT) {
			$msg .= "empty or equal to 2";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_DRIVERNAME1_UNIQUE) {
			$msg .= $sep . "already in use";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function isTeamDriver2Ok($error, &$msg) {
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_DRIVERNAME2_INPUT) {
			$msg .= "empty or equal to 1";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_DRIVERNAME2_UNIQUE) {
			$msg .= $sep . "already in use";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function isTeamBasenumberOk($error, &$msg) {
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_BASENUMBER_INPUT) {
			$msg .= "error";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_BASENUMBER_UNIQUE) {
			$msg .= $sep . "already in use";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function isTeamCarOk($error, &$msg) {
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_CAR_INPUT) {
			$msg .= "car not available";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function checkTeamPostForm(&$formerrors)
	{
		// Check team name.
		$formerrors |= (checkPostString('team_name', 1, 40) > 0) ? ERR_NAME_INPUT : 0;
		// Check module name.
		$formerrors |= (checkPostString('team_modulename', 1, 40) > 0) ? ERR_MODULENAME_INPUT : 0;
		// Driver 1 name.
		$formerrors |= (checkPostString('team_driver1_name', 1, 40) > 0) ? ERR_DRIVERNAME1_INPUT : 0;
		// Driver 2 name.
		$formerrors |= (checkPostString('team_driver2_name', 1, 40) > 0) ? ERR_DRIVERNAME2_INPUT : 0;
		// Check base number, must be odd.
		$formerrors |= (checkPostOddInt('team_base_number', 1, 997) > 0) ? ERR_BASENUMBER_INPUT : 0;
		// Check car id.
		$formerrors |= (checkPostInt('team_car_id', 1, 100000) > 0) ? ERR_CAR_INPUT : 0;

		if ($_POST['team_driver1_name'] == $_POST['team_driver2_name']) {
			$formerrors |= ERR_DRIVERNAME1_INPUT | ERR_DRIVERNAME2_INPUT;
		}
	}


	function checkTeamInput($team_tablename, $car_tablename, $driver_tablename, $editmode)
	{
		$formerrors = intval(0);

		checkTeamPostForm($formerrors);

		$sql_where = '';
		if ($editmode == TRUE) {
			$teamid_for_db = quoteString(intval(removeMagicQuotes($_POST['editteamid'])));
			$sql_where = " AND (teamid != $teamid_for_db) ";
		}

		// Check team name.
		if ($formerrors == 0) {
			$team_for_db = quoteString(removeMagicQuotes($_POST['team_name']));
			$sql = "SELECT teamid FROM $team_tablename WHERE (name=$team_for_db) " . $sql_where;
			$result = mysql_query($sql);
			if (mysql_num_rows($result) > 0) {
				// Error, team name already gone.
				$formerrors |= ERR_NAME_UNIQUE;
			}
		}

		// Check module name.
		if ($formerrors == 0) {
			$modname_for_db = quoteString(removeMagicQuotes($_POST['team_modulename']));
			$sql = "SELECT teamid FROM $team_tablename WHERE (modulename=$modname_for_db) " . $sql_where;
			$result = mysql_query($sql);
			if (mysql_num_rows($result) > 0) {
				// Error, module name already gone.
				$formerrors |= ERR_MODULENAME_UNIQUE;
			}
		}

		// Check car id.
		if ($formerrors == 0) {
			$carid_for_db = quoteString(intval(removeMagicQuotes($_POST['team_car_id'])));
			$sql = "SELECT * FROM $car_tablename WHERE carid=$carid_for_db";
			$result = mysql_query($sql);
			if (mysql_num_rows($result) == 0) {
				// Error, we should find one car.
				$formerrors |= ERR_CAR_INPUT;
			}
		}

		// Check driver name 1.
		if ($formerrors == 0) {
			$n1_for_db = quoteString(removeMagicQuotes($_POST['team_driver1_name']));
			$sql = "SELECT driverid FROM $driver_tablename WHERE (name=$n1_for_db) " . $sql_where;
			$result = mysql_query($sql);
			if (mysql_num_rows($result) > 0) {
				// Error, driver name already gone.
				$formerrors |= ERR_DRIVERNAME1_UNIQUE;
			}
		}

		// Check driver name 2.
		if ($formerrors == 0) {
			$n2_for_db = quoteString(removeMagicQuotes($_POST['team_driver2_name']));
			$sql = "SELECT driverid FROM $driver_tablename WHERE (name=$n2_for_db)" . $sql_where;
			$result = mysql_query($sql);
			if (mysql_num_rows($result) > 0) {
				// Error, driver name already gone.
				$formerrors |= ERR_DRIVERNAME2_UNIQUE;
			}
		}

		// Check driver numbers.
		if ($formerrors == 0) {
			$n1_for_db = quoteString(intval(removeMagicQuotes($_POST['team_base_number'])));
			$n2_for_db = quoteString(intval(removeMagicQuotes($_POST['team_base_number'])) + 1);
			$sql = "SELECT driverid FROM $driver_tablename WHERE (racenumber=$n1_for_db OR racenumber=$n2_for_db) " . $sql_where;
			$result = mysql_query($sql);
			if (mysql_num_rows($result) > 0) {
				// Error, race number already gone.
				$formerrors |= ERR_BASENUMBER_UNIQUE;
			}
		}

		return $formerrors;
	}


	function commitEditTeamInputInrace($team_tablename)
	{
		if ($_SESSION['usergroup'] == 'racer') {
			$teamid_for_db = quoteString(intval(removeMagicQuotes($_POST['editteamid'])));
			$teamdesc_for_db = isset($_POST['team_description']) ? quoteString(removeMagicQuotes($_POST['team_description'])) : '';
			$uid_for_db = quoteString($_SESSION['uid']);

			$sql = "UPDATE $team_tablename SET description=$teamdesc_for_db " .
				   "WHERE (owner=$uid_for_db) AND (teamid=$teamid_for_db)";
			mysql_query($sql);
			if (mysql_errno() == 0) {
				return 0;
			}
		}
		return ERR_COMMIT;
	}


	function commitEditTeamInput($team_tablename, $driver_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'racer') {
			$teamid_for_db = quoteString(intval(removeMagicQuotes($_POST['editteamid'])));
			$teamname_for_db = quoteString(removeMagicQuotes($_POST['team_name']));
			$teamdesc_for_db = isset($_POST['team_description']) ? quoteString(removeMagicQuotes($_POST['team_description'])) : '';
			$modname_for_db = quoteString(removeMagicQuotes($_POST['team_modulename']));
			$drivername1_for_db = quoteString(removeMagicQuotes($_POST['team_driver1_name']));
			$drivername2_for_db = quoteString(removeMagicQuotes($_POST['team_driver2_name']));
			$drivernum1_for_db = quoteString(intval(removeMagicQuotes($_POST['team_base_number'])));
			$drivernum2_for_db = quoteString(intval(removeMagicQuotes($_POST['team_base_number'])) + 1);
			$driver_id_1_for_db = quoteString(intval(removeMagicQuotes($_POST['driver_id_1'])));
			$driver_id_2_for_db = quoteString(intval(removeMagicQuotes($_POST['driver_id_2'])));
			$carid_for_db = quoteString(intval(removeMagicQuotes($_POST['team_car_id'])));
			$uid_for_db = quoteString($_SESSION['uid']);

			$sql = "UPDATE $team_tablename SET name=$teamname_for_db, description=$teamdesc_for_db, " .
				   "modulename=$modname_for_db, carid=$carid_for_db " .
				   "WHERE (owner=$uid_for_db) AND (teamid=$teamid_for_db)";
			mysql_query($sql);
			if (mysql_errno() == 0) {
				$sql = "UPDATE $driver_tablename SET name=$drivername1_for_db, " .
					   "racenumber=$drivernum1_for_db WHERE " .
					   "driverid=$driver_id_1_for_db AND teamid=$teamid_for_db";
				mysql_query($sql);
				$sql = "UPDATE $driver_tablename SET name=$drivername2_for_db, " .
					   "racenumber=$drivernum2_for_db WHERE " .
					   "driverid=$driver_id_2_for_db AND teamid=$teamid_for_db";
				mysql_query($sql);
				return 0;
			}
		}
		return ERR_COMMIT;
	}



	function commitTeamInput($team_tablename, $driver_tablename, $path_to_root)
	{
		if (createTeamAllowed($team_tablename)/*$_SESSION['usergroup'] == 'racer'*/) {
			$teamname_for_db = quoteString(removeMagicQuotes($_POST['team_name']));
			$teamdesc_for_db = isset($_POST['team_description']) ? quoteString(removeMagicQuotes($_POST['team_description'])) : '';
			$modname_for_db = quoteString(removeMagicQuotes($_POST['team_modulename']));
			$drivername1_for_db = quoteString(removeMagicQuotes($_POST['team_driver1_name']));
			$drivername2_for_db = quoteString(removeMagicQuotes($_POST['team_driver2_name']));
			$drivernum1_for_db = quoteString(intval(removeMagicQuotes($_POST['team_base_number'])));
			$drivernum2_for_db = quoteString(intval(removeMagicQuotes($_POST['team_base_number'])) + 1);
			$carid_for_db = quoteString(intval(removeMagicQuotes($_POST['team_car_id'])));
			$date_now_for_db = quoteString(date("Y-m-d H:i:s"));
			$uid_for_db = quoteString($_SESSION['uid']);

			$sql = "INSERT INTO $team_tablename (name, description, modulename, carid, created, owner) " .
				   "VALUES ($teamname_for_db, $teamdesc_for_db, $modname_for_db, $carid_for_db, " .
				   "$date_now_for_db, $uid_for_db)";
			mysql_query($sql);
			if (mysql_affected_rows() > 0) {
				$sql = "SELECT LAST_INSERT_ID() AS lastid";
                $result = mysql_query($sql);
                if ($myrow = mysql_fetch_array($result)) {
					$teamid_for_db = $myrow['lastid'];
					$sql = "INSERT INTO $driver_tablename (teamid, racenumber, name, created) " .
						   "VALUES ($teamid_for_db, $drivernum1_for_db, $drivername1_for_db, $date_now_for_db)";
					mysql_query($sql);
					if (mysql_affected_rows() > 0) {
						$sql = "INSERT INTO $driver_tablename (teamid, racenumber, name, created) " .
							   "VALUES ($teamid_for_db, $drivernum2_for_db, $drivername2_for_db, $date_now_for_db)";
						mysql_query($sql);
						if (mysql_affected_rows() > 0) {
							// Ok.
							return 0;
						} else {
							// Error, Rollback.
							$sql = "DELETE FROM $driver_tablename WHERE teamid=$teamid_for_db";
							mysql_query($sql);
							$sql = "DELETE FROM $team_tablename WHERE teamid=$teamid_for_db";
							mysql_query($sql);
						}
					} else {
						// Error, Rollback.
						$sql = "DELETE FROM $team_tablename WHERE teamid=$teamid_for_db";
						mysql_query($sql);
					}
				}
			}
		}

		return ERR_COMMIT;
	}


	function isTeamSignedInRace($signed_tablename, $event_tablename )
	{
		if (isset($_GET['editteamid'])) {
			$teamid = intval(removeMagicQuotes($_GET['editteamid']));
		} else if (isset($_POST['editteamid'])) {
			$teamid = intval(removeMagicQuotes($_POST['editteamid']));
		} else {
			return FALSE;
		}

		$sql = "SELECT e.signin_start AS start, e.enddate AS end FROM $signed_tablename s, " .
			   "$event_tablename e WHERE s.teamid=" . quoteString($teamid) . " " .
			   "AND s.eventid=e.eventid";
		$result = mysql_query($sql);
		while ($myrow = mysql_fetch_array($result)) {
			$ct = time();
			$time1 = strtotime($myrow['start']) - $ct;
			$time2 = strtotime($myrow['end']) - $ct;
			if (($time1 <= 0) && ($time2 >= 0)) {
				return TRUE;
			}
		}
		return FALSE;
	}


	function editTeamAllowed($team_tablename)
	{
		if ($_SESSION['usergroup'] == 'racer') {
			if (isset($_GET['editteamid'])) {
				$teamid = intval(removeMagicQuotes($_GET['editteamid']));
			} else if (isset($_POST['editteamid'])) {
				$teamid = intval(removeMagicQuotes($_POST['editteamid']));
			} else {
				return FALSE;
			}
			$sql = "SELECT owner FROM $team_tablename WHERE teamid=" . quoteString($teamid);
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				if ($myrow['owner'] == $_SESSION['uid']) {
					return TRUE;
				}
			}
		}
		return FALSE;
	}


	function createTeamAllowed($team_tablename)
	{
		if ($_SESSION['usergroup'] == 'racer') {
			$uid_for_db = quoteString(intval($_SESSION['uid']));
			$sql = "SELECT COUNT(owner) AS nbteams FROM $team_tablename " .
				   "WHERE owner=$uid_for_db GROUP BY owner";
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				// Teams available, allowed to create more?
				if ($myrow['nbteams'] < TEAMS_PER_USER) {
					return TRUE;
				}
			} else {
				// No count -> no teams -> more teams allowed.
				return TRUE;
			}
		}
		return FALSE;
	}


	function deleteTeam(
		&$event_report_driver_table,
		&$event_report_team_table,
		&$team_tablename,
		&$driver_tablename,
		&$event_team_table,
		&$race_report_driver_table,
		&$race_report_team_table,
		&$rawresult_tablename,
		&$path_to_root
	)
	{
		if ($_SESSION['usergroup'] == 'admin' && isset($_GET['deleteteamid'])) {
			$teamid = intval(removeMagicQuotes($_GET['deleteteamid']));
			$teamid_for_db = quoteString($teamid);

			// Create array with drivers.
			$sql = "SELECT driverid FROM $driver_tablename WHERE teamid=" . $teamid_for_db;
			$result = mysql_query($sql);
			$driver_ids = array();
			$drivers = 0;
			while ($myrow = mysql_fetch_array($result)) {
				$driver_ids[$drivers] = $myrow['driverid'];
				$drivers++;
			}

			// Delete driver entries.
			for ($i = 0; $i < $drivers; $i++) {
				// Delete event_report_driver entries.
				$sql = "DELETE FROM $event_report_driver_table WHERE driverid=" . quoteString($driver_ids[$i]);
				mysql_query($sql);
				// Delete race_report_driver entries.
				$sql = "DELETE FROM $race_report_driver_table WHERE driverid=" . quoteString($driver_ids[$i]);
				mysql_query($sql);
			}

			// Remove all robot files from events.
			$sql = "SELECT eventid FROM $event_team_table WHERE teamid=" . $teamid_for_db;
			$result = mysql_query($sql);
			while ($myrow = mysql_fetch_array($result)) {
				$dir = getcwd() . '/' . $path_to_root . 'robots/' . $myrow['eventid'];
				$path = $dir . '/' . $teamid . '.tar.bz2';
				if (file_exists($path)) {
					unlink($path);
				}
			}

			// TODO: All queries look most the same, collect it and shorten the code.
			$tables = array(
				$event_report_team_table,
				$race_report_team_table,
				$rawresult_tablename,
				$event_team_table,
				$driver_tablename,
				$team_tablename
			);
			foreach ($tables as $table) {
				$sql = "DELETE FROM " . $table . " WHERE teamid=" . $teamid_for_db;
				mysql_query($sql);
			}

			// Delete Images.
			$dirs = array('logo', 'flag', 'shot1', 'shot2');
			foreach ($dirs as $dir) {
				$path = getcwd() . '/' . $path_to_root . 'images/teams/' . $dir;
				$img = $path . '/' . $teamid . '.jpg';
				$img_tn = $path . '/' . $teamid . '_tn.jpg';
				if (file_exists($img)) {
					unlink($img);
				}
				if (file_exists($img_tn)) {
					unlink($img_tn);
				}
			}
		}
	}


?>
