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


	function cleanupPendingPasswordRequests($lostpwd_tablename)
	{
		// Delete outdated password requests.
		$date_expire_for_db = quoteString(date("YmdHis", time() - PASSWORD_REQUEST_EXPIRE));
		$sql = "DELETE FROM " . $lostpwd_tablename . " WHERE requestdate < " . $date_expire_for_db;
		mysql_query($sql);
	}

	function requestNewPassword($user_tablename, $lostpwd_tablename, $path_to_root)
	{
		if (isset($_POST['lostpassword_email'])) {
			// Look up e-main in db.
			$email_for_db = quoteString(removeMagicQuotes($_POST['lostpassword_email']));
			$sql = "SELECT * FROM " . $user_tablename . " WHERE email=" . $email_for_db;
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				// Ok, e-mail exists.
				// Create key.
				$activationkey = rand() . $_SERVER['REMOTE_ADDR'] . $email_for_db . time();
				$activationkey = md5($activationkey);
				$activationkey_for_db = quoteString($activationkey);
				// Write key.
				$sql = "INSERT INTO " . $lostpwd_tablename . " (id, activationkey) " .
					   "VALUES(" . quoteString($myrow['id']) . "," . $activationkey_for_db . ")";
				mysql_query($sql);

				if (mysql_errno() == 0) {
					// Compose and send mail.
					$activation = dirname($_SERVER['REQUEST_URI']) . "/" . "lostpassword.php";
					$tmpl_mail = new Template($path_to_root . 'templates', 'keep');
					$tmpl_mail->set_file(array("themail" => "lostpasswordrequestmail.tpl"));
					$tmpl_mail->set_var(array(
						'USERNAME'		=> $myrow['username'],
						'SERVERNAME'	=> $_SERVER['SERVER_NAME'],
						'ACTIVATION'	=> $activation,
						'KEY'			=> urlencode($activationkey)
					));
					$tmpl_mail->parse("MAIL", array("themail"));

					mail(
						removeMagicQuotes($_POST['lostpassword_email']),
						"Lost Account Password on " . SERVER_NAME,
						$tmpl_mail->get_var("MAIL"),
						"From: " . REGISTER_EMAIL . "\r\n" .
						"Reply-To: " . REGISTER_EMAIL . "\r\n"
					);
					return TRUE;
				} else {
					return FALSE;
				}
			} else {
				// Hmm, e-mail not found.
				return FALSE;
			}
		}
		return FALSE;
	}

	function sendNewPassword($user_tablename, $lostpwd_tablename, $path_to_root)
	{
		if (isset($_GET['aid'])) {
			// Check if aid is valid.
			$aid = removeMagicQuotes($_GET['aid']);
			$aid_for_db = quoteString($aid);
			$sql = "SELECT * FROM " . $lostpwd_tablename . " a, " . $user_tablename . " u " .
				   "WHERE a.activationkey=" . $aid_for_db . " AND a.id = u.id";
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				// Delete aid.
				$sql = "DELETE FROM " . $lostpwd_tablename . " WHERE id=" . quoteString($myrow['id']);
				mysql_query($sql);
				// Ok, reset password.
				$password = md5(rand() . $_SERVER['REMOTE_ADDR'] . time() . session_id());
				$password = substr($password, 7, 7);
				$password_for_db = quoteString(md5($password));
				$sql = "UPDATE " . $user_tablename . " SET password=" . $password_for_db . " " .
					   "WHERE id=" . quoteString($myrow['id']);
				mysql_query($sql);
				if (mysql_errno() == 0) {
					// Send mail.
					$tmpl_mail = new Template($path_to_root . 'templates', 'keep');
					$tmpl_mail->set_file(array("themail" => "lostpasswordmail.tpl"));
					$tmpl_mail->set_var(array(
						'USERNAME'		=> $myrow['username'],
						'SERVERNAME'	=> $_SERVER['SERVER_NAME'],
						'PASSWORD'		=> $password
					));
					$tmpl_mail->parse("MAIL", array("themail"));

					mail(
						$myrow['email'],
						"Your New Password for " . SERVER_NAME,
						$tmpl_mail->get_var("MAIL"),
						"From: " . REGISTER_EMAIL . "\r\n" .
						"Reply-To: " . REGISTER_EMAIL . "\r\n"
					);

					return TRUE;
				} else {
					return FALSE;
				}
			} else {
				return FALSE;
			}
		}
		return FALSE;
	}

?>

