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


	define('ERR_PASSWORD_MISMATCH', 1 << 0);
	define('ERR_PASSWORD_LENGTH',   1 << 1);
	define('ERR_USERNAME_TOO_SHORT',1 << 2);
	define('ERR_USERNAME_TOO_LONG', 1 << 3);
	define('ERR_USERNAME_CHARS',    1 << 4);
	define('ERR_USERNAME_EXISTS',   1 << 5);
	define('ERR_EMAIL_TOO_LONG', 	1 << 6);
	define('ERR_EMAIL_CHARS',    	1 << 7);
	define('ERR_EMAIL_EXISTS',   	1 << 8);
	define('ERR_FNAME_TOO_LONG',	1 << 9);
	define('ERR_LNAME_TOO_LONG',	1 << 10);
	define('ERR_PASSWORD_RQRD',		1 << 11);
	define('ERR_PASSWORD2_RQRD',	1 << 12);
	define('ERR_EMAIL_RQRD',		1 << 13);
	define('ERR_FNAME_RQRD',		1 << 14);
	define('ERR_LNAME_RQRD',		1 << 15);
	define('ERR_USERNAME_RQRD',		1 << 16);
	define('ERR_PASSWORD_TOO_EASY', 1 << 17);



	function isMailOk($error, &$msg)
	{
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_EMAIL_TOO_LONG) {
			$msg .= "too long";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_EMAIL_CHARS) {
			$msg .= $sep . "illegal string";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_EMAIL_EXISTS) {
			$msg .= $sep . "already in use";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_EMAIL_RQRD) {
			$msg .= $sep . "is required";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function isPasswordOk($error, &$msg)
	{
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_PASSWORD_LENGTH) {
			$msg .= "too short";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_PASSWORD_MISMATCH) {
			$msg .= $sep . "passwords do not match";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & (ERR_PASSWORD_RQRD | ERR_PASSWORD2_RQRD)) {
			$msg .= $sep . "passwords required";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_PASSWORD_TOO_EASY) {
			$msg .= $sep . "password too easy (choose another password)";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function isUsernameOk($error, &$msg)
	{
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_USERNAME_TOO_LONG) {
			$msg .= "too long";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_USERNAME_TOO_SHORT) {
			$msg .= "too short";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_USERNAME_CHARS) {
			$msg .= $sep . "illegal characters (just lowercase allowed)";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_USERNAME_EXISTS) {
			$msg .= $sep . "already in use";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_USERNAME_RQRD) {
			$msg .= $sep . "is required";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function isFirstnameOk($error, &$msg)
	{
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_FNAME_TOO_LONG) {
			$msg .= "too long";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_FNAME_RQRD) {
			$msg .= "is required";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function isLastnameOk($error, &$msg)
	{
		$ok = TRUE;
		$msg = "";
		$sep = "";
		if ($error & ERR_LNAME_TOO_LONG) {
			$msg .= "too long";
			$sep = ", ";
			$ok = FALSE;
		}
		if ($error & ERR_LNAME_RQRD) {
			$msg .= "is required";
			$sep = ", ";
			$ok = FALSE;
		}
		return $ok;
	}


	function checkRegisterInput()
	{
		$formerrors = intval(0);

		// Check password.
		if (isset($_POST['register_password']) && isset($_POST['register_password2'])) {
			if ($_POST['register_password'] != $_POST['register_password2']) {
				$formerrors |= ERR_PASSWORD_MISMATCH;
			}

			if (strlen(removeMagicQuotes($_POST['register_password'])) > MAX_USERNAME_LENGTH) {
				die("Spammer...");
			}

			if (strlen(removeMagicQuotes($_POST['register_password'])) < MIN_PASSWORD_LENGTH) {
				$formerrors |= ERR_PASSWORD_LENGTH;
			} else {
				// Check for trivial password, improve that.
				if (isset($_POST['register_username']) &&
					isset($_POST['register_firstname']) &&
					isset($_POST['register_lastname']) &&
					isset($_POST['register_email']))
				{
					$t_password = removeMagicQuotes($_POST['register_password']);
					$t_username = removeMagicQuotes($_POST['register_username']);
					$t_firstname = removeMagicQuotes($_POST['register_firstname']);
					$t_lastname = removeMagicQuotes($_POST['register_lastname']);
					$t_email = removeMagicQuotes($_POST['register_email']);
					if (substr_count($t_username, $t_password) > 0 ||
						substr_count($t_firstname, $t_password) > 0 ||
						substr_count($t_lastname, $t_password) > 0 ||
						substr_count($t_email, $t_password) > 0 ||
						(strlen($t_username) > 0 && substr_count($t_password, $t_username)) > 0 ||
						(strlen($t_firstname) > 0 && substr_count($t_password, $t_firstname)) > 0 ||
						(strlen($t_lastname) > 0 && substr_count($t_password, $t_lastname)) > 0 ||
						(strlen($t_email) > 0 && substr_count($t_password, $t_email)) > 0 ||
						substr_count($t_password, "password") > 0
					)
					{
						$formerrors |= ERR_PASSWORD_TOO_EASY;
					}
				}
			}
		} else {
			if (!isset($_POST['register_password'])) {
				$formerrors |= ERR_PASSWORD_RQRD;
			}
			if (!isset($_POST['register_password2'])) {
				$formerrors |= ERR_PASSWORD_RQRD2;
			}
		}

		// Check username.
		if (isset($_POST['register_username'])) {
			$tmp_username = removeMagicQuotes($_POST['register_username']);
			if (strlen($tmp_username) < MIN_USERNAME_LENGTH) {
				$formerrors |= ERR_USERNAME_TOO_SHORT;
			} elseif (strlen($tmp_username) > MAX_USERNAME_LENGTH) {
				$formerrors |= ERR_USERNAME_TOO_LONG;
			}
			if (!validateUsername($tmp_username)) {
				$formerrors |= ERR_USERNAME_CHARS;
			}
		} else {
			$formerrors |= ERR_USERNAME_RQRD;
		}

		// Check email
		if (isset($_POST['register_email'])) {
			$tmp_email = removeMagicQuotes($_POST['register_email']);
			if (strlen($tmp_email) > MAX_EMAIL_LENGTH) {
				$formerrors |= ERR_EMAIL_TOO_LONG;
			}
			if (!validateEMail($tmp_email)) {
				$formerrors |= ERR_EMAIL_CHARS;
			}
		} else {
			$formerrors |= ERR_EMAIL_RQRD;
		}

		// Check first name and last name.
		if (!isset($_POST['register_firstname'])) {
			$formerrors |= ERR_FNAME_RQRD;
		} else {
			if (strlen(removeMagicQuotes($_POST['register_firstname'])) > MAX_USERNAME_LENGTH) {
				$formerrors |= ERR_FNAME_TOO_LONG;
			}
		}
		if (!isset($_POST['register_lastname'])) {
			$formerrors |= ERR_LNAME_RQRD;
		} else {
			if (strlen(removeMagicQuotes($_POST['register_lastname'])) > MAX_USERNAME_LENGTH) {
				$formerrors |= ERR_LNAME_TOO_LONG;
			}
		}

		return $formerrors;
	}


	function commitRegisterInput($user_tablename, $confirm_tablename, $path_to_root)
	{
		$formerrors = intval(0);
		$password_for_db = quoteString(md5(removeMagicQuotes($_POST['register_password'])));
		$username_for_db = quoteString(removeMagicQuotes($_POST['register_username']));
		$email_for_db = quoteString(removeMagicQuotes($_POST['register_email']));
		$firstname_for_db = quoteString(removeMagicQuotes($_POST['register_firstname']));
		$lastname_for_db = quoteString(removeMagicQuotes($_POST['register_lastname']));
		$cookie = "${_SERVER['REMOTE_ADDR']}" . $username_for_db .
				  time() . strlen($username_for_db) . session_id();
		$cookie_for_db = quoteString(md5($cookie));

		// Try to insert new user record, optimistic approach.
		$sql = "INSERT INTO " . $user_tablename . " (username, password, cookie, email, firstname, lastname) " .
			   "VALUES ($username_for_db, $password_for_db, $cookie_for_db, $email_for_db, $firstname_for_db, $lastname_for_db)";
		mysql_query($sql);
		if (mysql_errno() != 0) {
			// Insert failed, what was the cause?
			if (existsEntry($user_tablename, "username", $username_for_db)) {
				$formerrors |= ERR_USERNAME_EXISTS;
			}

			if (existsEntry($user_tablename, "email", $email_for_db)) {
				$formerrors |= ERR_EMAIL_EXISTS;
			}
		}

		// If everything went perfect set up activation and send mail.
		if ($formerrors == 0) {
			// Create activation key.
			$activationkey = rand() . $_SERVER['REMOTE_ADDR'] . $username_for_db .
							 time() . strlen($username_for_db);
			$activationkey = md5($activationkey);
			$activationkey_for_db = quoteString($activationkey);

			// Find user id.
			$sql = "SELECT id FROM " . $user_tablename . " WHERE username=" . $username_for_db;
			$result = mysql_query($sql);
			$myrow = mysql_fetch_array($result);

			// Create date.
			$date_now_for_db = quoteString(date("Y-m-d H:i:s"));

			// Store registration date.
			$sql = "UPDATE " . $user_tablename . " SET registered=" . $date_now_for_db .
				   " WHERE id=" . quoteString($myrow['id']);
			mysql_query($sql);

			// Store registration key.
			$sql = "INSERT INTO " . $confirm_tablename . " (id, activationkey) " .
				   "VALUES (" . quoteString($myrow['id']) . ", $activationkey_for_db)";
			mysql_query($sql);

			// Create activation mail content.
			$activation = dirname($_SERVER['REQUEST_URI']) . "/" . "activate.php";
			$tmpl_mail = new Template($path_to_root . 'templates', 'keep');
			$tmpl_mail->set_file(array("themail" => "activationmail.tpl"));
			$tmpl_mail->set_var(array(
				'USERNAME'		=> removeMagicQuotes($_POST['register_username']),
				'PASSWORD'		=> removeMagicQuotes($_POST['register_password']),
				'SERVERNAME'	=> $_SERVER['SERVER_NAME'],
				'ACTIVATION'	=> $activation,
				'KEY'			=> urlencode($activationkey)
			));
			$tmpl_mail->parse("MAIL", array("themail"));

			mail(
				removeMagicQuotes($_POST['register_email']),
				"Welcome at " . SERVER_NAME,
				$tmpl_mail->get_var("MAIL"),
				"From: " . REGISTER_EMAIL . "\r\n" .
				"Reply-To: " . REGISTER_EMAIL . "\r\n"
			);
		}
		return $formerrors;
	}

?>
