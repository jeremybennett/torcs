<?php

/*
	copyright   : (C) 2007 Bernhard Wymann
	email       : berniw@bluewin.ch
	version     : $Id$

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
*/


	// Returns > 0 if errors are detected.
	function checkBulkMailInput()
	{
		$errors = intval(0);
		// Check if subject and body are not empty.
		if (!(isset($_POST['subject']) && strlen($_POST['subject']) > 0)) {
			$errors += 1;
		}

		if (!(isset($_POST['text']) && strlen($_POST['text']) > 0)) {
			$errors += 1;
		}

		// Check groups, at least one must be selected.
		if (isset($_POST['mail_groups']) && count($_POST['mail_groups']) > 0) {
			foreach ($_POST['mail_groups'] as $key => $value) {
				if ($value != 'admin' && $value != 'spectator' && $value != 'racer') {
					$errors += 1;
				}
			}
		} else {
			$errors += 1;
		}

		return $errors;
	}


	// Send mail to selected groups.
	function sendMails($user_tablename, $uid)
	{
		if ($_SESSION['usergroup'] != 'admin') {
			return 0;
		}		

		// Get list with all e-mail addresses, correctness of groups strings is checked by other function and
		// must be correct here (SQL-Injection, etc).
		$sql = "SELECT email FROM $user_tablename WHERE ";
		$separator = "";	
		foreach ($_POST['mail_groups'] as $key => $value) {
			$sql .= $separator . " account=" . quoteString($value);
			$separator = " OR ";
		}

		$failed = 0;
		$result = mysql_query($sql);
		while ($myrow = mysql_fetch_array($result)) {
			$success = mail(
				$myrow['email'],
				removeMagicQuotes($_POST['subject']),
				removeMagicQuotes($_POST['text']),
				"From: " . ADMIN_EMAIL . "\r\n" . "Reply-To: " . ADMIN_EMAIL . "\r\n"
			);
			
			if ($success == FALSE) {
				$failed++;
			}
		}

		return $failed;
	}

?>
