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


	function checkSShotInput()
	{
		$formerrors = intval(0);

		// Check description.
		$formerrors += checkPostString('sshot_description', 0, 100);
		// Check file.
		$formerrors += checkPostFile('sshot_image', 100000, 'image/jpeg');

		return $formerrors;
	}


	function commitSShotInput($sshot_tablename, $path_to_root)
	{
		$desc_for_db = isset($_POST['sshot_description']) ? quoteString(removeMagicQuotes($_POST['sshot_description'])) : "''";

		$file = $_FILES['sshot_image'];

		// Commit data.
		$sql = "INSERT INTO $sshot_tablename " .
			   "(description) VALUES ($desc_for_db)";
		mysql_query($sql);

		// Move file (picture).
		if (mysql_affected_rows() > 0) {
			$sql = "SELECT LAST_INSERT_ID() AS lastid";
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				$shotid = $myrow['lastid'];
				commitJPEGImage(
					$shotid, $path_to_root, 'sshot_image', 100000, 'images/screenshots/',
					620, 465, 140, 105, 90
				);
			}
		}
	}


	function deleteSShot($sshot_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin' &&
			isset($_GET['deleteshotid']))
		{
			$id = intval(removeMagicQuotes($_GET['deleteshotid']));
			$id_for_db = quoteString($id);
			$sql = "DELETE FROM $sshot_tablename WHERE id=" . $id_for_db;
			mysql_query($sql);
			if (mysql_affected_rows() > 0) {
				// Remove image.
				$path = getcwd() . '/' .$path_to_root . 'images/screenshots/' . $id . '.jpg';
				unlink($path);
				$tnpath = getcwd() . '/' .$path_to_root . 'images/screenshots/' . $id . '_tn.jpg';
				unlink($tnpath);
			}
		}
	}

?>
