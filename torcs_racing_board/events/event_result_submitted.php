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
	require_once($path_to_root . 'lib/functions_event_check.php');

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
	$event_team_table = $db_prefix . TBL_EVENTTEAM;
	$team_tablename = $db_prefix . TBL_TEAM;
	$race_tablename = $db_prefix . TBL_RACE;
	$track_tablename = $db_prefix . TBL_TRACK;
	$driver_tablename = $db_prefix . TBL_DRIVER;
	$submitted_tablename = $db_prefix . TBL_RESULTSUBMITTED;
	$car_tablename = $db_prefix . TBL_CAR;
	$rawresult_tablename = $db_prefix . TBL_RAWRESULT;

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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Result Submission Page',
		'PB_DESCRIPTION'	=> 'Submit the results for an event on the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, event, race, competition, run, result, submit',
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

	// TODO: heavy refactoring, structure is too deep, function too long.

	if (isset($_POST['race_result_submit']) && isset($_POST['event_id']) &&
		isset($_POST['race_id']) && $_SESSION['usergroup'] == 'racer' &&
		isset($_FILES['race_result_file']))
	{
		$eventid = intval(removeMagicQuotes($_POST['event_id']));
		$eventid_for_db = quoteString($eventid);
		$raceid = intval(removeMagicQuotes($_POST['race_id']));
		$raceid_for_db = quoteString($raceid);
		$uid_for_db = quoteString(intval($_SESSION['uid']));

		// Check if the racer has a team in this event.
		// Check the time, are we in the submission phase of the race?
		// Check if already submitted.
		$trackid = 0;
		if (hasUserTeamOnEvent($event_team_table, $team_tablename, $eventid_for_db, $uid_for_db) &&
			isSubmissionPhase($race_tablename, $raceid_for_db, $eventid_for_db, $trackid) &&
			!hasUserSubmittedRaceresult($submitted_tablename, $raceid_for_db, $uid_for_db))
		{
			$trackid_for_db = quoteString($trackid);

			// Check file.
			$file = $_FILES['race_result_file'];
			require_once($path_to_root . 'lib/functions_validate.php');

			// Up from here there are "non hacker" errors possible, so report them.
			$error = 0;
			$errorarray = array();
			$warning = 0;
			$warningarray = array();

			if (checkPostFile('race_result_file', ROBOT_RESULT_SIZE, 'text/xml') == 0) {
				// File looks ok.
				require_once($path_to_root . 'lib/functions_txml.php');
				require_once($path_to_root . 'lib/functions_result.php');

				$filename = $file['tmp_name'];
				if (is_uploaded_file($filename) && $root = getRoot($filename)) {
					// Create "indexed" node array.
					$nodes = array();
					children($root, $root->get_attribute(TXML_NAME), $nodes);

					// Do some simple sanity checks on the data.
					// Get track info.
					$sql = "SELECT * FROM $track_tablename WHERE trackid=$trackid_for_db";
					$result = mysql_query($sql);
					$track_row = mysql_fetch_array($result);
					if (isset($track_row) && isset($nodes[TXML_SECT_RESULTS . "/" . $track_row['name']])) {
						$startlist = getStartlistArray($track_row['name'], $nodes);
						$qualiresult = getQualiresultArray($track_row['name'], $nodes);
						$raceresult = getRaceresultArray($track_row['name'], $nodes);

						if (count($startlist) == count($qualiresult) && count($startlist) == count($raceresult)) {
// TODO?: Check for multiple entry of the same driver!
// The database definition avoids multiple inserts, should we let the user know?
							// Check if all required fields are available.
							$count = count($startlist);
							$htmltrack = htmlentities($track_row['name']);
							for ($i = 1; $i <= $count; $i++) {
								// Starting list.
								$ps = $htmltrack . '/' . TXML_SECT_DRIVERS;
								$checklist = array(TXML_ATTS_MODULENAME, TXML_ATTN_START_MODULE_INDEX);
								checkarray($i, $ps, $error, $errorarray, $startlist[$i], $checklist);

								// Qualification.
								$ps = TXML_SECT_QUALIFICATION . '/' . TXML_SECT_RANK;
								$checklist = array(TXML_ATTS_NAME, TXML_ATTS_CAR, TXML_ATTN_BEST_LAP_TIME,
												TXML_ATTS_MODULE, TXML_ATTN_MODULE_INDEX);
								checkarray($i, $ps, $error, $errorarray, $qualiresult[$i], $checklist);

								// Race.
								$ps = TXML_SECT_RACE1 . '/' . TXML_SECT_RANK;
								$checklist = array(TXML_ATTS_NAME, TXML_ATTS_CAR, TXML_ATTN_BEST_LAP_TIME,
												TXML_ATTS_MODULE, TXML_ATTN_MODULE_INDEX, TXML_ATTN_DAMAGE,
												TXML_ATTN_PITSTOPS, TXML_ATTN_LAPS, TXML_ATTN_TIME,
												TXML_ATTN_TOPSPEED);
								checkarray($i, $ps, $error, $errorarray, $raceresult[$i], $checklist);
							}

							if ($error == 0) {
								// Get drivers info.
								$sql = "SELECT d.name AS name, c.name AS car, t.modulename AS module FROM " .
									"$driver_tablename d, $event_team_table et, " .
									"$team_tablename t, $car_tablename c WHERE " .
									"d.teamid=et.teamid AND et.eventid=$eventid_for_db AND " .
									"t.teamid=et.teamid AND c.carid=t.carid ORDER BY d.name";
								$result = mysql_query($sql);
								if (mysql_num_rows($result) < $count) {
									$errorarray[$error] = 'Too many drivers in XML file.';
									$error++;
								}

								$i = 1;
								while ($myrow = mysql_fetch_array($result)) {
									// Seach for the name.
									$j = 1;
									while ($j <= $count && $myrow['name'] != $qualiresult[$j][TXML_ATTS_NAME]) {
										$j++;
									}
									if ($j <= $count) {
										if ($myrow['module'] != $startlist[$i][TXML_ATTS_MODULENAME] ||
											$qualiresult[$j][TXML_ATTN_MODULE_INDEX] != $startlist[$i][TXML_ATTN_START_MODULE_INDEX])
										{
											$errorarray[$error] = 'Wrong starting order, broken driver names or module name (required: ' .
																htmlentities($myrow['module']) . ', given: ' .
																$startlist[$j][TXML_ATTS_MODULENAME] . ').';
											$error++;
										} else {
											// Check if driver was as well in race.
											$k = 1;
											while ($k <= $count && $myrow['name'] != $raceresult[$k][TXML_ATTS_NAME]) {
												$k++;
											}
											if ($k > $count) {
												$errorarray[$error] = 'Driver ' . htmlentities($myrow['name']) .
																	' missing in race.';
												$error++;
											} else {
												// Check race modulename.
												if ($myrow['module'] != $raceresult[$k][TXML_ATTS_MODULE]) {
													$errorarray[$error] = 'Race module name is ' . htmlentities($raceresult[$k][TXML_ATTS_MODULE]) .
																		' but ' . htmlentities($myrow['module']) . ' is required.';
													$error++;
												}
												// Check quail modulename.
												if ($myrow['module'] != $qualiresult[$j][TXML_ATTS_MODULE]) {
													$errorarray[$error] = 'Qualification module name is ' . htmlentities($raceresult[$j][TXML_ATTS_MODULE]) .
																		' but ' . htmlentities($myrow['module']) . ' is required.';
													$error++;
												}
												// Check car in quali.
												if ($myrow['car'] != $qualiresult[$j][TXML_ATTS_CAR]) {
													$errorarray[$error] = 'Qualification car is ' . htmlentities($qualiresult[$j][TXML_ATTS_CAR]) .
																		' but ' . htmlentities($myrow['car']) . ' is required for driver ' .
																		htmlentities($myrow['name']) . ' in the qualification';
													$error++;
												}
												// Check car in race.
												if ($myrow['car'] != $raceresult[$k][TXML_ATTS_CAR]) {
													$errorarray[$error] = 'Race car is ' . htmlentities($raceresult[$k][TXML_ATTS_CAR]) .
																		' but ' . htmlentities($myrow['car']) . ' is required for driver ' .
																		htmlentities($myrow['name']) . ' in the race';
													$error++;
												}
											}
											$i++;
										}
									} else {
										$warningarray[$warning] = 'Race result without ' . $myrow['name']  . '.';
										$warning++;
									}
								}

								if ($error == 0) {
									// Puh, finally commit...
									for ($i = 1; $i <= $count; $i++) {
										// Drivername is unique, driver can just belong to one team, so this should work.
										$drivername = quoteString($raceresult[$i][TXML_ATTS_NAME]);
										// Search driver in quali.
										$qi = 1;
										while ($qi < $count && $raceresult[$i][TXML_ATTS_NAME] != $qualiresult[$qi][TXML_ATTS_NAME]) {
											$qi++;
										}

										$sql = "SELECT t.carid AS carid, t.teamid AS teamid, " .
											"d.driverid AS driverid FROM $driver_tablename d, " .
											"$team_tablename t WHERE d.name=$drivername AND " .
											"d.teamid=t.teamid";
										$result = mysql_query($sql);
										$myrow = mysql_fetch_array($result);

										$sql = "INSERT INTO $rawresult_tablename (raceid, teamid, " .
											"submitterid, driverid, carid, quali_laptime, quali_rank, " .
											"race_laptime, race_rank, race_laps, race_topspeed, " .
											"race_damage, race_pitstops, race_time) VALUES (" .
											"$raceid_for_db, " . quoteString($myrow['teamid']) . ", $uid_for_db, " .
											quoteString($myrow['driverid']) . ", " . quoteString($myrow['carid']) . ", " .
											quoteString($qualiresult[$qi][TXML_ATTN_BEST_LAP_TIME]) . ", " .
											quoteString($qi) . ", " .
											quoteString($raceresult[$i][TXML_ATTN_BEST_LAP_TIME]) . ", " .
											quoteString($i) . ", " .
											quoteString($raceresult[$i][TXML_ATTN_LAPS]) . ", " .
											quoteString($raceresult[$i][TXML_ATTN_TOPSPEED]) . ", " .
											quoteString($raceresult[$i][TXML_ATTN_DAMAGE]) . ", " .
											quoteString($raceresult[$i][TXML_ATTN_PITSTOPS]) . ", " .
											quoteString($raceresult[$i][TXML_ATTN_TIME]) . ")";
										$result = mysql_query($sql);
									}
									// Register submission.
									$sql = "INSERT INTO $submitted_tablename (raceid, submitterid, runrace) " .
										"VALUES ($raceid_for_db, $uid_for_db, 'ok')";
									$result = mysql_query($sql);
								}
							}
						} else {
							// Startlist/Quali/Race have not the equal number of robots.
							$errorarray[$error] = 'The number of drivers in the startlist, qualification or race do not match.';
							$error++;
						}
					} else {
						// Wrong track -> "hacker" error...
						$errorarray[$error] = 'Wrong track (' . htmlentities($track_row['name']) . ' expected).';
						$error++;
					}
				} else {
					// File upload problem or XML parser failed.
					$errorarray[$error] = 'File upload problem or XML parsing failed.';
					$error++;
				}
			} else {
				// File not ok.
				$errorarray[$error] = 'Wrong MIME type (submitted: ' . htmlentities($file['type']) .
									', required: text/xml) or file too big (size: ' . $file['size'] .
									', allowed: ' . ROBOT_RESULT_SIZE . ').';
				$error++;
			}
			if ($error == 0) {
				// Sucess page.
				$page->set_file('PAGE_CONTENT_T', 'event_result_submitted_ok.ihtml');
				$page->set_block('PAGE_CONTENT_T', 'warning', 'warningvar');
				$page->set_var(array(
					'PC_NB_WARNINGS'	=> ($warning == 0) ? 'no' : $warning,
					'PC_WARNING_STRING'	=> ($warning == 1) ? 'warning' : 'warnings'
				));
				for ($i = 0; $i < $warning; $i++) {
					$page->set_var(array(
						'PC_WARNING'	=> $warningarray[$i]
					));
					$page->parse('warningvar', 'warning', true);
				}
				if ($warning == 0) {
					$page->set_var('warningvar', '');
				}
			} else {
				// Error page.
				$page->set_file('PAGE_CONTENT_T', 'event_result_submitted_notok.ihtml');
				$page->set_block('PAGE_CONTENT_T', 'error', 'errorvar');
				$page->set_var(array(
					'PC_NB_ERRORS'		=> $error,
					'PC_ERROR_STRING'	=> ($error < 2) ? 'error' : 'errors',
					'PC_ADMIN_EMAIL'	=> ADMIN_EMAIL
				));
				for ($i = 0; $i < $error; $i++) {
					$page->set_var(array(
						'PC_ERROR'	=> $errorarray[$i]
					));
					$page->parse('errorvar', 'error', true);
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
