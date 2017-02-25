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

	function checkTrackInput()
	{
		$formerrors = intval(0);

		// Check name.
		$formerrors += checkPostString('track_name', MIN_USERNAME_LENGTH, 40);
		// Check internal name.
		$formerrors += checkPostString('track_internalname', MIN_USERNAME_LENGTH, 40);
		// Check author.
		$formerrors += checkPostString('track_author', MIN_USERNAME_LENGTH, 40);
		// Check width.
		$formerrors += checkPostFloat('track_width', 2.0, 1000.0);
		// Check length.
		$formerrors += checkPostFloat('track_length', 50.0, 100000.0);
		// Check nbpits.
		$formerrors += checkPostInt('track_nbpits', 0, 100);
		// Check track type.
		$formerrors += checkPostSet('track_type', array('oval', 'road', 'dirt'));
		// Check file.
		$formerrors += checkPostFile('track_image', 50000, 'image/jpeg');

		return $formerrors;
	}


	function commitTrackInput($track_tablename, $path_to_root)
	{
		$name_for_db = quoteString(removeMagicQuotes($_POST['track_name']));
		$internalname_for_db = quoteString(removeMagicQuotes($_POST['track_internalname']));
		$nbpits_for_db = quoteString(intval(removeMagicQuotes($_POST['track_nbpits'])));
		$width_for_db = quoteString(floatval(removeMagicQuotes($_POST['track_width'])));
		$length_for_db = quoteString(floatval(removeMagicQuotes($_POST['track_length'])));
		$author_for_db = quoteString(removeMagicQuotes($_POST['track_author']));
		$type_for_db = quoteString(removeMagicQuotes($_POST['track_type']));
		$desc_for_db = isset($_POST['track_description']) ? quoteString(removeMagicQuotes($_POST['track_description'])) : "''";

		$file = $_FILES['track_image'];

		// Commit data.
		$sql = "INSERT INTO $track_tablename " .
			   "(name, nbpits, width, length, author, type, description, internalname) VALUES " .
			   "($name_for_db, $nbpits_for_db, $width_for_db, $length_for_db, " .
			   " $author_for_db, $type_for_db, $desc_for_db, $internalname_for_db)";
		mysql_query($sql);

		// Move file (picture).
		if (mysql_affected_rows() > 0) {
			$sql = "SELECT LAST_INSERT_ID() AS lastid";
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				$trackid = $myrow['lastid'];
				commitJPEGImage(
					$trackid, $path_to_root, 'track_image', 40000, 'images/tracks/',
					256, 256, 140, 140, 90
				);
			}
		}
	}


	function updateTrackInput($track_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin' &&
			isset($_POST['track_id']))
		{
			$trackid = intval(removeMagicQuotes($_POST['track_id']));
			$trackid_for_db = quoteString($trackid);
			$name_for_db = quoteString(removeMagicQuotes($_POST['track_name']));
			$internalname_for_db = quoteString(removeMagicQuotes($_POST['track_internalname']));
			$nbpits_for_db = quoteString(intval(removeMagicQuotes($_POST['track_nbpits'])));
			$width_for_db = quoteString(floatval(removeMagicQuotes($_POST['track_width'])));
			$length_for_db = quoteString(floatval(removeMagicQuotes($_POST['track_length'])));
			$author_for_db = quoteString(removeMagicQuotes($_POST['track_author']));
			$type_for_db = quoteString(removeMagicQuotes($_POST['track_type']));
			$desc_for_db = isset($_POST['track_description']) ? quoteString(removeMagicQuotes($_POST['track_description'])) : "''";

			$file = $_FILES['track_image'];

			$sql = "UPDATE $track_tablename SET " .
				   "name=$name_for_db, nbpits=$nbpits_for_db, " .
				   "width=$width_for_db, length=$length_for_db, " .
				   "author=$author_for_db, type=$type_for_db, " .
				   "description=$desc_for_db, internalname=$internalname_for_db " .
				   "WHERE trackid=$trackid_for_db";
			mysql_query($sql);

			// Move file (picture).
			if (mysql_affected_rows() > 0 || mysql_errno() == 0) {
				commitJPEGImage(
					$trackid, $path_to_root, 'track_image', 40000, 'images/tracks/',
					256, 256, 140, 140, 90
				);
			}
		}
	}


	function deleteTrack($track_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin' &&
			isset($_GET['deletetrackid']))
		{
			$id = intval(removeMagicQuotes($_GET['deletetrackid']));
			$id_for_db = quoteString($id);
			$sql = "DELETE FROM $track_tablename WHERE trackid=" . $id_for_db;
			mysql_query($sql);
			if (mysql_affected_rows() > 0) {
				// Remove image.
				$path = getcwd() . '/' .$path_to_root . 'images/tracks/' . $id . '.jpg';
				unlink($path);
				$tnpath = getcwd() . '/' .$path_to_root . 'images/tracks/' . $id . '_tn.jpg';
				unlink($tnpath);
			}
		}
	}

?>
