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


	// Puts a new message into the DB.
	function forumSubmitNewMessage($forum_tablename, $topic_tablename, $user_tablename, $forumpoll_tablename, &$show_topic_id)
	{
		// Submit new message?
		if (isset($_POST['submit_forum_write'])) {
			// The creation checks the login.
			if ($_SESSION['logged'] == TRUE &&
				isset($_POST['id_parent']) &&
				isset($_POST['id_thread']) &&
				isset($_POST['subject']) &&
				isset($_POST['text'])
			) {
				// write to db.
				$userid_for_db = quoteString($_SESSION['uid']);
				$id_parent = intval(removeMagicQuotes($_POST['id_parent']));	// 0 if empty.
				$id_thread = intval(removeMagicQuotes($_POST['id_thread']));	// dito.
				$subject_for_db = quoteString(removeMagicQuotes($_POST['subject']));
				$text_for_db = quoteString(removeMagicQuotes($_POST['text']));
				$date_now_for_db = quoteString(date("Y-m-d H:i:s"));

				// New thread or new message?
				if ($id_thread != 0 && $id_parent != 0) {
					// Reply into an exising thread.
					// Check if parent exists.
					$id_thread_for_db = quoteString($id_thread);
					$id_parent_for_db = quoteString($id_parent);
					$sql = "SELECT * FROM " . $forum_tablename . " WHERE " .
						"id=" . $id_parent_for_db . " AND " .
						"id_thread=" . $id_thread_for_db;
					$result = mysql_query($sql);
					if ($myrow = mysql_fetch_array($result)) {
						// Ok, a message with id in id_thread exists.
						$sql = "INSERT INTO " . $forum_tablename . " " .
						"(author, last_editor, subject, text, created, last_edited, id_thread, id_parent) " .
						" VALUES " .
						"($userid_for_db, $userid_for_db, $subject_for_db, " .
						"$text_for_db, $date_now_for_db, $date_now_for_db, " .
						"$id_thread_for_db, $id_parent_for_db)";
						mysql_query($sql);
						// Update topic related data.
						$sql = "UPDATE " . $topic_tablename . " SET replies=replies+1 " .
							"WHERE id=" . $id_thread_for_db;
						mysql_query($sql);
						$sql = "UPDATE " . $user_tablename . " SET postings=postings+1 " .
							"WHERE id=" . $userid_for_db;
						mysql_query($sql);
					} else {
						// Error, the parent does not exist, silent.
					}
				} else {
					// New thread, insert data.
					$sql = "INSERT INTO " . $forum_tablename . " " .
						"(author, last_editor, subject, text, created, last_edited) VALUES " .
						"($userid_for_db, $userid_for_db, $subject_for_db, " .
						"$text_for_db, $date_now_for_db, $date_now_for_db)";
					mysql_query($sql);
					// Update topic related data.
					$sql = "SELECT LAST_INSERT_ID() AS id";
					$result = mysql_query($sql);
					if ($myrow = mysql_fetch_array($result)) {
						$show_topic_id = $myrow['id'];
						$id_thread_for_db = quoteString($myrow['id']);
						$sql = "INSERT INTO " . $topic_tablename . " (id) VALUES " .
							"($id_thread_for_db)";
						mysql_query($sql);
						$sql = "UPDATE " . $forum_tablename . " SET id_thread=" . $id_thread_for_db . " " .
							"WHERE id=" . $id_thread_for_db;
						mysql_query($sql);
						$sql = "UPDATE " . $user_tablename . " SET postings=postings+1 " .
							"WHERE id=" . $userid_for_db;
						mysql_query($sql);

						// Poll-Message connection.
						if ($_SESSION['usergroup'] == 'admin' && isset($_POST['message_pollid'])) {
							$pollid = intval(removeMagicQuotes($_POST['message_pollid']));
							if ($pollid > 0) {
								$pollid_for_db = quoteString($pollid);
								$sql = "INSERT INTO " . $forumpoll_tablename . " (threadid, pollid) " .
									   "VALUES($id_thread_for_db, $pollid_for_db)";
								mysql_query($sql);
							}
						}
					}
				}
			} else {
				// Silent, not logged in.
			}
		}
	}


	// Submit an edited message.
	function forumSubmitEditedMessage($forum_tablename, $forumpoll_tablename)
	{
		if (isset($_POST['submit_forum_edit'])) {
			if ($_SESSION['logged'] == TRUE &&
				isset($_POST['id_message']) &&
				isset($_POST['id_thread']) &&
				isset($_POST['subject']) &&
				isset($_POST['text'])
			) {
				// Check existing message.
				$id_msg_for_db = quoteString(intval(removeMagicQuotes($_POST['id_message'])));
				$sql = "SELECT * FROM " . $forum_tablename . " WHERE id=" . $id_msg_for_db;
				$result = mysql_query($sql);
				if ($myrow = mysql_fetch_array($result)) {
					if (($myrow['author'] == $_SESSION['uid']) ||
						($_SESSION['usergroup'] == 'admin'))
					{
						// Alter message.
						$subject_for_db = quoteString(removeMagicQuotes($_POST['subject']));
						$text_for_db = quoteString(removeMagicQuotes($_POST['text']));
						$date_now_for_db = quoteString(date("Y-m-d H:i:s"));
						$sql = "UPDATE " . $forum_tablename . " SET subject=" . $subject_for_db . ", " .
							"text=" . $text_for_db . ", last_edited=" . $date_now_for_db . ", " .
							"last_editor=" . $_SESSION['uid'] . " " .
							"WHERE id=" . $id_msg_for_db;
						mysql_query($sql);
						// Updating topic.lastpost useful on edit? Then put it here.
					}
					// Update poll connection.
					if ($_SESSION['usergroup'] == 'admin' &&
						isset($_POST['message_pollid']) &&
						$myrow['id_parent'] == 0
					) {
						$pollid = intval(removeMagicQuotes($_POST['message_pollid']));
						if ($pollid == 0) {
							// Remove poll from thread, optimistic.
							$sql = "DELETE FROM " . $forumpoll_tablename . " WHERE threadid=" . $id_msg_for_db;
							mysql_query($sql);
						} else {
							// Set poll, try first update, then insert.
							$pollid_for_db = quoteString($pollid);
							$sql = "UPDATE " . $forumpoll_tablename . " SET pollid=" . $pollid_for_db . " " .
								   "WHERE threadid=" . $id_msg_for_db;
							mysql_query($sql);
							if (mysql_affected_rows() == 0) {
								// Failed, try insert.
								$sql = "INSERT INTO " . $forumpoll_tablename . " (threadid, pollid) " .
									   "VALUES ($id_msg_for_db, $pollid_for_db)";
								mysql_query($sql);
							}
						}
					}
				}
			}
		}
	}


	// Hide a message.
	function forumHideMessage($forum_tablename)
	{
		if (isset($_GET['hide'])) {
			// Check if admin.
			if ($_SESSION['usergroup'] == 'admin' &&
				isset($_GET['msgid']))
			{
				// Check if message exists.
				$id_msg_for_db = quoteString(intval(removeMagicQuotes($_GET['msgid'])));
				$sql = "SELECT * FROM " . $forum_tablename . " WHERE id=" . $id_msg_for_db;
				$result = mysql_query($sql);
				if ($myrow = mysql_fetch_array($result)) {
					if ($_GET['hide'] == 'true') {
						$state = "'hidden'";
					} else {
						$state = "'visible'";
					}
					$sql = "UPDATE " . $forum_tablename . " SET state=" . $state . " " .
						"WHERE id=" . $id_msg_for_db;
					mysql_query($sql);
				}
			}
		}
	}


	// Delete a message recursively.
	function forumDeleteMessagesRecursive($forum_tablename, $id, $n, &$deleted)
	{
		if ( $n < 1) return;
		$id_for_db = quoteString($id);
		$sql = "SELECT * FROM " . $forum_tablename . " WHERE " .
			   "id_parent=" . $id_for_db;
		$result = mysql_query($sql);

		while ($myrow = mysql_fetch_array($result)) {
			forumDeleteMessagesRecursive($forum_tablename, $myrow['id'], $n - 1, $deleted);
		}

		$sql = "DELETE FROM " . $forum_tablename . " WHERE id=" . $id_for_db;
		mysql_query($sql);
		if (mysql_errno() == 0) {
			$deleted += mysql_affected_rows();
		}
	}


	// Delete a message recursively.
	function forumDeleteMessage($forum_tablename, $topic_tablename, $forumpoll_tablename)
	{
		if ($_SESSION['usergroup'] == 'admin' && isset($_GET['topicid']) && isset($_GET['deleteid'])) {
			$deleted = intval(0);
			$topicid = intval(removeMagicQuotes($_GET['topicid']));
			$msgid = intval(removeMagicQuotes($_GET['deleteid']));
			forumDeleteMessagesRecursive($forum_tablename, $msgid, MAX_FORUM_RECURSION, $deleted);
			// Update topic data.
			if ($topicid == $msgid) {
				// The whole topic was deleted.
				$sql = "DELETE FROM " . $topic_tablename . " WHERE id=" . quoteString($topicid);
				mysql_query($sql);
				$sql = "DELETE FROM " . $forumpoll_tablename . " WHERE threadid=" . quoteString($topicid);
				mysql_query($sql);
			} else {
				if ($deleted != 0) {
					// Just some message(s) removed, update reply counter.
					$sql = "UPDATE " . $topic_tablename . " SET replies=replies-$deleted WHERE id=$topicid";
					mysql_query($sql);
				}
			}
		}
	}


	// Build the HTML for a thread.
	function displayReplies(
		$id_parent,
		$id_thread,
		&$t,			// template.
		$forum,			// forum table name.
		$users,			// users table name.
		$n,				// Recursion limit, just in case...
		&$output
	)
	{
		if ( $n < 1) return;
		$sql = "SELECT f.id, f.subject, u.username, f.author, f.id_parent, " .
			   "f.created, f.last_edited, f.id_thread, f.text, f.state, " .
			   "uu.username AS lasteditor, uu.id AS lasteditor_id " .
			   "FROM $forum f, $users u, $users uu " .
			   "WHERE f.id_parent=$id_parent AND f.id_thread=$id_thread AND " .
			   "u.id = f.author AND f.last_editor=uu.id ORDER BY f.created ASC";
		$result = mysql_query($sql);
		while ($myrow = mysql_fetch_array($result)) {
			// Edit is just possible for the author and the admin.
			// TODO: nicer solution without compromise the templates.
			if (($myrow['author'] == $_SESSION['uid']) ||
				($_SESSION['usergroup'] == 'admin'))
			{
				$edit = 'Edit';
				$edit_href = './edit.php?msgid=' . $myrow['id'];
			} else {
				$edit = '';
				$edit_href = '';
			}

			// Delete just for admins.
			if ($_SESSION['usergroup'] == 'admin') {
				$delete = 'Delete';
				if ($myrow['id_parent'] == 0) {
					$delete_href = './threadlist.php' . '?deleteid=' . $myrow['id'] . '&topicid=' . $myrow['id_thread'];
				} else {
					$delete_href = $_SERVER['PHP_SELF'] . '?deleteid=' . $myrow['id'] . '&topicid=' . $myrow['id_thread'];
				}
			} else {
				$delete = '';
				$delete_href = '';
			}

			// Visible or hidden?
			if ($myrow['state'] == 'visible') {
				$display_text = nl2br(htmlentities($myrow['text']));
				$display_subject = htmlentities($myrow['subject']);
				if ($_SESSION['usergroup'] == 'admin') {
					$hide_href = $_SERVER['PHP_SELF'] . '?msgid=' . $myrow['id'] .
								 '&hide=true&topicid=' . $myrow['id_thread'];
					$hide = 'Hide';
				} else {
					$hide_href = '';
					$hide = '';
				}
			} elseif ($myrow['state'] == 'hidden') {
				if ($_SESSION['usergroup'] == 'admin') {
					$display_text = nl2br(htmlentities($myrow['text']));
					$display_subject = htmlentities($myrow['subject']);
					$hide_href = $_SERVER['PHP_SELF'] . '?msgid=' . $myrow['id'] .
								 '&hide=false&topicid=' . $myrow['id_thread'];
					$hide = 'Show';
				} else {
					$hide = '';
					$hide_href = '';
					$display_text = '';
					$display_subject = "Message set to hidden by the moderator.";
				}
			} else {
				die;
			}

			// Reply just for logged in users.
			if ($_SESSION['logged'] == TRUE) {
				$reply = 'Reply';
				$reply_href = './write.php?id_thread=' . $myrow['id_thread'] .
							  '&id_parent=' . $myrow['id'];
			} else {
				$reply = '';
				$reply_href = '';
			}

			$t->set_var(array(
				'PC_SUBJECT'			=> $display_subject,
				'PC_SUBJECT_URL'		=> urlencode($display_subject),
				'PC_ID_THREAD'			=> $myrow['id_thread'],
				'PC_ID_PARENT'			=> $myrow['id'],
				'PC_AUTHOR'				=> htmlentities($myrow['username']),
				'PC_AUTHOR_ID'			=> $myrow['author'],
				'PC_LASTEDITOR'			=> $myrow['lasteditor'],
				'PC_LASTEDITOR_ID'		=> $myrow['lasteditor_id'],
				'PC_CREATED'			=> $myrow['created'],
				'PC_LASTEDITED'			=> $myrow['last_edited'],
				'PC_TEXT'				=> $display_text,
				'PC_EDIT_MESSAGE'		=> $edit,
				'PC_EDIT_MESSAGE_HREF'	=> $edit_href,
				'PC_HIDE_MESSAGE'		=> $hide,
				'PC_HIDE_MESSAGE_HREF'	=> $hide_href,
				'PC_REPLY_MESSAGE'		=> $reply,
				'PC_REPLY_MESSAGE_HREF'	=> $reply_href,
				'PC_DELETE_MESSAGE'		=> $delete,
				'PC_DELETE_MESSAGE_HREF'=> $delete_href,
				'PC_COLOR_HEADER'		=> ($myrow['state'] == 'hidden') ? COLOR_TB_ERR : COLOR_TB1,
				'PC_COLOR_MESSAGE'		=> '#ffffff',
				'PC_COLOR_FOOTER'		=> COLOR_TB3
			));

			$t->parse("MESSAGE", array("message"));
			$output .= $t->get_var("MESSAGE");
			// TODO: nicer solution without compromise the templates.
			$output .= "\n<ul " . 'style="margin-left:10px; padding-left:10px;"' .">\n";
			displayReplies($myrow['id'], $myrow['id_thread'], $t, $forum, $users, $n - 1, $output);
			//echo "</ul>\n";
			$output .= "\n</ul>\n";
		}
	}

?>
