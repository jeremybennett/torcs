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


	function checkAccountPasswords($pass1, $pass2, $uname, $fname, $lname, $email, $formerrors)
	{
		if ($pass1 != $pass2) {
			$formerrors |= ERR_PASSWORD_MISMATCH;
		}
		if (strlen($pass1) < MIN_PASSWORD_LENGTH) {
			// Special case, if we leave the field empty we want not to change the password.
			if ($pass1 != "") {
				$formerrors |= ERR_PASSWORD_LENGTH;
			}
		} else {
			// Check for trivial password, improve that.
			if (substr_count($uname, $pass1) > 0 ||
				substr_count($fname, $pass1) > 0 ||
				substr_count($lname, $pass1) > 0 ||
				substr_count($email, $pass1) > 0 ||
				(strlen($uname) > 0 && substr_count($pass1, $uname)) > 0 ||
				(strlen($fname) > 0 && substr_count($pass1, $fname)) > 0 ||
				(strlen($lname) > 0 && substr_count($pass1, $lname)) > 0 ||
				(strlen($email) > 0 && substr_count($pass1, $email)) > 0 ||
				substr_count($pass1, "password") > 0)
			{
				$formerrors |= ERR_PASSWORD_TOO_EASY;
			}
		}
		return $formerrors;
	}


	function checkAccountUsername($uname, $formerrors)
	{
		if (strlen($uname) < MIN_USERNAME_LENGTH) {
			$formerrors |= ERR_USERNAME_TOO_SHORT;
		} elseif (strlen($uname) > MAX_USERNAME_LENGTH) {
			$formerrors |= ERR_USERNAME_TOO_LONG;
		}
		if (!validateUsername($uname)) {
			$formerrors |= ERR_USERNAME_CHARS;
		}
		return $formerrors;
	}


	function checkAccountEmail($email, $formerrors)
	{
		if (strlen($email) > MAX_EMAIL_LENGTH) {
			$formerrors |= ERR_EMAIL_TOO_LONG;
		}
		if (!validateEMail($email)) {
			$formerrors |= ERR_EMAIL_CHARS;
		}
		return $formerrors;
	}


	function checkAccountNames($fname, $lname, $formerrors)
	{
		if (strlen($fname) > MAX_USERNAME_LENGTH) {
			$formerrors |= ERR_FNAME_TOO_LONG;
		}
		if (strlen($lname) > MAX_USERNAME_LENGTH) {
			$formerrors |= ERR_LNAME_TOO_LONG;
		}
		return $formerrors;
	}


	function checkAccountInput()
	{
		$formerrors = intval(0);
		$t_password = isset($_POST['account_password']) ? removeMagicQuotes($_POST['account_password']) : "";
		$t_password2 = isset($_POST['account_password2']) ? removeMagicQuotes($_POST['account_password2']) : "";
		$t_username = isset($_POST['account_username']) ? removeMagicQuotes($_POST['account_username']) : "";
		$t_firstname = isset($_POST['account_firstname']) ? removeMagicQuotes($_POST['account_firstname']) : "";
		$t_lastname = isset($_POST['account_lastname']) ? removeMagicQuotes($_POST['account_lastname']) : "";
		$t_email = isset($_POST['account_email']) ? removeMagicQuotes($_POST['account_email']) : "";

		$formerrors = checkAccountPasswords(
			$t_password,
			$t_password2,
			$t_username,
			$t_firstname,
			$t_lastname,
			$t_email,
			$formerrors
		);
		//$formerrors = checkAccountUsername($t_username, $formerrors);
		$formerrors = checkAccountEmail($t_email, $formerrors);
		$formerrors = checkAccountNames($t_firstname, $t_lastname, $formerrors);
		return $formerrors;
	}


	function commitAccountInput($user_tablename, $uid)
	{
		$formerrors = intval(0);
		$password = isset($_POST['account_password']) ? removeMagicQuotes($_POST['account_password']) : "";
		$firstname = isset($_POST['account_firstname']) ? removeMagicQuotes($_POST['account_firstname']) : "";
		$lastname = isset($_POST['account_lastname']) ? removeMagicQuotes($_POST['account_lastname']) : "";
		$email = isset($_POST['account_email']) ? removeMagicQuotes($_POST['account_email']) : "";
		$uid_for_db = quoteString(removeMagicQuotes($uid));

		$update = "";
		$sep = " SET ";
		$update .= ($password != "") ? $sep . " password=" . quoteString(md5($password)) : "";
		$sep = ($update == "") ? " SET " : " , ";
		$update .= ($firstname != "") ? $sep . " firstname=" . quoteString($firstname) : "";
		$sep = ($update == "") ? " SET " : " , ";
		$update .= ($lastname != "") ? $sep . " lastname=" . quoteString($lastname) : "";
		$sep = ($update == "") ? " SET " : " , ";
		$update .= ($email != "") ? $sep . " email=" . quoteString($email) : "";

		$sql = "UPDATE " . $user_tablename . $update .
			   " WHERE id=" . $uid_for_db;
		mysql_query($sql);
		if (mysql_errno() != 0) {
			// Update failed, what was the cause?
			if (existsEntry($user_tablename, "email", quoteString($email))) {
				$formerrors |= ERR_EMAIL_EXISTS;
			}
		}
		return $formerrors;
	}


	function commitRacerPhoto($uid, $path_to_root)
	{
		commitJPEGImage(
			$uid,
			$path_to_root,
			'racer_image',
			20000,
			'images/users/',
			150,
			150,
			50,
			50,
			90
		);
	}

?>
