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
	require_once($path_to_root . 'lib/functions_forum.php');

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
	$forumpoll_tablename = $db_prefix . TBL_FORUM_POLL;

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks the login.
	$user = new User($db, $user_tablename, $loginlog_tablename);

	// Login?
	checkLogin($user);
	// Logout?
	checkLogout();

	if (isset($_GET['topicid'])) {
		$show_topic_id = removeMagicQuotes($_GET['topicid']);
	} elseif (isset($_POST['id_thread'])) {
		$show_topic_id = removeMagicQuotes($_POST['id_thread']);
	} else {
		$show_topic_id = 0;
	}

	forumSubmitNewMessage($forum_tablename, $topic_tablename, $user_tablename, $forumpoll_tablename, $show_topic_id);
	forumSubmitEditedMessage($forum_tablename, $forumpoll_tablename);
	forumHideMessage($forum_tablename);
	forumDeleteMessage($forum_tablename, $topic_tablename, $forumpoll_tablename);

	if ($_SESSION['logged'] == TRUE) {
		// Login template for statusbar.
		$page_statusbar = 'page_statusbar_logged_in.ihtml';
	} else {
		// Status view template for statusbar.
		$page_statusbar = 'page_statusbar.ihtml';
	}
	$page_content = 'forum_showthread.ihtml';

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
		'PB_PAGETITLE'		=> 'The TORCS Racing Board forum thread display',
		'PB_DESCRIPTION'	=> 'Show forum thread of The TORCS Racing Board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, Forum, Discuss, Thread, Topic',
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
			'PS_LOGINPAGE'		=> $_SERVER['PHP_SELF'] . '?' . $_SERVER['QUERY_STRING'],
			'PS_HOSTNAME'		=> SERVER_NAME
		));
	}

	$page->set_file(array(
		"message" => "forum_message.ihtml"
	));
	$OUTPUT_MESSAGES = "";

	$page->set_block('PAGE_CONTENT_T', 'show_poll', 'showpoll');
	$page->set_var('showpoll', "");
	if ($show_topic_id > 0) {
		$show_topic_id_for_db = quoteString($show_topic_id);
		displayReplies('0', $show_topic_id_for_db, $page, $forum_tablename, $user_tablename, MAX_FORUM_RECURSION, $OUTPUT_MESSAGES);
		// Display poll?
		$sql = "SELECT * FROM " . $forumpoll_tablename . " WHERE threadid=" . $show_topic_id_for_db;
		$result = mysql_query($sql);
		if ($myrow = mysql_fetch_array($result)) {
			// We have a poll.
			require_once($path_to_root . 'lib/functions_poll.php');
			$poll_tablename = $db_prefix . TBL_POLL;
			$poll_answer_tablename = $db_prefix . TBL_POLLANSWERS;
			$poll_voters_tablename = $db_prefix . TBL_POLLVOTERS;
			checkAndCommitVote($poll_tablename, $poll_answer_tablename, $poll_voters_tablename, $_SESSION['uid'], $_SESSION['usergroup']);

			$page->set_var('PC_POLL', displayPoll(
				$myrow['pollid'],
				$poll_tablename,
				$poll_answer_tablename,
				$poll_voters_tablename,
				$_SESSION['uid'],
				$_SESSION['usergroup'],
				$path_to_root
			));
			$page->parse('showpoll', 'show_poll');
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

	$page->set_var('MESSAGES', $OUTPUT_MESSAGES);

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
