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
	require_once($path_to_root . 'lib/functions_images.php');
	require_once($path_to_root . 'lib/functions_validate.php');
	require_once($path_to_root . 'lib/functions_team.php');

	if (!isset($_SESSION['uid'])) {
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
	$signed_tablename = $db_prefix . TBL_EVENTTEAM;
	$event_tablename = $db_prefix . TBL_EVENT;

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks the login.
	$user = new User($db, $user_tablename, $loginlog_tablename);

	// Login?
	checkLogin($user);
	// Logout?
	checkLogout();

	$formerrors = intval(0);
	$inrace = TRUE;

	if ($_SESSION['logged'] == TRUE) {
		// Login template for statusbar.
		$page_statusbar = 'page_statusbar_logged_in.ihtml';
		if (editTeamAllowed($team_tablename) == TRUE) {
			$inrace = isTeamSignedInRace($signed_tablename, $event_tablename);

			if (isset($_POST['team_logo_image_submit'])) {
				commitJPEGImage(
					intval(removeMagicQuotes($_GET['editteamid'])), $path_to_root,
					'team_logo_image', 15000, 'images/teams/logo/', 124, 84, 74, 50, 90
				);
			}

			if (isset($_POST['team_flag_image_submit'])) {
				commitJPEGImage(
					intval(removeMagicQuotes($_GET['editteamid'])), $path_to_root,
					'team_flag_image', 10000, 'images/teams/flag/', 124, 84, 74, 50, 90
				);
			}

			if (isset($_POST['team_shot1_image_submit'])) {
				commitJPEGImage(
					intval(removeMagicQuotes($_GET['editteamid'])), $path_to_root,
					'team_shot1_image', 15000, 'images/teams/shot1/', 300, 180, 83, 50, 90
				);
			}

			if (isset($_POST['team_shot2_image_submit'])) {
				commitJPEGImage(
					intval(removeMagicQuotes($_GET['editteamid'])), $path_to_root,
					'team_shot2_image', 15000, 'images/teams/shot2/', 300, 180, 83, 50, 90
				);
			}

			if (isset($_POST['team_edit_submit_full']) && ($inrace == FALSE)) {
				if ($formerrors = checkTeamInput($team_tablename, $car_tablename, $driver_tablename, TRUE)) {
					// Errors.
					$page_content = 'team_edit_full.ihtml';
				} else {
					$formerrors = commitEditTeamInput($team_tablename, $driver_tablename, $path_to_root);
					if ($formerrors != 0) {
						// Commit failed.
						$page_content = 'team_edit_full.ihtml';
					} else {
						$page_content = 'team_create_ok.ihtml';
					}
				}
			} else if (isset($_POST['team_edit_submit_inrace'])) {
				//if ($formerrors = checkEditTeamInput($team_tablename, $car_tablename, $driver_tablename)) {
				if ($formerrors = checkTeamInput($team_tablename, $car_tablename, $driver_tablename, TRUE)) {
					// Errors.
					$page_content = 'team_edit_inrace.ihtml';
				} else {
					$formerrors = commitEditTeamInputInrace($team_tablename);
					if ($formerrors != 0) {
						// Commit failed.
						$page_content = 'team_edit_inrace.ihtml';
					} else {
						$page_content = 'team_create_ok.ihtml';
					}
				}
			} else if ($inrace == FALSE) {
				$page_content = 'team_edit_full.ihtml';
			} else {
				$page_content = 'team_edit_inrace.ihtml';
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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Team Edit Page',
		'PB_DESCRIPTION'	=> 'Edit a team on the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, team, create, edit',
		'ROOTPATH'			=> $path_to_root
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		$page->set_var(array(
			'PS_USERNAME'			=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'		=> $_SESSION['usergroup'],
			'PS_IPADSRESS'			=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'			=> $path_to_root . 'index.php',
			'PC_EDITTEAMPAGE'		=> $_SERVER['PHP_SELF']
		));

		$teamid = 0;
		if ((isset($_POST['team_edit_submit_full']) || isset($_POST['team_edit_submit_inrace'])) /*&& $formerrors > 0*/) {
			$teamid = intval(removeMagicQuotes($_POST['editteamid']));
			$page->set_var(array(
				'PC_TEAM_ID'			=> $teamid,
				'PC_TEAM_NAME'			=> isset($_POST['team_name']) ? htmlentities(removeMagicQuotes($_POST['team_name'])) : '',
				'PC_TEAM_DESCRIPTION'	=> isset($_POST['team_description']) ? htmlentities(removeMagicQuotes($_POST['team_description'])) : '',
				'PC_TEAM_MODULE'		=> isset($_POST['team_modulename']) ? htmlentities(removeMagicQuotes($_POST['team_modulename'])) : '',
				'PC_TEAM_DRIVERNAME1'	=> isset($_POST['team_driver1_name']) ? htmlentities(removeMagicQuotes($_POST['team_driver1_name'])) : '',
				'PC_TEAM_DRIVERNAME2'	=> isset($_POST['team_driver2_name']) ? htmlentities(removeMagicQuotes($_POST['team_driver2_name'])) : '',
				'PC_COLOR_DESCRIPTION'	=> COLOR_TB1,
				'PC_TEAM_DRIVER1_ID'	=> htmlentities($_POST['driver_id_1']),
				'PC_TEAM_DRIVER2_ID'	=> htmlentities($_POST['driver_id_2']),
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
		} else if (isset($_GET['editteamid'])) {
			// Get data from db.
			$teamid = intval(removeMagicQuotes($_GET['editteamid']));
			$teamid_for_db = quoteString($teamid);
			// Get team data.
			$sql = "SELECT * FROM $team_tablename WHERE teamid=$teamid_for_db";
			$result_team = mysql_query($sql);
			if (mysql_num_rows($result_team) == 1) {
				// Ok, team exists.
				$sql = "SELECT * FROM $driver_tablename WHERE teamid=$teamid_for_db ORDER BY racenumber ASC";
				$result_drivers = mysql_query($sql);
				if (mysql_num_rows($result_drivers) == 2) {
					// Ok, drivers as well.
					$data_team = mysql_fetch_array($result_team);
					$data_drv1 = mysql_fetch_array($result_drivers);
					$data_drv2 = mysql_fetch_array($result_drivers);

					$page->set_var(array(
						'PC_TEAM_ID'			=> $teamid,
						'PC_TEAM_NAME'			=> htmlentities($data_team['name']),
						'PC_TEAM_DESCRIPTION'	=> htmlentities($data_team['description']),
						'PC_TEAM_MODULE'		=> htmlentities($data_team['modulename']),
						'PC_TEAM_DRIVER1_ID'	=> htmlentities($data_drv1['driverid']),
						'PC_TEAM_DRIVERNAME1'	=> htmlentities($data_drv1['name']),
						'PC_TEAM_DRIVER2_ID'	=> htmlentities($data_drv2['driverid']),
						'PC_TEAM_DRIVERNAME2'	=> htmlentities($data_drv2['name']),
						'PC_NAME_ERROR'			=> '',
						'PC_CAR_ERROR'			=> '',
						'PC_MODULENAME_ERROR'	=> 'without suffix, e.g. test_2004',
						'PC_DRIVERNAME1_ERROR'	=> 'e.g. test 2004 1',
						'PC_DRIVERNAME2_ERROR'	=> 'e.g. test 2004 2',
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
			}
		}

		if (isset($_POST['team_car_id'])) {
			$cmp_car_id = intval(removeMagicQuotes($_POST['team_car_id']));
		} else if (isset($data_team['carid'])) {
			$cmp_car_id = $data_team['carid'];
		}

		if (isset($_POST['team_base_number'])) {
			$cmp_base_nb = intval(removeMagicQuotes($_POST['team_base_number']));
		} else if (isset($data_drv1['racenumber'])) {
			$cmp_base_nb = $data_drv1['racenumber'];
		}

		if ($page_content == 'team_edit_full.ihtml') {
			// Fill in drop down list with cars.
			$page->set_block("PAGE_CONTENT_T", "row", "rows");
			$sql = "SELECT * FROM $car_tablename";
			$result = mysql_query($sql);
			while ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_TEAM_CAR_SEL'	=> ($cmp_car_id == $myrow['carid']) ? 'selected' : '',
					'PC_TEAM_CAR_ID'	=> $myrow['carid'],
					'PC_TEAM_CAR_NAME'	=> htmlentities($myrow['name'])
				));
				$page->parse("rows", "row", true);
			}

			// Fill in drop down list with cars.
			$page->set_block("PAGE_CONTENT_T", "racenumber_row", "racenumber_rows");
			$racenb_for_db = quoteString($cmp_base_nb);
			$sql = "SELECT racenumber FROM $driver_tablename WHERE (racenumber % 2 = 1) " .
				   //"AND (racenumber != $racenb_for_db) AND (teamid != " . quoteString($teamid) .
				   "AND (teamid != " . quoteString($teamid) .
				   ") ORDER BY racenumber ASC";
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
						'PC_TEAM_RN_SEL'	=> ($cmp_base_nb == $i) ? 'selected' : '',
						'PC_TEAM_RN'		=> $i,
					));
					$page->parse("racenumber_rows", "racenumber_row", true);
				}
			}

		} else if ($page_content == 'team_edit_inrace.ihtml') {
			$sql = "SELECT * FROM $car_tablename WHERE carid=" . quoteString($cmp_car_id);
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_TEAM_CAR_NAME'	=> htmlentities($myrow['name']),
					'PC_TEAM_CAR_ID'	=> $myrow['carid']
				));
			} else {
				$page->set_var(array(
					'PC_TEAM_CAR_NAME'	=> 'ERROR, NO CAR',
					'PC_TEAM_CAR_ID'	=> 'ERROR, NO CAR'
				));
			}
			$page->set_var(array(
				'PC_TEAM_RN'	=> $cmp_base_nb,
			));
		}

		if (($page_content == 'team_edit_full.ihtml' ||
			$page_content == 'team_edit_inrace.ihtml') &&
			isset($_GET['editteamid']))
		{
			$teamid = intval(removeMagicQuotes($_GET['editteamid']));

			// show team logo image thumbnail if available.
			$page->set_block('PAGE_CONTENT_T', 'logoimage', 'logoimagevar');
			$relpath = $path_to_root . 'images/teams/logo/' . $teamid . '_tn.jpg';
			$imagepath = getcwd() . '/' . $relpath;
			if (file_exists($imagepath)) {
				$page->set_var('PC_TEAM_LOGO_IMG', $relpath);
				$page->parse('logoimagevar', 'logoimage');
			} else {
				$page->set_var('logoimagevar', '');
			}

			// show flag thumbnail if available.
			$page->set_block('PAGE_CONTENT_T', 'flagimage', 'flagimagevar');
			$relpath = $path_to_root . 'images/teams/flag/' . $teamid . '_tn.jpg';
			$imagepath = getcwd() . '/' . $relpath;
			if (file_exists($imagepath)) {
				$page->set_var('PC_TEAM_FLAG_IMG', $relpath);
				$page->parse('flagimagevar', 'flagimage');
			} else {
				$page->set_var('flagimagevar', '');
			}

			// show screenshot thumbnail if available.
			$page->set_block('PAGE_CONTENT_T', 'shot1image', 'shot1imagevar');
			$relpath = $path_to_root . 'images/teams/shot1/' . $teamid . '_tn.jpg';
			$imagepath = getcwd() . '/' . $relpath;
			if (file_exists($imagepath)) {
				$page->set_var('PC_TEAM_SHOT1_IMG', $relpath);
				$page->parse('shot1imagevar', 'shot1image');
			} else {
				$page->set_var('shot1imagevar', '');
			}

			// show screenshot 2 thumbnail if available.
			$page->set_block('PAGE_CONTENT_T', 'shot2image', 'shot2imagevar');
			$relpath = $path_to_root . 'images/teams/shot2/' . $teamid . '_tn.jpg';
			$imagepath = getcwd() . '/' . $relpath;
			if (file_exists($imagepath)) {
				$page->set_var('PC_TEAM_SHOT2_IMG', $relpath);
				$page->parse('shot2imagevar', 'shot2image');
			} else {
				$page->set_var('shot2imagevar', '');
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
