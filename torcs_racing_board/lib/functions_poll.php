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


	// Returns > 0 if errors are detected.
	function checkPollInput()
	{
		$errors = intval(0);
		// Check if question field is not empty.
		if (!(isset($_POST['poll_question']) && strlen($_POST['poll_question']) > 0)) {
			$errors += 1;
		}

		// Check dates, format ok?
		$sdate = (isset($_POST['poll_startdate']) && strlen($_POST['poll_startdate']) > 0) ? $_POST['poll_startdate'] : "dummy";
		$edate = (isset($_POST['poll_enddate']) && strlen($_POST['poll_enddate']) > 0) ? $_POST['poll_enddate'] : "dummy";
		if (($sd = strtotime($sdate)) < 0) {
			$errors += 1;
		}
		if (($ed = strtotime($edate)) < 0) {
			$errors += 1;
		}

		// Check dates, end after start?
		if ($sd >= $ed) {
			$errors += 1;
		}
		// Check groups, at least one must be selected.
		if (isset($_POST['poll_groups']) && count($_POST['poll_groups']) > 0) {
			foreach ($_POST['poll_groups'] as $key => $value) {
				if ($value != 'anonymous' && $value != 'spectator' && $value != 'racer') {
					$errors += 1;
				}
			}
		} else {
			$errors += 1;
		}

		// At least two answers?
		if (isset($_POST['poll_answer']) && count($_POST['poll_answer']) > 1) {
			// Check the length of the answers.
			foreach ($_POST['poll_answer'] as $key => $value) {
				if (strlen($value) > 255 || strlen($value) < 1) {
					$errors += 1;
				}
			}
		} else {
			$errors += 1;
		}
		return $errors;
	}


	// Fills the tables with the posted poll data, the input is not validated (validate with checkPollInput()).
	function commitPollInput($poll, $poll_answers, $uid)
	{
		// Commit poll into poll table.
		$question_for_db = quoteString(removeMagicQuotes($_POST['poll_question']));
		$sdate_for_db = quoteString(removeMagicQuotes($_POST['poll_startdate']));
		$edate_for_db = quoteString(removeMagicQuotes($_POST['poll_enddate']));
		$groups_for_db = "";
		$separator = "";
		foreach ($_POST['poll_groups'] as $key => $value) {
			$groups_for_db .= $separator . removeMagicQuotes($value);
			$separator = ",";
		}
		$groups_for_db = quoteString($groups_for_db);


		$sql = "INSERT INTO $poll (question, start, end, groups, owner) VALUES " .
			   "($question_for_db, $sdate_for_db, $edate_for_db, $groups_for_db, " . quoteString($uid) . ")";
		mysql_query($sql);

		// Commit answers into answers table.
		$sql = "SELECT LAST_INSERT_ID() AS lastid";
		$result = mysql_query($sql);
		if ($myrow = mysql_fetch_array($result)) {
			$pollid_for_db = quoteString($myrow['lastid']);
			foreach ($_POST['poll_answer'] as $key => $value) {
				$answer_for_db = quoteString(removeMagicQuotes($value));
				$sql = "INSERT INTO $poll_answers (pollid, answer) VALUES " .
					   "($pollid_for_db, $answer_for_db)";
						mysql_query($sql);
			}
		}
	}


	// Fills the tables with the edited poll data, the input is not validated (validate with checkPollInput()).
	function commitEditPollInput($poll, $poll_answers, $uid)
	{
		// Commit changes into poll table.
		$question_for_db = quoteString(removeMagicQuotes($_POST['poll_question']));
		$sdate_for_db = quoteString(removeMagicQuotes($_POST['poll_startdate']));
		$edate_for_db = quoteString(removeMagicQuotes($_POST['poll_enddate']));
		$pollid_for_db = quoteString(removeMagicQuotes($_POST['poll_id']));
		$groups_for_db = "";
		$separator = "";
		foreach ($_POST['poll_groups'] as $key => $value) {
			$groups_for_db .= $separator . removeMagicQuotes($value);
			$separator = ",";
		}
		$groups_for_db = quoteString($groups_for_db);

		$sql = "UPDATE $poll SET question=$question_for_db, " .
			   "start=$sdate_for_db, end=$edate_for_db, " .
			   "groups=$groups_for_db, owner=" . quoteString($uid) . " WHERE " .
			   "pollid=" . $pollid_for_db;
		mysql_query($sql);

		// Commit answers into answers table.
		$i = 0;
		foreach ($_POST['poll_answer'] as $key => $value) {
			$answer_id_for_db = quoteString(removeMagicQuotes($_POST['poll_answer_id'][$i]));
			$answer_for_db = quoteString(removeMagicQuotes($value));
			$sql = "UPDATE $poll_answers SET answer=$answer_for_db WHERE pollanswerid=$answer_id_for_db";
			mysql_query($sql);
			$i++;
		}
	}


	// Delete poll with id.
	function deletePoll($poll, $poll_answers, $poll_votes, $forumpoll_tablename, $pollid)
	{
		$pollid_for_db = quoteString(removeMagicQuotes($pollid));
		// Delete votes.
		$sql = "DELETE FROM " . $poll_votes . " WHERE " .
			   "pollid=" . $pollid_for_db;
		mysql_query($sql);
		// Delete answers.
		$sql = "DELETE FROM " . $poll_answers . " WHERE " .
			   "pollid=" . $pollid_for_db;
		mysql_query($sql);
		// Delete poll.
		$sql = "DELETE FROM " . $poll . " WHERE " .
			   "pollid=" . $pollid_for_db;
		mysql_query($sql);
		// Delete forum-poll connection.
		$sql = "DELETE FROM " . $forumpoll_tablename . " WHERE " .
			   "pollid=" . $pollid_for_db;
		mysql_query($sql);
	}


	// Exists poll with id?
	function existsPoll($poll, $pollid)
	{
		$pollid_for_db = quoteString(removeMagicQuotes($pollid));
		return existsEntry($poll, 'pollid', $pollid_for_db);
	}


	function votingAllowed($poll, $poll_voters_tbl, $ugroup, $uid_for_db, $pollid_for_db)
	{
		// Already voted?
		if ($ugroup == 'anonymous') {
			// Anonymous users can vote once per session.
			$i = 'poll_voted_' . $poll['pollid'];
			if (isset($_SESSION[$i])) {
				$voted = TRUE;
			} else {
				$voted = FALSE;
			}
		} else {
			// Registered user can just vote once.
			$sql = "SELECT * FROM $poll_voters_tbl WHERE pollid=$pollid_for_db AND userid=$uid_for_db";
			$result = mysql_query($sql);
			if (mysql_num_rows($result) == 0) {
				// Not voted yet.
				$voted = FALSE;
			} else {
				$voted = TRUE;
			}
		}

		// Poll open (start/end-date and time)
		$current_time = date("Y-m-d H:i:s", time());
		if ($poll['start'] <= $current_time && $current_time <= $poll['end']) {
			$active = TRUE;
		} else {
			$active = FALSE;
		}

		// Allowed to vote?
		if (strpos($poll['groups'], $ugroup) !== FALSE) {
			$permitted = TRUE;
		} else {
			$permitted = FALSE;
		}
		return $permitted && $active && !$voted;
	}


	function displayPoll($pollid, $poll_tbl, $poll_answers_tbl, $poll_voters_tbl, $uid, $ugroup, $path_to_root)
	{
		// Vote if not voted yet, allowed to vote, poll open, else just show result.
		$pollid_for_db = quoteString(removeMagicQuotes($pollid));
		$uid_for_db = quoteString(removeMagicQuotes($uid));
		$sql = "SELECT * FROM $poll_tbl WHERE pollid=$pollid_for_db";
		$result = mysql_query($sql);
		if ($poll = mysql_fetch_array($result)) {
			$sql = "SELECT * FROM $poll_answers_tbl WHERE pollid=$pollid_for_db ORDER BY pollanswerid ASC";
			$poll_answers_raw = mysql_query($sql);

			// Sum of all yet given votes.
			$sql = "SELECT SUM(count) AS votes FROM $poll_answers_tbl WHERE pollid=$pollid_for_db GROUP BY POLLID";
			$result = mysql_query($sql);
			$sumofvotes = mysql_fetch_array($result);
			$sumofvotes = $sumofvotes['votes'];

			$content = new Template($path_to_root . 'templates', 'keep');

			//if ($permitted && $active && !$voted) {
			if (votingAllowed($poll, $poll_voters_tbl, $ugroup, $uid_for_db, $pollid_for_db)) {
				// Show voting box.
				$content->set_file('poll', 'poll_vote.ihtml');
			} else {
				// Show result.
				$content->set_file('poll', 'poll_result.ihtml');
			}

			// Set poll data.
			$content->set_var(array(
				'PC_POLL_QUESTION'			=> htmlentities($poll['question']),
				'PC_POLL_VOTES'				=> $sumofvotes,
				'PC_POLL_ID'				=> $pollid,
				'PC_POLL_GROUPS'			=> $poll['groups'],
				'PC_POLL_STIME'				=> $poll['start'],
				'PC_POLL_ETIME'				=> $poll['end'],
				'ROOTPATH'					=> $path_to_root,
				'PC_POLL_PAGE'				=> $_SERVER['PHP_SELF'] . '?' . $_SERVER['QUERY_STRING']
			));

			// Set answer data.
			$content->set_block('poll', 'answer_row', 'answer_rows');
  			while ($myrow = mysql_fetch_array($poll_answers_raw)) {
            	$content->set_var(array(
					'PC_ANSWER_ID'			=> $myrow['pollanswerid'],
					'PC_ANSWER_TEXT'		=> htmlentities($myrow['answer']),
					'PC_ANSWER_COUNT'		=> $myrow['count'],
					'PC_ANSWER_PERCENT'		=> ($sumofvotes > 0) ? sprintf("%01.2f", 100*$myrow['count']/$sumofvotes) : '0.00',
					'PC_ANSWER_PERCENT2'		=> ($sumofvotes > 0) ? sprintf("%01.2f", 100 - 100*$myrow['count']/$sumofvotes) : '100.00'
				));
				$content->parse('answer_rows', 'answer_row', true);
			}
			$content->parse('OUTPUT', 'poll');
			return $content->get_var('OUTPUT');
		} else {
			return 'No Poll';
		}
	}


	// Check if there has been posted a voting, if the permissions and conditions are ok, commit.
	function checkAndCommitVote($poll_tbl, $poll_answers_tbl, $poll_voters_tbl, $uid, $ugroup)
	{
		// Check $POST variables
		if (isset($_POST['poll_submit']) && isset($_POST['poll_vote'])) {
			$answerid_for_db = quoteString(removeMagicQuotes($_POST['poll_vote']));
			$sql = "SELECT * FROM $poll_answers_tbl WHERE pollanswerid=$answerid_for_db";
			$result = mysql_query($sql);
			if ($answer = mysql_fetch_array($result)) {
				// We have an answer.
				$pollid_for_db = quoteString($answer['pollid']);
				$sql = "SELECT * FROM $poll_tbl WHERE pollid=$pollid_for_db";
				$result = mysql_query($sql);
				if ($poll = mysql_fetch_array($result)) {
					// We have also a poll.
					// Check if we are permitted to vote.
					$uid_for_db = quoteString(removeMagicQuotes($uid));
					if (votingAllowed($poll, $poll_voters_tbl, $ugroup, $uid_for_db, $pollid_for_db)) {
						// Ok, accept vote.
						// Mark user as voted.
						if ($ugroup == 'anonymous') {
							// Anonymous users can vote once per session.
							$i = 'poll_voted_' . $answer['pollid'];
							$_SESSION[$i] = TRUE;
						} else {
							// Registered user can just vote once.
							$sql = "INSERT INTO $poll_voters_tbl (pollid, pollanswerid, userid) VALUES " .
								   "($pollid_for_db, $answerid_for_db, $uid_for_db)";
							mysql_query($sql);
						}
						// Update the vote itself.
						$sql = "UPDATE $poll_answers_tbl SET count=count+1 WHERE pollanswerid=$answerid_for_db";
						mysql_query($sql);
					}
				}
			}
		}
	}

?>
