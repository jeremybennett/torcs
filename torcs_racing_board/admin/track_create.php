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
	require_once($path_to_root . 'lib/functions_track.php');


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
	$track_tablename = $db_prefix . TBL_TRACK;

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
		if ($_SESSION['usergroup'] == 'admin') {
			if (isset($_POST['track_submit'])) {
				if ($formerrors = checkTrackInput()) {
					// Errors.
					$page_content = 'admin_track_create.ihtml';
				} else {
					commitTrackInput($track_tablename, $path_to_root);
					$page_content = 'admin_track_create_ok.ihtml';
				}
			} else {
				$page_content = 'admin_track_create.ihtml';
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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Track Creation Page',
		'PB_DESCRIPTION'	=> 'Create a track for the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, track, create',
		'ROOTPATH'			=> $path_to_root
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		$page->set_var(array(
			'PS_USERNAME'			=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'		=> $_SESSION['usergroup'],
			'PS_IPADSRESS'			=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'			=> $path_to_root . 'index.php',
			'PC_CREATETRACKPAGE'	=> $_SERVER['PHP_SELF']
		));

		if (isset($_POST['track_submit']) && $formerrors > 0) {
			$page->set_var(array(
				'PC_TRACK_NAME'			=> isset($_POST['track_name']) ? htmlentities(removeMagicQuotes($_POST['track_name'])) : "",
				'PC_TRACK_NBPITS'		=> isset($_POST['track_nbpits']) ? htmlentities(removeMagicQuotes($_POST['track_nbpits'])) : "",
				'PC_TRACK_WIDTH'		=> isset($_POST['track_width']) ? htmlentities(removeMagicQuotes($_POST['track_width'])) : "",
				'PC_TRACK_LENGTH'		=> isset($_POST['track_length']) ? htmlentities(removeMagicQuotes($_POST['track_length'])) : "",
				'PC_TRACK_AUTHOR'		=> isset($_POST['track_author']) ? htmlentities(removeMagicQuotes($_POST['track_author'])) : "",
				'PC_TRACK_TYPE_DIRT'	=> (isset($_POST['track_type']) && removeMagicQuotes($_POST['track_type']) == 'dirt') ? 'selected' : "",
				'PC_TRACK_TYPE_OVAL'	=> (isset($_POST['track_type']) && removeMagicQuotes($_POST['track_type']) == 'oval') ? 'selected' : "",
				'PC_TRACK_TYPE_ROAD'	=> (isset($_POST['track_type']) && removeMagicQuotes($_POST['track_type']) == 'road') ? 'selected' : "",
				'PC_TRACK_DESCRIPTION'	=> isset($_POST['track_description']) ? htmlentities(removeMagicQuotes($_POST['track_description'])) : "",
				'PC_TRACK_IMG_SRC'		=> isset($_FILES['track_image']) ? htmlentities(removeMagicQuotes($_FILES['track_image']['name'])) : ""
			));
		} else {
			$page->set_var(array(
				'PC_TRACK_NAME'			=> "",
				'PC_TRACK_NBPITS'		=> "",
				'PC_TRACK_WIDTH'		=> "",
				'PC_TRACK_LENGTH'		=> "",
				'PC_TRACK_AUTHOR'		=> "",
				'PC_TRACK_TYPE_DIRT'	=> "",
				'PC_TRACK_TYPE_OVAL'	=> "",
				'PC_TRACK_TYPE_ROAD'	=> "",
				'PC_TRACK_DESCRIPTION'	=> "",
				'PC_TRACK_IMG_SRC'		=> ""
			));
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
