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
	require_once($path_to_root . 'lib/functions_car.php');


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
			(isset($_POST['car_submit']) || isset($_GET['editcarid']))
		) {
			if (isset($_POST['car_submit'])) {
				if ($formerrors = checkCarInput()) {
					// Errors.
					$page_content = 'admin_car_edit.ihtml';
				} else {
					updateCarInput($car_tablename, $path_to_root);
					$page_content = 'admin_car_create_ok.ihtml';
				}
			} else {
				$page_content = 'admin_car_edit.ihtml';
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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Car Data Edit Page',
		'PB_DESCRIPTION'	=> 'Edit a cars data for the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, car, data, edit',
		'ROOTPATH'			=> $path_to_root
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		$page->set_var(array(
			'PS_USERNAME'			=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'		=> $_SESSION['usergroup'],
			'PS_IPADSRESS'			=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'			=> $path_to_root . 'index.php',
			'PC_CREATECARPAGE'		=> $_SERVER['PHP_SELF']
		));

		if (isset($_POST['car_submit']) && $formerrors > 0 && isset($_POST['car_id'])) {
			$page->set_var(array(
				'PC_CAR_ID'				=> intval(removeMagicQuotes($_POST['car_id'])),
				'PC_CAR_NAME'			=> isset($_POST['car_name']) ? htmlentities(removeMagicQuotes($_POST['car_name'])) : "",
				'PC_CAR_AUTHOR'			=> isset($_POST['car_author']) ? htmlentities(removeMagicQuotes($_POST['car_author'])) : "",
				'PC_CAR_MASS'			=> isset($_POST['car_mass']) ? htmlentities(removeMagicQuotes($_POST['car_mass'])) : "",
				'PC_CAR_TANK'			=> isset($_POST['car_maxfuel']) ? htmlentities(removeMagicQuotes($_POST['car_maxfuel'])) : "",
				'PC_CAR_CXA'			=> isset($_POST['car_cxa']) ? htmlentities(removeMagicQuotes($_POST['car_cxa'])) : "",
				'PC_CAR_POWER'			=> isset($_POST['car_power']) ? htmlentities(removeMagicQuotes($_POST['car_power'])) : "",
				'PC_CAR_WIDTH'			=> isset($_POST['car_width']) ? htmlentities(removeMagicQuotes($_POST['car_width'])) : "",
				'PC_CAR_LENGTH'			=> isset($_POST['car_length']) ? htmlentities(removeMagicQuotes($_POST['car_length'])) : "",
				'PC_CAR_RWD'			=> (isset($_POST['car_type']) && removeMagicQuotes($_POST['car_type']) == 'rwd') ? 'selected' : "",
				'PC_CAR_FWD'			=> (isset($_POST['car_type']) && removeMagicQuotes($_POST['car_type']) == 'fwd') ? 'selected' : "",
				'PC_CAR_4WD'			=> (isset($_POST['car_type']) && removeMagicQuotes($_POST['car_type']) == '4wd') ? 'selected' : "",
				'PC_CAR_DESCRIPTION'	=> isset($_POST['car_description']) ? htmlentities(removeMagicQuotes($_POST['car_description'])) : "",
				'PC_CAR_IMG_SRC'		=> isset($_FILES['car_image']) ? htmlentities(removeMagicQuotes($_FILES['car_image']['name'])) : ""
			));
		} elseif (isset($_GET['editcarid'])) {
			$id_for_db = quoteString(intval(removeMagicQuotes($_GET['editcarid'])));
			$sql = "SELECT * FROM $car_tablename WHERE carid=$id_for_db";
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
			$page->set_var(array(
				'PC_CAR_ID'				=> $myrow['carid'],
				'PC_CAR_NAME'			=> htmlentities($myrow['name']),
				'PC_CAR_AUTHOR'			=> htmlentities($myrow['author']),
				'PC_CAR_MASS'			=> $myrow['mass'],
				'PC_CAR_TANK'			=> $myrow['tank'],
				'PC_CAR_CXA'			=> $myrow['cxa'],
				'PC_CAR_POWER'			=> $myrow['power'],
				'PC_CAR_WIDTH'			=> $myrow['width'],
				'PC_CAR_LENGTH'			=> $myrow['length'],
				'PC_CAR_RWD'			=> (strcmp($myrow['train'], 'rwd') == 0) ? 'selected' : '',
				'PC_CAR_FWD'			=> (strcmp($myrow['train'], 'fwd') == 0) ? 'selected' : '',
				'PC_CAR_4WD'			=> (strcmp($myrow['train'], '4wd') == 0) ? 'selected' : '',
				'PC_CAR_DESCRIPTION'	=> htmlentities($myrow['description']),
				'PC_CAR_IMG_SRC'		=> ""
			));
			} else {
				$page->set_file('PAGE_CONTENT_T', 'admin_no_access.ihtml');
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
