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


	function displayQuestions($quizzid, $answers, $questions, $quizzquestions, $quizz, $path_to_root, $nextpage)
	{
		$sql = "SELECT qq.questionid, question FROM " .
			   "$quizzquestions qq, $questions q WHERE " .
			   "qq.quizzid=" . quoteString($quizzid) . " AND qq.questionid=q.questionid " .
			   "ORDER BY q.questionid";
		$result = mysql_query($sql);
		if (mysql_errno() == 0 && mysql_num_rows($result) > 0) {
			$nb_quest_avail =  mysql_num_rows($result);
			$sql = "SELECT nbquestions FROM $quizz WHERE quizzid=" . quoteString($quizzid);
			$nbqrow = mysql_fetch_array(mysql_query($sql));
			$nb_quest_req = $nbqrow['nbquestions'];
			$rand_max = getrandmax();
			$question_nb = intval(1);

			$content = new Template($path_to_root . 'templates', 'keep');
			$content->set_file('quizz', 'quizz_show.ihtml');
			$content->set_block('quizz', 'question_row', 'question_rows');
			$content->set_block('question_row', 'answer_row', 'answer_rows');

			while ($myrow = mysql_fetch_array($result)) {
				// Choose this question?
				$prob_q = $nb_quest_req / $nb_quest_avail;
				if (rand()/$rand_max <= $prob_q) {
					$sql = "SELECT * FROM $answers WHERE questionid=" . quoteString($myrow['questionid']);
					$ansres = mysql_query($sql);
					while ($ansrow = mysql_fetch_array($ansres)) {
						$content->set_var(array(
							'PC_QUIZZ_QUESTION_NB'	=> $question_nb,
							'PC_QUIZZ_ANSWER_TEXT'	=> htmlentities($ansrow['answer']),
							'PC_QUIZZ_QUESTION_ID'	=> $myrow['questionid'],
							'PC_QUIZZ_ANSWER_ID'	=> $ansrow['answerid']
						));
						$content->parse('answer_rows', 'answer_row', true);
					}
					$content->set_var(array(
						'PC_QUIZZ_QUESTION'	=> htmlentities($myrow['question'])
					));
					$content->parse('question_rows', 'question_row', true);
					$content->set_var('answer_rows', '');
					$nb_quest_req--;
					$question_nb++;
				}
				$nb_quest_avail--;
			}
			$content->set_var(array(
				'PC_QUIZZ_PAGE'	=> $nextpage,
				'PC_QUIZZ_ID'	=> $quizzid
			));
			$content->parse('OUTPUT', 'quizz');
			return $content->get_var('OUTPUT');
		} else {
			return 'No Quizz';
		}
	}


	// Returns number of errors or -1 in case of failure.
	// Return == 0 --> perfect.
	function checkAnswers($quizzid, $answers, $quizzquestions, $quizz)
	{
		// Input available?
		if (!isset($_POST['id_quizz']) || !isset($_POST['quizz_submit'])) {
			return -1;
		}
		// Quizzid ok?
		$postquizzid = intval(removeMagicQuotes($_POST['id_quizz']));
		if ($postquizzid != $quizzid) {
			return -1;
		}
		// Get quizz properties.
		$quizzid_for_db = quoteString($quizzid);
		$sql = "SELECT nbquestions,allowederrors FROM $quizz WHERE quizzid=$quizzid_for_db";
		$quizzprop = mysql_query($sql);
		if (mysql_errno() != 0 || mysql_num_rows($quizzprop) != 1) {
			return -1;
		}
		$quizzproprow = mysql_fetch_array($quizzprop);
		$allowederrors = $quizzproprow['allowederrors'];
		$nbanswers = $quizzproprow['nbquestions'];

		// Check the answers.
		$wrongans = intval(0);
		for ($i = intval(1); $i <= $nbanswers; $i++) {
			$varname = 'quizz_question_' . $i;
			if (isset($_POST[$varname])) {
				// Does answer belong to quizz and is true?
				$answer_for_db = quoteString(intval(removeMagicQuotes($_POST[$varname])));
				$sql = "SELECT * FROM $quizzquestions qq, $answers a WHERE " .
					   "qq.quizzid=$quizzid_for_db AND qq.questionid=a.questionid " .
					   "AND a.answerid=$answer_for_db AND a.true=1";
				$answer_result = mysql_query($sql);
				if (mysql_errno() > 0 || mysql_num_rows($answer_result) != 1) {
					$wrongans++;
				}
			} else {
				$wrongans++;
			}
		}
		if ($wrongans > $allowederrors) {
			return -1;
		} else {
			return $wrongans;
		}
	}


	// Changes the user into a racer.
	function toRacer($user_tablename, $uid)
	{
		$sql = "UPDATE $user_tablename SET account='racer' WHERE id=" . quoteString($uid);
		mysql_query($sql);
	}
?>
