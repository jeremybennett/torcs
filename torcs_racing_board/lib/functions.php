<?php

/*
	copyright   : (C) 2004 Bernhard Wymann
	email       : berniw@bluewin.ch
	version     : $Id$

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	Some functions (c) PHPbb, phpbb.com, licensed under the GPL, the
	functions are tagged with "(c) PHPbb".
*/

//ini_set('display_errors','1');
//error_reporting(E_ALL);
error_reporting(0);

// Check if table already exists.
// Preconditions: DB Connected and Selected.
// Input:
// $tablename: Table name, must be alrady quoted..
// Comment: Does NOT check for SQL-injection!
function existsTable($tablename)
{
	$sql = "SELECT * FROM " . $tablename;
	return mysql_query($sql);
}


// Check if entry alredy exists in database.
// Preconditions: DB Connected and Selected.
// $tablename: Table name.
// Comment: Does NOT check for SQL-injection!
function existsEntry($tablename, $identifier, $value)
{
	$sql = "SELECT * FROM $tablename WHERE $identifier = $value";
	$result = mysql_query($sql);
	if (mysql_fetch_row($result)) {
		return TRUE;
	} else {
		return FALSE;
	}
}


// Sets the session defaults in the global $_SESSION variables.
// Preconditions: Requires previously session_start().
function session_defaults()
{
	$_SESSION['logged'] = FALSE;
	$_SESSION['uid'] = 0;
	$_SESSION['username'] = '';
	$_SESSION['cookie'] = 0;
	$_SESSION['remember'] = FALSE;
	$_SESSION['usergroup'] = 'anonymous';
}


// Updates the hit counter of the given page in $page in the $table.
// Requires an existing db connection.
function countHit($page, $table)
{
	$page_for_db = quoteString($page);
	// If it exists update.
	$sql = "UPDATE " . $table . " SET hits=hits+1 WHERE page=" . $page_for_db;
	mysql_query($sql);
	if (mysql_affected_rows() == 0) {
		// Create.
		$sql = "INSERT INTO " . $table . " (page, hits) VALUES " .
			   "($page_for_db, '1')";
		mysql_query($sql);
	}
}


// Updates the list of active sessions and the session statistics.
// Requires an existing db connection.
function countSession($session, $table, $stats_table)
{
	// Delete outdated sessions.
	$date_expire_for_db = quoteString(date("YmdHis", time() - SESSION_STATS_EXPIRE));
	$sql = "DELETE FROM " . $table . " WHERE start < " . $date_expire_for_db;
	mysql_query($sql);

	// Check if session exists.
	$session_for_db = quoteString($session);
	$sql = "SELECT * FROM " . $table . " WHERE session=" . $session_for_db;
	$result = mysql_query($sql);
	if (mysql_num_rows($result) == 0) {
		$sql = "INSERT INTO " . $table . " (session) VALUES ($session_for_db)";
		mysql_query($sql);
		// Update visits counter.
		$sql = "UPDATE " . $stats_table . " SET value=value+1 WHERE name='visits'";
		mysql_query($sql);
	}
}


// Logout.
function session_logout()
{
	session_defaults();
	// Expire cookie, so the browser should get rid of it.
	// TODO: Timezone on browser?
	setcookie(COOKIE_NAME, "", time() - COOKIE_EXPIRE, COOKIE_DIR, COOKIE_DOMAIN);
	setcookie('PHPSESSID', "", time() - COOKIE_EXPIRE, '/');
}


// Returns TRUE if logged in, FLASE if not. The $_SESSION variables
// are set (look at session_defaults).
function checkLogin(&$user)
{
	if ($_SESSION['logged'] == TRUE) {
		// Already logged in, do nothing.
		return TRUE;
	} else {
		if (isset($_POST['login_submit']) &&
			isset($_POST['login_username']) &&
			isset($_POST['login_password']))
		{
			return $user->_checkLogin(
						removeMagicQuotes($_POST['login_username']),
						removeMagicQuotes($_POST['login_password']),
						isset($_POST['login_remember'])
				   );
		} else {
			return FALSE;
		}
	}
}


function checkLogout()
{
	if ($_SESSION['logged'] == TRUE) {
		// Ok, possible to log out.
		if (isset($_GET['logout'])) {
			session_logout();
		}
	}
}


// Quote table or column identifier.
function quoteIdentifier($in)
{
	$in = htmlentities(stripslashes($in));
	return '`' . $in . '`';
}


// Prepare strings to avoid SQL-injection.
// True and false is converted to 0/1.
// NULL is converted to 'NULL'
function quoteString($in)
{
	//$in = htmlentities(stripslashes($in));
	if (is_int($in) || is_double($in)) {
		return $in;
	} elseif (is_bool($in)) {
		return $in ? 1 : 0;
	} elseif (is_null($in)) {
		return 'NULL';
	} else {
		return "'" . mysql_real_escape_string($in) . "'";
	}
}


// Check if the pattern matches a possible e-mail address (c) PHPbb.
function validateEMail($email)
{
	return preg_match('/^[a-z0-9&\'\.\-_\+]+@[a-z0-9\-]+\.([a-z0-9\-]+\.)*?[a-z]+$/', $email);
}


// Check if the pattern matches an URL (c) PHPbb.
function validateURL($url)
{
	return preg_match('#^http[s]?\\:\\/\\/[a-z0-9\-]+\.([a-z0-9\-]+\.)?[a-z]+#i', $url);
}


// (c) PHPbb
function validateUsername($uname) {
	return preg_match('/^[a-z0-9&\'\.\-_\+]+$/', $uname);
}


// Remove magic slashes for simple variables.
function removeMagicQuotes($var)
{
	if (get_magic_quotes_gpc()) {
		return stripslashes($var);
	} else {
		return $var;
	}
}


// Convert mysql timestamp to YYYY-MM-DD HH:MM:SS
function mysqlToTime($time)
{
	return substr($time, 0, 4) . "-" . substr($time, 4, 2) . "-" . substr($time, 6, 2) . " " .
		   substr($time, 8, 2) . ":" . substr($time, 10, 2) . ":" . substr($time, 12, 2);
}


?>
