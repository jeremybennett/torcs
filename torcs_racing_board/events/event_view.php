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
	require_once($path_to_root . 'lib/functions_validate.php');
	require_once($path_to_root . 'lib/functions_event.php');
	require_once($path_to_root . 'lib/functions_points.php');
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
	$car_tablename = $db_prefix . TBL_CAR;
	$event_car_table = $db_prefix . TBL_EVENT_CAR;
	$event_team_table = $db_prefix . TBL_EVENTTEAM;
	$team_tablename = $db_prefix . TBL_TEAM;
	$race_tablename = $db_prefix . TBL_RACE;
	$track_tablename = $db_prefix . TBL_TRACK;
	$submitted_tablename = $db_prefix . TBL_RESULTSUBMITTED;
	$race_report_driver_table = $db_prefix . TBL_RACE_REPORT_DRIVER;
	$race_report_team_table = $db_prefix . TBL_RACE_REPORT_TEAM;
	$rawresult_tablename = $db_prefix . TBL_RAWRESULT;

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks the login.
	$user = new User($db, $user_tablename, $loginlog_tablename);

	// Login?
	checkLogin($user);
	// Logout?
	checkLogout();

	deleteRace($race_tablename, $race_report_driver_table, $race_report_team_table, $rawresult_tablename, $submitted_tablename);
	unregisterRobot($event_team_table, $event_tablename, $team_tablename, $path_to_root);

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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board View Event Page',
		'PB_DESCRIPTION'	=> 'View an event for the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, event, race, competition, view',
		'ROOTPATH'			=> $path_to_root
	));

	$pagecommand = isset($_GET['vieweventid']) ? "?vieweventid=" . removeMagicQuotes($_GET['vieweventid']) : '';

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
			'PS_LOGINPAGE'		=> $_SERVER['PHP_SELF'] . $pagecommand,
			'PS_HOSTNAME'		=> SERVER_NAME
		));
	}

	if (isset($_GET['vieweventid'])) {
		$eventid = intval(removeMagicQuotes($_GET['vieweventid']));
		$eventid_for_db = quoteString($eventid);
		$sql = "SELECT * FROM $event_tablename WHERE eventid=" . $eventid_for_db;
		$result = mysql_query($sql);
		if ($myrow = mysql_fetch_array($result)) {
			// TODO: Template according to user group?
			$p = getPointSystems();
			$page->set_file('PAGE_CONTENT_T', 'event_view.ihtml');

			$page->set_var(array(
				'PC_EVENT_ID'				=> $myrow['eventid'],
				'PC_EVENT_NAME'				=> htmlentities($myrow['name']),
				'PC_EVENT_DESCRIPTION'		=> htmlentities($myrow['description']),
				'PC_EVENT_SIGNIN_START'		=> htmlentities($myrow['signin_start']),
				'PC_EVENT_SIGNIN_END'		=> htmlentities($myrow['signin_end']),
				'PC_EVENT_START'			=> htmlentities($myrow['startdate']),
				'PC_EVENT_END'				=> htmlentities($myrow['enddate']),
				'PC_EVENT_MAXTEAMS'			=> $myrow['maxteams'],
				'PC_EVENT_POINTSYSTEM_NAME'	=> htmlentities($p[$myrow['pointsystem']])
			));

			// Variables used below.
			$teams_max = intval($myrow['maxteams']);
			$registertimeframe = false;
			$ct = time();
			$time1 = strtotime($myrow['signin_start']) - $ct;
			$time2 = strtotime($myrow['signin_end']) - $ct;
			if ($time1 <= 0 && $time2 >= 0) {
				$registertimeframe = true;
			}

			$uid_for_db = quoteString(intval($_SESSION['uid']));
			$has_team = FALSE;
			if ($_SESSION['usergroup'] == 'racer') {
				$has_team = hasUserTeamOnEvent($event_team_table, $team_tablename, $eventid_for_db, $uid_for_db);
			}

			// Allowed car list.
			$page->set_block("PAGE_CONTENT_T", "carlist", "carlistrows");
			$sql = "SELECT c.name AS name, c.carid AS carid FROM $event_car_table ec, $car_tablename c WHERE ec.eventid=" .
				   $eventid_for_db . " AND ec.carid=c.carid ORDER BY name ASC";
			$result = mysql_query($sql);
			$sep = '';
			while ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_EVENT_CAR_ID'	=> $myrow['carid'],
					'PC_EVENT_CAR_NAME'	=> htmlentities($myrow['name']),
					'PC_EVENT_CAR_SEP'	=> $sep
				));
				$page->parse("carlistrows", "carlist", true);
				$sep =', ';
			}

			// Registered teams.
			$page->set_block("PAGE_CONTENT_T", "teamlist", "teamlistrows");
			$sql = "SELECT t.name AS name, t.teamid AS teamid FROM $event_team_table et, $team_tablename t WHERE et.eventid=" .
				   $eventid_for_db . " AND et.teamid=t.teamid";
			$result = mysql_query($sql);

			$teams_registered = intval(mysql_num_rows($result));
			$teams_left = intval($teams_max) - $teams_registered;
			$page->set_var(array(
				'PC_EVENT_FREE_TEAMS'		=> $teams_left,
				'PC_EVENT_REGISTERED_TEAMS'	=> $teams_registered
			));

			$sep = '';
			$fetched_rows = 0;
			while ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_EVENT_TEAM_ID'		=> $myrow['teamid'],
					'PC_EVENT_TEAM_NAME'	=> htmlentities($myrow['name']),
					'PC_EVENT_TEAM_SEP'		=> $sep
				));
				$page->parse("teamlistrows", "teamlist", true);
				$sep =', ';
				$fetched_rows++;
			}

			if ($fetched_rows == 0) {
				$page->set_var("teamlistrows", "None");
			}

			// Races.
			$lastdoneraceid = -1;
			$page->set_block("PAGE_CONTENT_T", "racelist", "racelistrows");
			$page->set_block("racelist", "raceadmin", "raceadminvar");
			$page->set_block("racelist", "raceresult", "raceresultvar");

			$sql = "SELECT t.name AS name, t.trackid AS trackid, r.robot_submission_start AS robbegin, " .
				   "r.robot_submission_end AS robend, r.result_submission_start AS resbegin, " .
				   "r.result_submission_end AS resend, r.raceid AS raceid " .
				   "FROM $race_tablename r, $track_tablename t WHERE r.eventid=" .
				   $eventid_for_db . " AND r.trackid=t.trackid ORDER BY r.robot_submission_start ASC";
			$result = mysql_query($sql);

			$fetched_rows = 0;
			while ($myrow = mysql_fetch_array($result)) {

				$ct = time();
				$time1 = strtotime($myrow['robbegin']) - $ct;
				$time2 = strtotime($myrow['robend']) - $ct;
				$time3 = strtotime($myrow['resbegin']) - $ct;
				$time4 = strtotime($myrow['resend']) - $ct;

				$showstandings = false;
				if ($time4 < 0) {
					// All over.
					$color = 'e8e8e8';
					$state = 'Done';
					$showstandings = true;
					$lastdoneraceid = $myrow['raceid'];
				} elseif ($time3 < 0) {
					// Result submission.
					$color = 'e8a8a8';
					if ($_SESSION['usergroup'] == 'racer' &&
						$has_team &&
						!hasUserSubmittedRaceresult($submitted_tablename, quoteString($myrow['raceid']), $uid_for_db))
					{
						$state = '<a href="' . $path_to_root . 'events/event_submit_result.php?eventid=' .
								 $eventid . '&raceid=' . intval($myrow['raceid']) . '" title="Download the Robots/Run the Race/Submit Result">Racing/Result Submission</a>';
					} else {
						$state = 'Racing/Result Submission';
					}
				} elseif ($time2 < 0) {
					// Run the race.
					$color = 'e8c8a8';
					if ($_SESSION['usergroup'] == 'racer' &&
						$has_team &&
						!hasUserSubmittedRaceresult($submitted_tablename, quoteString($myrow['raceid']), $uid_for_db))
					{
						$state = '<a href="' . $path_to_root . 'events/event_submit_result.php?eventid=' .
								 $eventid . '&raceid=' . intval($myrow['raceid']) . '">Run the race</a>';
					} else {
						$state = 'Run races';
					}
				} elseif ($time1 < 0) {
					// Robot submission.
					$color = 'e8e8a8';
					if ($_SESSION['usergroup'] == 'racer') {
						$state = '<a href="' . $path_to_root . 'events/event_submit_robot.php?eventid=' .
								 $eventid . '&raceid=' . intval($myrow['raceid']) . '">Robot Submission</a>';
					} else {
						$state = 'Robot Submission';
					}
				} else {
					// Race is in the future.
					$color = 'a8e8a8';
					$state = 'Upcoming';
				}

				$page->set_var(array(
					'PC_EVENT_TRACK_ID'				=> $myrow['trackid'],
					'PC_EVENT_TRACK_NAME'			=> htmlentities($myrow['name']),
					'PC_EVENT_RACE_ROBOT_BEGIN'		=> htmlentities($myrow['robbegin']),
					'PC_EVENT_RACE_ROBOT_END'		=> htmlentities($myrow['robend']),
					'PC_EVENT_RACE_RESULT_BEGIN'	=> htmlentities($myrow['resbegin']),
					'PC_EVENT_RACE_RESULT_END'		=> htmlentities($myrow['resend']),
					'PC_RACE_ID'					=> $myrow['raceid'],
					'PC_RACE_STATE'					=> $state,
					'PC_RACE_STATE_COLOR'			=> $color
				));

				if ($showstandings) {
					$page->parse("raceresultvar", "raceresult");
				} else {
					$page->set_var("raceresult", "");
					$page->parse("raceresultvar", "raceresult");
				}

				if ($_SESSION['usergroup'] == 'admin') {
					$page->parse("raceadminvar", "raceadmin");
				} else {
					$page->set_var("raceadmin", "");
					$page->parse("raceadminvar", "raceadmin");

				}

				$page->parse("racelistrows", "racelist", true);
				$sep =', ';
				$fetched_rows++;
			}

			if ($fetched_rows == 0) {
				$page->set_var("racelistrows", "None");
			}

			// Admin only functions.
			$page->set_block("PAGE_CONTENT_T", "admin", "adminvar");
			if ($_SESSION['usergroup'] == 'admin') {
				//$page->set_var(array(
				//));
				$page->parse("adminvar", "admin");
			} else {
				$page->set_var("adminvar", "");
			}

			// Racer only functions.
			$page->set_block("PAGE_CONTENT_T", "racer", "racervar");
			$page->set_block("racer", "raceteamadd", "raceteamaddvar");
			$page->set_block("racer", "raceteamremove", "raceteamremovevar");

			if ($_SESSION['usergroup'] == 'racer') {
				// List possible teams to sign in.
				$sql = "SELECT t.name AS name, t.teamid AS teamid FROM $event_car_table ec, $team_tablename t LEFT JOIN " .
					   "$event_team_table et ON (t.teamid=et.teamid AND et.eventid=$eventid_for_db) WHERE " .
					   "ec.eventid=$eventid_for_db AND ec.carid=t.carid AND t.owner=" . quoteString(intval($_SESSION['uid'])) . " " .
					   "AND (et.eventid!=$eventid_for_db OR isnull(et.eventid))";
				$result = mysql_query($sql);
				$fetched_rows = 0;
				while ($myrow = mysql_fetch_array($result)) {
					$page->set_var(array(
						'PC_TEAM_ID'	=> intval($myrow['teamid']),
						'PC_TEAM_NAME'	=> htmlentities($myrow['name'])
					));
					$page->parse("raceteamaddvar", "raceteamadd", true);
					$fetched_rows++;
				}
				if ($fetched_rows == 0) {
					$page->set_var("raceteamaddvar", "None of your unassigned teams fit.");
				}
				if (!$registertimeframe) {
					$page->set_var("raceteamaddvar", "Event is not in register phase.");
				}
				if ($teams_left < 1) {
					$page->set_var("raceteamaddvar", "No more teams allowed.");
				}

				$page->parse("racervar", "racer");

				// List possible team to sign out.
				$sql = "SELECT t.name AS name, t.teamid AS teamid FROM $team_tablename t, " .
					   "$event_team_table et WHERE " .
					   "et.eventid=$eventid_for_db AND t.owner=" . quoteString(intval($_SESSION['uid'])) .
					   " AND et.teamid=t.teamid";
				$result = mysql_query($sql);
				$fetched_rows = 0;
				while ($myrow = mysql_fetch_array($result)) {
					$page->set_var(array(
						'PC_TEAM_ID'	=> intval($myrow['teamid']),
						'PC_TEAM_NAME'	=> htmlentities($myrow['name'])
					));
					$page->parse("raceteamremovevar", "raceteamremove", true);
					$fetched_rows++;
				}
				if ($fetched_rows == 0) {
					$page->set_var("raceteamremovevar", "You have no teams registered.");
				}
				if (!$registertimeframe) {
					$page->set_var("raceteamremovevar", "Event is not in register phase.");
				}

				$page->parse("racervar", "racer");
			} else {
				$page->set_var("racervar", "");
			}

			// Standings.
			$page->set_block("PAGE_CONTENT_T", "standings", "standingsvar");
			if ($lastdoneraceid > -1) {
				$page->set_var(array(
					'PC_RACE_ID'	=> $lastdoneraceid
				));
				$page->parse("standingsvar", "standings");
			} else {
				$page->set_var("standingsvar", "");
			}
			// TODO: show next step for the user.
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
