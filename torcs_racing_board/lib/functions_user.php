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

	function changeUserState($user_tablename, $rawid, $state)
	{
		$id = intval(removeMagicQuotes($rawid));
		if ($id != $_SESSION['uid']) {
			$id_for_db = quoteString($id);
			$sql = "UPDATE $user_tablename SET active='$state' WHERE id=$id_for_db";
			mysql_query($sql);
		}
	}


	function processUserState($user_tablename)
	{
		if (isset($_GET['activate'])) {
			changeUserState($user_tablename, $_GET['activate'], 'activated');
		} elseif (isset($_GET['disable'])) {
			changeUserState($user_tablename, $_GET['disable'], 'disabled');
		}
	}


?>
