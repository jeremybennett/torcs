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
	require_once($path_to_root . 'lib/functions_team.php');

	if (!isset($_SESSION['uid']) ) {
		session_defaults();
	}

	$db = mysql_connect($db_host, $db_user, $db_passwd) or die;
	mysql_select_db($db_name, $db) or die;
	$user_tablename = $db_prefix . TBL_USERS;
	$forum_tablename = $db_prefix . TBL_FORUM;
	$topic_tablename = $db_prefix . TBL_FORUM_TOPICDATA;
	$stats_hitcount_tablename = $db_prefix . TBL_HITCOUNT;
	$stats_sessioncount_tablename = $db_prefix . TBL_SESSIONCOUNT;
	$stats_tablename = $db_prefix . TBL_STATS;
	$loginlog_tablename = $db_prefix . TBL_LOGIN_LOG;
	$team_tablename = $db_prefix . TBL_TEAM;
	$driver_tablename = $db_prefix . TBL_DRIVER;
	$car_tablename = $db_prefix . TBL_CAR;

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
		if (createTeamAllowed($team_tablename)/*$_SESSION['usergroup'] == 'racer'*/) {
			if (isset($_POST['team_submit'])) {
				if ($formerrors = checkTeamInput($team_tablename, $car_tablename, $driver_tablename, FALSE)) {
					// Errors.
					$page_content = 'team_create.ihtml';
				} else {
					$formerrors = commitTeamInput($team_tablename, $driver_tablename, $path_to_root);
					if ($formerrors != 0) {
						// Commit failed.
						$page_content = 'team_create.ihtml';
					} else {
						$page_content = 'team_create_ok.ihtml';
					}
				}
			} else {
				$page_content = 'team_create.ihtml';
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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Team Creation Page',
		'PB_DESCRIPTION'	=> 'Create a team on the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, team, create',
		'ROOTPATH'			=> $path_to_root
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		$page->set_var(array(
			'PS_USERNAME'			=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'		=> $_SESSION['usergroup'],
			'PS_IPADSRESS'			=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'			=> $path_to_root . 'index.php',
			'PC_CREATETEAMPAGE'		=> $_SERVER['PHP_SELF']
		));

		if (isset($_POST['team_submit']) && $formerrors > 0) {
			$page->set_var(array(
				'PC_TEAM_NAME'			=> isset($_POST['team_name']) ? htmlentities(removeMagicQuotes($_POST['team_name'])) : '',
				'PC_TEAM_DESCRIPTION'	=> isset($_POST['team_description']) ? htmlentities(removeMagicQuotes($_POST['team_description'])) : '',
				'PC_TEAM_MODULE'		=> isset($_POST['team_modulename']) ? htmlentities(removeMagicQuotes($_POST['team_modulename'])) : '',
				'PC_TEAM_DRIVERNAME1'	=> isset($_POST['team_driver1_name']) ? htmlentities(removeMagicQuotes($_POST['team_driver1_name'])) : '',
				'PC_TEAM_DRIVERNAME2'	=> isset($_POST['team_driver2_name']) ? htmlentities(removeMagicQuotes($_POST['team_driver2_name'])) : '',
				'PC_COLOR_DESCRIPTION'	=> COLOR_TB1
			));
			// Check team name.
			$errmsg = '';
			if (isTeamNameOk($formerrors, $errmsg)) {
				$page->set_var(array(
					'PC_NAME_ERROR'			=> '',
					'PC_COLOR_NAME'			=> COLOR_TB1
				));
			} else {
				$page->set_var(array(
					'PC_NAME_ERROR'			=> $errmsg,
					'PC_COLOR_NAME'			=> COLOR_TB_ERR,
				));
			}

			if (isTeamModuleNameOk($formerrors, $errmsg)) {
				$page->set_var(array(
					'PC_MODULENAME_ERROR'	=> '',
					'PC_COLOR_MODULENAME'	=> COLOR_TB2
				));
			} else {
				$page->set_var(array(
					'PC_MODULENAME_ERROR'	=> $errmsg,
					'PC_COLOR_MODULENAME'	=> COLOR_TB_ERR,
				));
			}

			if (isTeamDriver1Ok($formerrors, $errmsg)) {
				$page->set_var(array(
					'PC_DRIVERNAME1_ERROR'	=> '',
					'PC_COLOR_DRIVER1'		=> COLOR_TB1
				));
			} else {
				$page->set_var(array(
					'PC_DRIVERNAME1_ERROR'	=> $errmsg,
					'PC_COLOR_DRIVER1'		=> COLOR_TB_ERR,
				));
			}

			if (isTeamDriver2Ok($formerrors, $errmsg)) {
				$page->set_var(array(
					'PC_DRIVERNAME2_ERROR'	=> '',
					'PC_COLOR_DRIVER2'		=> COLOR_TB2
				));
			} else {
				$page->set_var(array(
					'PC_DRIVERNAME2_ERROR'	=> $errmsg,
					'PC_COLOR_DRIVER2'		=> COLOR_TB_ERR,
				));
			}

			if (isTeamBasenumberOk($formerrors, $errmsg)) {
				$page->set_var(array(
					'PC_RACENUMBER_ERROR'	=> '',
					'PC_COLOR_RACENUMBER'	=> COLOR_TB1
				));
			} else {
				$page->set_var(array(
					'PC_RACENUMBER_ERROR'	=> $errmsg,
					'PC_COLOR_RACENUMBER'	=> COLOR_TB_ERR,
				));
			}

			if (isTeamCarOk($formerrors, $errmsg)) {
				$page->set_var(array(
					'PC_CAR_ERROR'			=> '',
					'PC_COLOR_CAR'			=> COLOR_TB2
				));
			} else {
				$page->set_var(array(
					'PC_CAR_ERROR'			=> $errmsg,
					'PC_COLOR_CAR'			=> COLOR_TB_ERR,
				));
			}


		} else {
			$page->set_var(array(
				'PC_TEAM_NAME'			=> '',
				'PC_TEAM_DESCRIPTION'	=> '',
				'PC_TEAM_MODULE'		=> '',
				'PC_TEAM_DRIVERNAME1'	=> '',
				'PC_TEAM_DRIVERNAME2'	=> '',
				'PC_NAME_ERROR'			=> '',
				'PC_CAR_ERROR'			=> '',
				'PC_MODULENAME_ERROR'	=> 'without suffix, e.g. test_2004',
				'PC_DRIVERNAME1_ERROR'	=> 'e. g. test 2004 1',
				'PC_DRIVERNAME2_ERROR'	=> 'e. g. test 2004 2',
				'PC_RACENUMBER_ERROR'	=> '',
				'PC_COLOR_NAME'			=> COLOR_TB1,
				'PC_COLOR_CAR'			=> COLOR_TB2,
				'PC_COLOR_MODULENAME'	=> COLOR_TB2,
				'PC_COLOR_DRIVER1'		=> COLOR_TB1,
				'PC_COLOR_DRIVER2'		=> COLOR_TB2,
				'PC_COLOR_RACENUMBER'	=> COLOR_TB1,
				'PC_COLOR_DESCRIPTION'	=> COLOR_TB1
			));
		}

		if ($page_content == 'team_create.ihtml') {
			// Fill in drop down list with cars.
			$page->set_block("PAGE_CONTENT_T", "row", "rows");
			$sql = "SELECT * FROM $car_tablename";
			$result = mysql_query($sql);
			while ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_TEAM_CAR_SEL'	=> (isset($_POST['team_car_id']) && (removeMagicQuotes($_POST['team_car_id']) == $myrow['carid'])) ? 'selected' : '',
					'PC_TEAM_CAR_ID'	=> $myrow['carid'],
					'PC_TEAM_CAR_NAME'	=> htmlentities($myrow['name'])
				));
				$page->parse("rows", "row", true);
			}

			// Fill in drop down list with cars.
			$page->set_block("PAGE_CONTENT_T", "racenumber_row", "racenumber_rows");
			$sql = "SELECT racenumber FROM $driver_tablename WHERE (racenumber % 2 = 1) ORDER BY racenumber ASC";
			$result = mysql_query($sql);
			$currentnumber = 0;
			if ($myrow = mysql_fetch_array($result)) {
				$currentnumber = $myrow['racenumber'];
			}
			for ($i = 1; $i < 998; $i += 2) {
				// Number already gone?
				if ($currentnumber == $i) {
					// Yes.
					if ($myrow = mysql_fetch_array($result)) {
						$currentnumber = $myrow['racenumber'];
					}
				} else {
					$page->set_var(array(
						'PC_TEAM_RN_SEL'	=> (isset($_POST['team_base_number']) && (removeMagicQuotes($_POST['team_base_number']) == $i)) ? 'selected' : '',
						'PC_TEAM_RN'		=> $i,
					));
					$page->parse("racenumber_rows", "racenumber_row", true);
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
