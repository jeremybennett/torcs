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
	require_once($path_to_root . 'lib/functions_poll.php');


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
	$poll_tablename = $db_prefix . TBL_POLL;
	$poll_answer_tablename = $db_prefix . TBL_POLLANSWERS;
	$poll_voters_tablename = $db_prefix . TBL_POLLVOTERS;

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks the login.
	$user = new User($db, $user_tablename, $loginlog_tablename);

	// Login?
	checkLogin($user);
	// Logout?
	checkLogout();

	$viewpage = FALSE;

	if ($_SESSION['logged'] == TRUE) {
		// Login template for statusbar.
		$page_statusbar = 'page_statusbar_logged_in.ihtml';
		if ($_SESSION['usergroup'] == 'admin' &&
			isset($_GET['viewpollid']) &&
			existsPoll($poll_tablename, $_GET['viewpollid']))
		{
			$page_content = 'admin_poll_view.ihtml';
			$viewpage = TRUE;
		} else {
			$page_content = 'admin_object_not_found.ihtml';
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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Poll List',
		'PB_DESCRIPTION'	=> 'List all polls of the TORCS Racing Board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, poll, list',
		'ROOTPATH'			=> $path_to_root
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		$page->set_var(array(
			'PS_USERNAME'		=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'	=> $_SESSION['usergroup'],
			'PS_IPADSRESS'		=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'		=> $path_to_root . 'index.php',
			'PC_CREATEPOLLPAGE'	=> $_SERVER['PHP_SELF']
		));

		if ($viewpage) {
			$pollid_for_db = quoteString(removeMagicQuotes($_GET['viewpollid']));
			$sql = "SELECT * FROM $poll_tablename WHERE pollid=" . $pollid_for_db;
			$thepoll = mysql_query($sql);
			$sql = "SELECT * FROM $poll_answer_tablename WHERE pollid=" . $pollid_for_db . " " .
				   "ORDER BY pollanswerid ASC";
			$theanswers = mysql_query($sql);

			$myrow = mysql_fetch_array($thepoll);

			$sql = "SELECT username AS uname FROM $poll_tablename p, $user_tablename u WHERE " .
				   "p.pollid=$pollid_for_db AND p.owner=u.id";
			$poll_owner = mysql_fetch_array(mysql_query($sql));
			$poll_owner = $poll_owner['uname'];

			$page->set_var(array(
				'PC_POLL_ID'			=> $myrow['pollid'],
				'PC_POLL_QUESTION'		=> htmlentities($myrow['question']),
				'PC_POLL_STARTDATE'		=> $myrow['start'],
				'PC_POLL_ENDDATE'		=> $myrow['end'],
				'PC_POLL_GROUPS'		=> $myrow['groups'],
				'PC_POLL_OWNER'			=> $poll_owner
			));

			$page->set_block('PAGE_CONTENT_T', 'answer_row', 'answer_rows');
			// Answers.
			// Build table.
			$toggle = intval(0);
			while ($myrow = mysql_fetch_array($theanswers)) {
				$page->set_var(array(
					'PC_COLOR_ANSWER'		=> ($toggle == 0) ? COLOR_TB1 : COLOR_TB2,
					'PC_POLL_ANSWER_ID'		=> $myrow['pollanswerid'],
					'PC_POLL_ANSWER'		=> htmlentities($myrow['answer']),
					'PC_POLL_ANSWER_VOTES'	=> $myrow['count']
				));
				$toggle = ($toggle == 0) ? 1 : 0;
				$page->parse('answer_rows', 'answer_row', true);
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
