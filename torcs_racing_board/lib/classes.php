<?php

/*
	copyright   : (C) 2004 Bernhard Wymann
	email       : berniw@bluewin.ch
	version     : $Id$

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	Class and functions to provide logins/accounts.

	The User class which was the base for this file has the
	following license/copyright:

	Copyright (c) 2001, 2002 by Martin Tsachev. All rights reserved.
	mailto:martin@f2.org
	http://martin.f2o.org

	Redistribution and use in source and binary forms,
	with or without modification, are permitted provided
	that the conditions available at
	http://www.opensource.org/licenses/bsd-license.html
	are met.
*/

class User {
	var $db = NULL;			// DB pointer
	var $failed = FALSE;	// failed login attempt
	var $id = 0;			// the current user's id.
	var $usertable = NULL;	// Table name (user data).
	var $loginlog = NULL;

	function User(&$db, $tablename, $loginlog)
	{
		$this->db = $db;
		$this->loginlog = $loginlog;
		$this->usertable = $tablename;
		if ($_SESSION['logged']) {
			$this->_checkSession();
		} elseif (isset($_COOKIE[COOKIE_NAME])) {
			$this->_checkRemembered(removeMagicQuotes($_COOKIE[COOKIE_NAME]));
		}
	}


	function _loginLog($uid, $pass, $username)
	{
		// Delete outdated login entries.
		$date_expire_for_db = quoteString(date("YmdHis", time() - LOGIN_LOG_EXPIRE));
		$sql = "DELETE FROM " . $this->loginlog . " WHERE time < " . $date_expire_for_db;
		mysql_query($sql);

		// Collect entries or create a new one?
		$uid_for_db = quoteString($uid);
		$ip_for_db= quoteString($_SERVER['REMOTE_ADDR']);
		$pass_for_db = quoteString($pass);
		$date_collect_for_db = quoteString(date("YmdHis", time() - LOGIN_LOG_NEWENTRY));

		$sql = "SELECT * FROM " . $this->loginlog . " WHERE " .
			   "id=" . $uid_for_db . " AND " .
			   "ip=" . $ip_for_db . " AND " .
			   "pf=" . $pass_for_db . " AND " .
			   "username=" . $username . " AND " .
			   "time > " . $date_collect_for_db . " " .
			   "ORDER BY time DESC";
		$result = mysql_query($sql);
		if ($myrow = mysql_fetch_array($result)) {
			// Increment counter of existing entry.
			$sql = "UPDATE " . $this->loginlog . " SET count=count+1 " .
				   "WHERE " .
				   "id=" . $uid_for_db . " AND " .
				   "ip=" . $ip_for_db . " AND " .
				   "pf=" . $pass_for_db . " AND " .
				   "username=" . $username . " AND " .
				   "time=" . quoteString($myrow['time']);
			mysql_query($sql);
		} else {
			// New entry.
			$sql = "INSERT INTO " . $this->loginlog . " (id, ip, pf, username) VALUES " .
				   "($uid_for_db, $ip_for_db, $pass_for_db, $username)";
			mysql_query($sql);
		}
	}


	function _setNow($uid, $colname)
	{
		$date_now_for_db = quoteString(date("Y-m-d H:i:s", time()));
		$sql = 	"UPDATE " . $this->usertable . " SET " .
			    $colname . "=" . $date_now_for_db . " WHERE id =" . quoteString($this->id);
		mysql_query($sql);
	}


	function _setLastLogin($uid)
	{
		$this->_setNow($uid,  "lastlogin");
	}


	function _setLastVisit($uid)
	{
		$this->_setNow($uid, "lastvisit");
	}


	function _checkLogin($username, $password, $remember)
	{
		$username = quoteString(substr($username, 0, MAX_USERNAME_LENGTH));
		$password = quoteString(md5($password));
		$sql = 	"SELECT * FROM " . $this->usertable . " WHERE " .
			"(username = $username) AND " .
			"(password = $password) AND " .
			"(active = 'activated')";
		$result = mysql_query($sql);
		if ($myrow = mysql_fetch_array($result)) {
			$this->_setSession($myrow, $remember);
			$this->_setLastLogin($_SESSION['uid']);
			$this->_loginLog($_SESSION['uid'], 'passed', $username);
			return TRUE;
		} else {
			$this->failed = TRUE;
			$this->_logout();
			$this->_loginLog(0, 'failed', $username);
			return FALSE;
		}
	}


	function _setSession(&$values, $remember, $init = TRUE)
	{
		// $values comes from the database, not from outside.
		$this->id = $values['id'];
		$_SESSION['uid'] = $this->id;
		$_SESSION['username'] = htmlentities($values['username']);
		//$_SESSION['username'] = htmlspecialchars($values['username']);
		$_SESSION['cookie'] = $values['cookie'];
		$_SESSION['logged'] = TRUE;
		$_SESSION['usergroup'] = $values['account'];
		if ($remember) {
			$this->updateCookie($values['cookie'], TRUE);
		}
		if ($init) {
			$session = quoteString(session_id());
			$ip = quoteString($_SERVER['REMOTE_ADDR']);
			$sql = 	"UPDATE " . $this->usertable . " SET " .
					"session = $session, ip = $ip WHERE id =" . quoteString($this->id);
			mysql_query($sql);
		}
	}


	function updateCookie($cookie, $save)
	{
		$_SESSION['cookie'] = $cookie;
		if ($save) {
			$cookie = serialize(array($_SESSION['username'], $cookie));
			setcookie(COOKIE_NAME, $cookie, time() + COOKIE_EXPIRE,
					  COOKIE_DIR, COOKIE_DOMAIN);
		}
	}


	function _checkRemembered($cookie)
	{
		list($username, $cookie) = unserialize($cookie);
		if (!$username or !$cookie) {
			return;
		} else {
			// Cookie comes from client, danger!
			$username = quoteString(substr($username, 0, MAX_USERNAME_LENGTH));
			$cookie = quoteString($cookie);
			$sql = 	"SELECT * FROM "  . $this->usertable . " WHERE " .
				"(username = $username) AND (cookie = $cookie) AND " .
				"(active = 'activated')";
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				$this->_setSession($myrow, TRUE);
				$this->_setLastVisit($_SESSION['uid']);
			}
		}
	}


	function _checkSession()
	{
		$username = quoteString($_SESSION['username']);
		$cookie = quoteString($_SESSION['cookie']);
		$session = quoteString(session_id());
		$ip = quoteString($_SERVER['REMOTE_ADDR']);
		$sql = 	"SELECT * FROM " . $this->usertable . " WHERE " .
			"(username = $username) AND (cookie = $cookie) AND" .
			"(session = $session) AND (ip = $ip) AND " .
			"(active = 'activated')";
		$result = mysql_query($sql);
		if ($myrow = mysql_fetch_array($result)) {
			$this->_setSession($myrow, FALSE, FALSE);
		} else {
			$this->_logout();
		}
	}


	function _logout()
	{
		session_defaults();
	}
}

?>
