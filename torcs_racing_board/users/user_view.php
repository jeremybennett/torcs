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
	$team_tablename = $db_prefix . TBL_TEAM;

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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board User View',
		'PB_DESCRIPTION'	=> 'View user of the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, Board, User, View, Show',
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

	if (isset($_GET['viewuserid'])) {
		$userid = intval(removeMagicQuotes($_GET['viewuserid']));
		$userid_for_db = quoteString($userid);
		$sql = "SELECT * FROM $user_tablename WHERE id=" . $userid_for_db;
		$result = mysql_query($sql);
		if ($myrow = mysql_fetch_array($result)) {
			$page->set_file('PAGE_CONTENT_T', 'user_view.ihtml');
			$page->set_block("PAGE_CONTENT_T", "admin", "adminvar");
			if ($_SESSION['usergroup'] == 'admin') {
				$page->set_var(array(
					'PC_USER_EMAIL'		=> htmlentities($myrow['email']),
					'PC_USER_IP'		=> htmlentities($myrow['ip']),
					'PC_USER_ACTIVE'	=> htmlentities($myrow['active']),
					'PC_USER_LASTLOGIN'	=> htmlentities($myrow['lastlogin']),
					'PC_USER_REGISTER'	=> htmlentities($myrow['registered']),
					'PC_USER_LASTVISIT'	=> htmlentities($myrow['lastvisit'])
				));
				$page->parse("adminvar", "admin");
			} else {
				$page->set_var("adminvar", "");
			}
			$page->set_var(array(
				'PC_USER_ID'		=> $myrow['id'],
				'PC_USER_NAME'		=> htmlentities($myrow['username']),
				'PC_USER_FIRSTNAME'	=> ($myrow['firstname'] == '') ? '?' : htmlentities($myrow['firstname']),
				'PC_USER_LASTNAME'	=> htmlentities($myrow['lastname']),
				'PC_USER_ACCOUNT'	=> htmlentities($myrow['account']),
				'PC_USER_IMG_SRC'	=> $path_to_root . 'images/users/' . $myrow['id'] . '.jpg',
				'PC_USER_POSTINGS'	=> $myrow['postings']
			));

			// show user image if available.
			$page->set_block('PAGE_CONTENT_T', 'userimage', 'userimagevar');
			$imagepath = getcwd() . '/' .$path_to_root . 'images/users/' . $userid . '.jpg';
			if (file_exists($imagepath)) {
				$page->set_var('PC_USER_IMG_SRC', $path_to_root . 'images/users/' . $myrow['id'] . '.jpg');
				$page->parse('userimagevar', 'userimage');
			} else {
				$page->set_var('userimagevar', '');
			}

			// TODO: Show teams of user.
			$page->set_block('PAGE_CONTENT_T', 'racer', 'racervar');
			if (($myrow['account']) == 'racer') {
				$page->set_block('racer', 'team', 'teamvar');
				$sql = "SELECT teamid,name FROM $team_tablename WHERE owner=$userid_for_db";
				$result = mysql_query($sql);
				$nb_teams = 0;
				while ($myrow = mysql_fetch_array($result)) {
					$page->set_var(array(
						'PC_USER_TEAM_ID'	=> $myrow['teamid'],
						'PC_USER_TEAM_NAME'	=> htmlentities($myrow['name'])
					));
					$page->parse('teamvar', 'team', TRUE);
					$nb_teams++;
				}
				if ($nb_teams == 0) {
					$page->set_var('teamvar', '');
				}
				$page->parse('racervar', 'racer');
			} else {
				$page->set_var('racervar', '');
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
