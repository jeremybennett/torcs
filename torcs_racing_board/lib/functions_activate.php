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


	// Check for outdated pending accounts and delete them.
	function cleanupPending($user_tablename, $confirm_tablename)
	{
		$date_now_for_db = quoteString(date("Y-m-d H:i:s", time() - ACTIVATION_EXPIRE));
		$sql = "SELECT id FROM " . $user_tablename . " WHERE " .
			   "active='pending' AND registered < " . $date_now_for_db;
		$result = mysql_query($sql);
		// TODO: Is it possible in mysql 3.x to express all that in one query?
		while ($myrow = mysql_fetch_array($result)) {
			$sql = "DELETE FROM " . $confirm_tablename . " WHERE " .
				   "id=" . quoteString($myrow['id']);
			mysql_query($sql);
			$sql = "DELETE FROM " . $user_tablename . " WHERE " .
				   "id=" . quoteString($myrow['id']);
			mysql_query($sql);
		}
	}

	// Try to activate account.
	function activateAccount($user_tablename, $confirm_tablename)
	{
		$ok = FALSE;
		if (isset($_GET['aid'])) {
			$aid_for_db = quoteString(removeMagicQuotes($_GET['aid']));
			// Because MySQL misses subselects... two steps.
			// Get unique user id to activate.
			$sql = "SELECT id FROM " . $confirm_tablename . " WHERE " .
				   "activationkey=" . $aid_for_db;
			$result = mysql_query($sql);
			$myrow = mysql_fetch_array($result);

			// If the user exists set the account to activated.
			if (isset($myrow['id'])) {
				$sql = "UPDATE " . $user_tablename . " SET active='activated' " .
					   "WHERE id=" . quoteString($myrow['id']) . " AND active='pending'";
				mysql_query($sql);
				if (mysql_errno() == 0) {
					// Ok, Delete activation key.
					$sql = "DELETE FROM " . $confirm_tablename . " WHERE " .
						   "id=" . quoteString($myrow['id']);
					mysql_query($sql);
					$ok = TRUE;
				}
			}
		}
		return $ok;
	}

?>
