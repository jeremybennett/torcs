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

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks the login.
	$user = new User($db, $user_tablename, $loginlog_tablename);

	// Login?
	checkLogin($user);
	// Logout?
	checkLogout();


	$formerrors = intval(0);

	if ($_SESSION['logged'] == TRUE) {
		// Login template for statusbar.
		$page_statusbar = 'page_statusbar_logged_in.ihtml';
		if ($_SESSION['usergroup'] == 'admin' &&
			(isset($_POST['event_submit']) || isset($_GET['editeventid'])))
		{
			if (isset($_POST['event_submit'])) {
				if ($formerrors = checkEventInput()) {
					// Errors.
					$page_content = 'admin_event_edit.ihtml';
				} else {
					updateEventInput($event_tablename, $event_car_table, $path_to_root);
					// Add races...
					$page_content = 'admin_event_create_ok.ihtml';
				}
			} else {
				$page_content = 'admin_event_edit.ihtml';
			}
		} else {
			$page_content = 'admin_no_access.ihtml';
		}
	} else {
		// Status view template for statusbar.
		$page_statusbar = 'page_statusbar.ihtml';
		$page_content = 'admin_no_access.ihtml';
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
		'PAGE_CONTENT_T'	=> $page_content,
		'PAGE_FOOTER_T'		=> 'page_footer.ihtml',
		'PAGE_END_T'		=> 'page_end.ihtml'
	));

	// Set up page header.
	$page->set_var(array(
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Edit Event Page',
		'PB_DESCRIPTION'	=> 'Edit an event for the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, event, race, edit',
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

		if ($_SESSION['usergroup'] == 'admin' && $page_content == 'admin_event_edit.ihtml') {

			$sql = "SELECT * FROM $car_tablename";
			$result = mysql_query($sql);

			if (isset($_POST['event_submit']) && $formerrors > 0 && isset($_POST['event_id'])) {

				$page->set_block("PAGE_CONTENT_T", "row", "rows");
				$page->set_block("PAGE_CONTENT_T", "maxtrow", "maxtrows");
				$page->set_block("PAGE_CONTENT_T", "pointsrow", "pointsrows");

				$page->set_var(array(
					'PC_EVENT_ID'			=> intval(removeMagicQuotes($_POST['event_id'])),
					'PC_EVENT_NAME'			=> isset($_POST['event_name']) ? htmlentities(removeMagicQuotes($_POST['event_name'])) : "",
					'PC_EVENT_DESCRIPTION'	=> isset($_POST['event_description']) ? htmlentities(removeMagicQuotes($_POST['event_description'])) : "",
					'PC_EVENT_SIGNIN_START'	=> isset($_POST['event_signin_start']) ? htmlentities(removeMagicQuotes($_POST['event_signin_start'])) : "",
					'PC_EVENT_SIGNIN_END'	=> isset($_POST['event_signin_end']) ? htmlentities(removeMagicQuotes($_POST['event_signin_end'])) : "",
					'PC_EVENT_START'		=> isset($_POST['event_start']) ? htmlentities(removeMagicQuotes($_POST['event_start'])) : "",
					'PC_EVENT_END'			=> isset($_POST['event_end']) ? htmlentities(removeMagicQuotes($_POST['event_end'])) : "",
				));

				while ($myrow = mysql_fetch_array($result)) {
					if (isset($_POST['event_cars'])) {
						$page->set_var(array(
							'PC_EVENT_CAR_SEL'	=> (array_search($myrow['carid'], $_POST['event_cars']) !== FALSE) ? 'selected' : "",
						));
					} else {
						$page->set_var(array(
							'PC_EVENT_CAR_SEL'	=> "",
						));
					}
					$page->set_var(array(
						'PC_EVENT_CAR_ID'	=> $myrow['carid'],
						'PC_EVENT_CAR_NAME'	=> htmlentities($myrow['name'])
					));
					$page->parse("rows", "row", true);
				}

				for ($i = 2; $i <= TEAMS_PER_EVENT; $i++) {
					$page->set_var(array(
						'PC_EVENT_MAXTEAM_SEL'	=> (isset($_POST['event_maxteams']) && $i == intval(removeMagicQuotes($_POST['event_maxteams']))) ? 'selected' : "",
						'PC_EVENT_MAXTEAM_NB'	=> $i
					));
					$page->parse("maxtrows", "maxtrow", true);
				}

				$p = getPointSystems();
				for ($i = 0; $i < count($p); $i++) {
					$page->set_var(array(
						'PC_EVENT_POINTSYSTEM_SEL'		=> (isset($_POST['event_pointsystem']) && $i == intval(removeMagicQuotes($_POST['event_pointsystem']))) ? 'selected' : "",
						'PC_EVENT_POINTSYSTEM_NB'		=> $i,
						'PC_EVENT_POINTSYSTEM_NAME'		=> $p[$i]
					));
					$page->parse("pointsrows", "pointsrow", true);
				}


			} elseif (isset($_GET['editeventid'])) {
				$id_for_db = quoteString(intval(removeMagicQuotes($_GET['editeventid'])));
				$sql = "SELECT * FROM $event_tablename WHERE eventid=" . $id_for_db;
				$eresult = mysql_query($sql);
				if ($emyrow = mysql_fetch_array($eresult)) {

					$page->set_block("PAGE_CONTENT_T", "row", "rows");
					$page->set_block("PAGE_CONTENT_T", "maxtrow", "maxtrows");
					$page->set_block("PAGE_CONTENT_T", "pointsrow", "pointsrows");

					$page->set_var(array(
						'PC_EVENT_ID'			=> $emyrow['eventid'],
						'PC_EVENT_NAME'			=> htmlentities($emyrow['name']),
						'PC_EVENT_DESCRIPTION'	=> htmlentities($emyrow['description']),
						'PC_EVENT_SIGNIN_START'	=> htmlentities($emyrow['signin_start']),
						'PC_EVENT_SIGNIN_END'	=> htmlentities($emyrow['signin_end']),
						'PC_EVENT_START'		=> htmlentities($emyrow['startdate']),
						'PC_EVENT_END'			=> htmlentities($emyrow['enddate'])
					));

					// Query the allowed cars.
					$sql = "SELECT * FROM $event_car_table WHERE eventid=" . $id_for_db . " ORDER BY carid ASC";
					$cresult = mysql_query($sql);
					$nextmatch = mysql_fetch_array($cresult);

					while ($myrow = mysql_fetch_array($result)) {
						$sel = '';
						if ($nextmatch && $nextmatch['carid'] == $myrow['carid']) {
							$sel = 'selected';
							$nextmatch = mysql_fetch_array($cresult);
						}

						$page->set_var(array(
							'PC_EVENT_CAR_SEL'	=> $sel,
							'PC_EVENT_CAR_ID'	=> $myrow['carid'],
							'PC_EVENT_CAR_NAME'	=> htmlentities($myrow['name'])
						));
						$page->parse("rows", "row", true);
					}

					for ($i = 2; $i <= TEAMS_PER_EVENT; $i++) {
						$page->set_var(array(
							'PC_EVENT_MAXTEAM_SEL'	=> (intval($emyrow['maxteams']) == $i) ? 'selected' : "",
							'PC_EVENT_MAXTEAM_NB'	=> $i
						));
						$page->parse("maxtrows", "maxtrow", true);
					}

					$p = getPointSystems();
					for ($i = 0; $i < count($p); $i++) {
						$page->set_var(array(
							'PC_EVENT_POINTSYSTEM_SEL'		=> (intval($emyrow['pointsystem']) == $i) ? 'selected' : "",
							'PC_EVENT_POINTSYSTEM_NB'		=> $i,
							'PC_EVENT_POINTSYSTEM_NAME'		=> $p[$i]
						));
						$page->parse("pointsrows", "pointsrow", true);
					}
				} else {
					$page->set_file('PAGE_CONTENT_T', 'admin_no_access.ihtml');
				}
			}
		}
	} else {
		// Variables if NOT logged in.
		$page->set_var(array(
			'PS_PASSWORD_SIZE'	=> MAX_USERNAME_LENGTH,
			'PS_USERNAME_SIZE'	=> MAX_USERNAME_LENGTH,
			'PS_LOGINPAGE'		=> $_SERVER['PHP_SELF'],
			'PS_HOSTNAME'		=> SERVER_NAME
		));
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
