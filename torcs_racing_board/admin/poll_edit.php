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

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks the login.
	$user = new User($db, $user_tablename, $loginlog_tablename);

	// Login?
	checkLogin($user);
	// Logout?
	checkLogout();


	$formerrors = intval(0);
	$editpage = FALSE;

	if ($_SESSION['logged'] == TRUE) {
		// Login template for statusbar.
		$page_statusbar = 'page_statusbar_logged_in.ihtml';
		if ($_SESSION['usergroup'] == 'admin') {
			if (isset($_POST['poll_submit'])) {
				if ($formerrors = checkPollInput()) {
					// Errors.
					$page_content = 'admin_poll_edit.ihtml';
				} else {
					commitEditPollInput($poll_tablename, $poll_answer_tablename, $_SESSION['uid']);
					$page_content = 'admin_poll_create_ok.ihtml';
				}
			} elseif (isset($_GET['editpollid']) && existsPoll($poll_tablename, $_GET['editpollid'])) {
				$page_content = 'admin_poll_edit.ihtml';
				$editpage = TRUE;
			} else {
				$page_content = 'admin_object_not_found.ihtml';
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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Poll Creation Page',
		'PB_DESCRIPTION'	=> 'Create a poll for the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, poll, create',
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

		if (isset($_POST['poll_submit']) && $formerrors > 0) {
			// Additional fields for error, page edit.
			$page->set_var(array(
				'PC_POLL_QUESTION'		=> isset($_POST['poll_question']) ? htmlentities(removeMagicQuotes($_POST['poll_question'])) : "",
				'PC_VALUE_STARTDATE'	=> isset($_POST['poll_startdate']) ? htmlentities(removeMagicQuotes($_POST['poll_startdate'])) : "",
				'PC_VALUE_ENDDATE'		=> isset($_POST['poll_enddate']) ? htmlentities(removeMagicQuotes($_POST['poll_enddate'])) : "",
				'PC_POLL_ID'			=> isset($_POST['poll_id']) ? htmlentities(removeMagicQuotes($_POST['poll_id'])) : ""
			));
			if (isset($_POST['poll_groups'])) {
				$page->set_var(array(
					'PC_ANONYMOUS_SELECTED'	=> (array_search('anonymous', $_POST['poll_groups']) !== FALSE) ? 'selected' : "",
					'PC_SPECTATOR_SELECTED'	=> (array_search('spectator', $_POST['poll_groups']) !== FALSE) ? 'selected' : "",
					'PC_RACER_SELECTED'		=> (array_search('racer', $_POST['poll_groups']) !== FALSE) ? 'selected' : ""
				));
			} else {
				$page->set_var(array(
					'PC_ANONYMOUS_SELECTED'	=> "",
					'PC_SPECTATOR_SELECTED'	=> "",
					'PC_RACER_SELECTED'		=> ""
				));
			}

			$page->set_block('PAGE_CONTENT_T', 'answer_row', 'answer_rows');

			if (isset($_POST['poll_answer'])) {
				$i = 1;
				foreach ($_POST['poll_answer'] as $key => $value) {
					$page->set_var(array(
						'PC_ANSWER_NUMBER'	=> $i,
						'PC_ANSWER_TEXT'	=> htmlentities(removeMagicQuotes($value)),
						'PC_ANSWER_ID'		=> htmlentities(removeMagicQuotes($_POST['poll_answer_id'][$i-1]))
					));
					$page->parse('answer_rows', 'answer_row', true);
					$i++;
				}
			}
		} elseif ($editpage) {
			$pollid_for_db = quoteString(removeMagicQuotes($_GET['editpollid']));
			$sql = "SELECT * FROM $poll_tablename WHERE pollid=" . $pollid_for_db;
			$thepoll = mysql_query($sql);
			$sql = "SELECT * FROM $poll_answer_tablename WHERE pollid=" . $pollid_for_db . " " .
				   "ORDER BY pollanswerid ASC";
			$theanswers = mysql_query($sql);

			$myrow = mysql_fetch_array($thepoll);

			$page->set_var(array(
				'PC_POLL_QUESTION'		=> htmlentities($myrow['question']),
				'PC_VALUE_STARTDATE'	=> $myrow['start'],
				'PC_VALUE_ENDDATE'		=> $myrow['end'],
				'PC_POLL_ID'			=> $myrow['pollid'],
				'PC_ANONYMOUS_SELECTED'	=> (strpos($myrow['groups'], 'anonymous') !== FALSE) ? 'selected' : "",
				'PC_SPECTATOR_SELECTED'	=> (strpos($myrow['groups'], 'spectator') !== FALSE) ? 'selected' : "",
				'PC_RACER_SELECTED'		=> (strpos($myrow['groups'], 'racer') !== FALSE) ? 'selected' : "",
			));

			$page->set_block('PAGE_CONTENT_T', 'answer_row', 'answer_rows');

			$i = 1;
			while ($myrow = mysql_fetch_array($theanswers)) {
				$page->set_var(array(
					'PC_ANSWER_NUMBER'	=> $i,
					'PC_ANSWER_TEXT'	=> htmlentities($myrow['answer']),
					'PC_ANSWER_ID'		=> $myrow['pollanswerid']
				));
				$page->parse('answer_rows', 'answer_row', true);
				$i++;
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
