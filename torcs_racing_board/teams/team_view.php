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
	$car_tablename = $db_prefix . TBL_CAR;
	$team_tablename = $db_prefix . TBL_TEAM;
	$driver_tablename = $db_prefix . TBL_DRIVER;

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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Team View',
		'PB_DESCRIPTION'	=> 'View team of the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, Board, Team, View, Show',
		'ROOTPATH'			=> $path_to_root,
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		$page->set_var(array(
			'PS_USERNAME'		=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'	=> $_SESSION['usergroup'],
			'PS_IPADSRESS'		=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'		=> $path_to_root . 'index.php'
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

	if (isset($_GET['viewteamid'])) {
		$teamid = intval(removeMagicQuotes($_GET['viewteamid']));
		$teamid_for_db = quoteString($teamid);
		$sql = "SELECT c.name AS carname, u.username AS username, t.name AS teamname, " .
			   "c.carid AS carid, u.id AS userid, t.teamid AS teamid, t.races AS races, " .
			   "t.points AS points, t.distance AS distance, t.description AS description, " .
			   "t.created AS created " .
			   "FROM $team_tablename t, $user_tablename u, $car_tablename c " .
			   "WHERE t.teamid=$teamid_for_db AND t.owner=u.id AND t.carid=c.carid";
		//$sql = "SELECT * FROM $team_tablename WHERE teamid=" . $teamid_for_db;
		$result = mysql_query($sql);
		if ($myrow = mysql_fetch_array($result)) {
			$page->set_file('PAGE_CONTENT_T', 'team_view.ihtml');
			$page->set_var(array(
				'PC_TEAM_ID'			=> $myrow['teamid'],
				'PC_TEAM_NAME'			=> htmlentities($myrow['teamname']),
				'PC_TEAM_DESCRIPTION'	=> htmlentities($myrow['description']),
				'PC_TEAM_CAR_ID'		=> $myrow['carid'],
				'PC_TEAM_CAR_NAME'		=> htmlentities($myrow['carname']),
				'PC_TEAM_OWNER_ID'		=> $myrow['userid'],
				'PC_TEAM_OWNER_NAME'	=> htmlentities($myrow['username']),
				'PC_TEAM_RACES'			=> $myrow['races'],
				'PC_TEAM_DISTANCE'		=> sprintf("%.1f", $myrow['distance']),
				'PC_TEAM_POINTS'		=> sprintf("%.1f", $myrow['points']),
				'PC_TEAM_CREATED'		=> htmlentities($myrow['created']),
			));

			$page->set_block("PAGE_CONTENT_T", "driver", "drivers");
			$sql = "SELECT * FROM $driver_tablename WHERE teamid=$teamid_for_db";
			$result = mysql_query($sql);
			// The team MUST have some drivers!
			while ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_TEAM_DRIVER_ID'			=> $myrow['driverid'],
					'PC_TEAM_DRIVER_NAME'		=> htmlentities($myrow['name']),
					'PC_TEAM_DRIVER_RACENUMBER'	=> $myrow['racenumber'],
					'PC_TEAM_DRIVER_CREATED'	=> htmlentities($myrow['created']),
					'PC_TEAM_DRIVER_DISTANCE'	=> sprintf("%.1f",$myrow['distance']),
					'PC_TEAM_DRIVER_POINTS'		=> sprintf("%.1f", $myrow['points']),
					'PC_TEAM_DRIVER_RACES'		=> $myrow['races']
				));
				$page->parse('drivers', 'driver', TRUE);
			}

			// show team flag image if available.
			$page->set_block("PAGE_CONTENT_T", "flagimage", "flagimagevar");
			$imagepath = getcwd() . '/' .$path_to_root . 'images/teams/flag/' . $teamid . '.jpg';
			if (file_exists($imagepath)) {
				$page->set_var('PC_TEAM_IMG_FLAG', $path_to_root . 'images/teams/flag/' . $teamid . '.jpg');
				$page->parse("flagimagevar", "flagimage");
			} else {
				$page->set_var("flagimagevar", "");
			}

			// show team logo image if available.
			$page->set_block("PAGE_CONTENT_T", "logoimage", "logoimagevar");
			$imagepath = getcwd() . '/' .$path_to_root . 'images/teams/logo/' . $teamid . '.jpg';
			if (file_exists($imagepath)) {
				$page->set_var('PC_TEAM_IMG_LOGO', $path_to_root . 'images/teams/logo/' . $teamid . '.jpg');
				$page->parse("logoimagevar", "logoimage");
			} else {
				$page->set_var("logoimagevar", "");
			}

			// show team screenshot(s) if available.
			$page->set_block("PAGE_CONTENT_T", "shot1image", "shot1imagevar");
			$imagepath = getcwd() . '/' .$path_to_root . 'images/teams/shot1/' . $teamid . '.jpg';
			if (file_exists($imagepath)) {
				$page->set_var('PC_TEAM_IMG_SHOT1', $path_to_root . 'images/teams/shot1/' . $teamid . '.jpg');
				$page->parse("shot1imagevar", "shot1image");
			} else {
				$page->set_var("shot1imagevar", "");
			}

			$page->set_block("PAGE_CONTENT_T", "shot2image", "shot2imagevar");
			$imagepath = getcwd() . '/' .$path_to_root . 'images/teams/shot2/' . $teamid . '.jpg';
			if (file_exists($imagepath)) {
				$page->set_var('PC_TEAM_IMG_SHOT2', $path_to_root . 'images/teams/shot2/' . $teamid . '.jpg');
				$page->parse("shot2imagevar", "shot2image");
			} else {
				$page->set_var("shot2imagevar", "");
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
