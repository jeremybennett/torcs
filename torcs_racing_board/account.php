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
	$path_to_root = './';
	require_once($path_to_root . 'secrets/configuration.php');
	require_once($path_to_root . 'lib/functions.php');
	require_once($path_to_root . 'lib/classes.php');
	require_once($path_to_root . 'lib/template.inc');
	require_once($path_to_root . 'lib/functions_register.php');
	require_once($path_to_root . 'lib/functions_account.php');
	require_once($path_to_root . 'lib/functions_images.php');
	require_once($path_to_root . 'lib/functions_validate.php');


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
	$confirm_tablename = $db_prefix . TBL_CONFIRM;

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks if we are logged in.
	$user = new User($db, $user_tablename, $loginlog_tablename);
	// New login?
	checkLogin($user);
	// Logout?
	checkLogout();

	$formerrors = intval(0);

	if ($_SESSION['logged'] == TRUE) {
		// Login template for statusbar.
		$page_statusbar = 'page_statusbar_logged_in.ihtml';
		$page_content = 'account_content.ihtml';
		if (isset($_POST['account_submit'])) {
			$formerrors = checkAccountInput();
			if ($formerrors == 0) {
				$formerrors = commitAccountInput($user_tablename, $_SESSION['uid']);
			}
		}
		if (isset($_POST['racer_image_submit']) && $_SESSION['usergroup'] == 'racer') {
			commitRacerPhoto($_SESSION['uid'], $path_to_root);
		}

	} else {
		// Status view template for statusbar.
		$page_statusbar = 'page_statusbar.ihtml';
		$page_content = 'page_content.ihtml';
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
		'PB_PAGETITLE'		=> 'Your Account at the TORCS Racing Board',
		'PB_DESCRIPTION'	=> 'manage your TORCS racing board account',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, manage, settings, account',
		'ROOTPATH'			=> $path_to_root
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		if ($_SESSION['usergroup'] == 'spectator') {
			$page->set_var('BECOME_A_RACER', '<a href="' . $path_to_root . 'users/spectator_to_racer.php">Become a racer</a>.');
		} else {
			$page->set_var('BECOME_A_RACER', 'No change allowed.');
		}

		$page->set_block('PAGE_CONTENT_T', 'racer_image', 'racer_image_var');
		if ($_SESSION['usergroup'] == 'racer') {
			// show user image thumbnail if available.
			$page->set_block('racer_image', 'userimage', 'userimagevar');
			$imagepath = getcwd() . '/' .$path_to_root . 'images/users/' . $_SESSION['uid'] . '_tn.jpg';
			if (file_exists($imagepath)) {
				$page->set_var('PC_USER_IMG_SRC', $path_to_root . 'images/users/' . $_SESSION['uid'] . '_tn.jpg');
				$page->parse('userimagevar', 'userimage');
			} else {
				$page->set_var('userimagevar', '');
			}
			$page->parse('racer_image_var', 'racer_image');
		} else {
			$page->set_var('racer_image_var', '');
		}

		$page->set_var(array(
			'PS_USERNAME'			=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'		=> $_SESSION['usergroup'],
			'PS_IPADSRESS'			=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'			=> $path_to_root . 'index.php',
			'PS_USERNAME_SIZE'		=> MAX_USERNAME_LENGTH,
			'PC_ACCOUNTPAGE'		=> $_SERVER['PHP_SELF'],
			'PC_VALUE_USERNAME'		=> htmlentities($_SESSION['username']),
			'PC_COLOR_USERNAME'		=> COLOR_TB1,
			'PC_VALUE_ACCOUNT'		=> htmlentities($_SESSION['usergroup']),
			'PC_COLOR_ACCOUNT'		=> COLOR_TB2
		));

		if (!isset($_POST['account_submit']) || ($formerrors == 0)) {
			// Fetch user data from db.
			$sql = "SELECT * FROM " . $user_tablename . " WHERE " .
				   "id=" . quoteString($_SESSION['uid']);
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_COLOR_FIRSTNAME'	=> COLOR_TB1,
					'PC_COLOR_LASTNAME'		=> COLOR_TB2,
					'PC_COLOR_PASSWORD'		=> COLOR_TB1,
					'PC_COLOR_PASSWORD2'	=> COLOR_TB2,
					'PC_COLOR_EMAIL'		=> COLOR_TB1,

					'PC_VALUE_FIRSTNAME'	=> htmlentities($myrow['firstname']),
					'PC_VALUE_LASTNAME'		=> htmlentities($myrow['lastname']),
					'PC_VALUE_PASSWORD'		=> "",
					'PC_VALUE_PASSWORD2'	=> "",
					'PC_VALUE_EMAIL'		=> htmlentities($myrow['email']),

					'PC_DESC_FIRSTNAME'		=> "Your first name.",
					'PC_DESC_LASTNAME'		=> "Your last name.",
					'PC_DESC_PASSWORD'		=> "Your password.",
					'PC_DESC_PASSWORD2'		=> "Retype your password.",
					'PC_DESC_EMAIL'			=> "Your e-mail address.",
					'PC_ACCOUNTPAGE'		=> $_SERVER['PHP_SELF']
				));
			}
		} else {
			$errmsg = "";
			if (isFirstnameOk($formerrors, $errmsg)) {
				$page->set_var(array(
					'PC_VALUE_FIRSTNAME'	=> htmlentities(removeMagicQuotes($_POST['account_firstname'])),
					'PC_COLOR_FIRSTNAME'	=> COLOR_TB1,
					'PC_DESC_FIRSTNAME'		=> "Ok"
				));
			} else {
				$page->set_var(array(
					'PC_VALUE_FIRSTNAME'	=> htmlentities(removeMagicQuotes($_POST['account_firstname'])),
					'PC_COLOR_FIRSTNAME'	=> COLOR_TB_ERR,
					'PC_DESC_FIRSTNAME'		=> $errmsg
				));
			}

			if (isLastnameOk($formerrors, $errmsg)) {
				$page->set_var(array(
					'PC_VALUE_LASTNAME'		=> htmlentities(removeMagicQuotes($_POST['account_lastname'])),
					'PC_COLOR_LASTNAME'		=> COLOR_TB2,
					'PC_DESC_LASTNAME'		=> "Ok"
				));
			} else {
				$page->set_var(array(
					'PC_VALUE_LASTNAME'		=> htmlentities(removeMagicQuotes($_POST['account_lastname'])),
					'PC_COLOR_LASTNAME'		=> COLOR_TB_ERR,
					'PC_DESC_LASTNAME'		=> $errmsg
				));
			}

			if (isPasswordOk($formerrors, $errmsg)) {
				$page->set_var(array(
					'PC_VALUE_PASSWORD'		=> "",
					'PC_VALUE_PASSWORD2'	=> "",
					'PC_COLOR_PASSWORD'		=> COLOR_TB1,
					'PC_COLOR_PASSWORD2'	=> COLOR_TB2,
					'PC_DESC_PASSWORD'		=> "Ok",
					'PC_DESC_PASSWORD2'		=> "Ok"
				));
			} else {
				$page->set_var(array(
					'PC_VALUE_PASSWORD'		=> "",
					'PC_VALUE_PASSWORD2'	=> "",
					'PC_COLOR_PASSWORD'		=> COLOR_TB_ERR,
					'PC_COLOR_PASSWORD2'	=> COLOR_TB_ERR,
					'PC_DESC_PASSWORD'		=> $errmsg,
					'PC_DESC_PASSWORD2'		=> $errmsg
				));
			}

			if (isMailOk($formerrors, $errmsg)) {
				$page->set_var(array(
					'PC_VALUE_EMAIL'		=> htmlentities(removeMagicQuotes($_POST['account_email'])),
					'PC_COLOR_EMAIL'		=> COLOR_TB1,
					'PC_DESC_EMAIL'			=> "Ok"
				));
			} else {
				$page->set_var(array(
					'PC_VALUE_EMAIL'		=> htmlentities(removeMagicQuotes($_POST['account_email'])),
					'PC_COLOR_EMAIL'		=> COLOR_TB_ERR,
					'PC_DESC_EMAIL'			=> $errmsg
				));
			}
		}
	} else {
		// Variables if NOT logged in.
		$page->set_var(array(
			'PS_PASSWORD_SIZE'	=> MAX_USERNAME_LENGTH,
			'PS_USERNAME_SIZE'	=> MAX_USERNAME_LENGTH,
			'PS_LOGINPAGE'		=> $_SERVER['PHP_SELF'],
			'PS_HOSTNAME'		=> SERVER_NAME,
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
