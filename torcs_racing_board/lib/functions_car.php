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


	function checkCarInput()
	{
		$formerrors = intval(0);

		// Check name.
		$formerrors += checkPostString('car_name', MIN_USERNAME_LENGTH, 40);
		// Check author.
		$formerrors += checkPostString('car_author', MIN_USERNAME_LENGTH, 40);
		// Check width.
		$formerrors += checkPostFloat('car_width', 1.0, 3.0);
		// Check length.
		$formerrors += checkPostFloat('car_length', 1.0, 30.0);
		// Check maxfuel.
		$formerrors += checkPostFloat('car_maxfuel', 1.0, 300.0);
		// Check mass.
		$formerrors += checkPostFloat('car_mass', 300.0, 30000.0);
		// Check cxa.
		$formerrors += checkPostFloat('car_cxa', 0.1, 10.0);
		// Check power.
		$formerrors += checkPostFloat('car_power', 10.0, 10000.0);
		// Check train.
		$formerrors += checkPostSet('car_type', array('rwd', 'fwd', '4wd'));
		// Check file.
		$formerrors += checkPostFile('car_image', 40000, 'image/jpeg');

		return $formerrors;
	}


	function commitCarInput($car_tablename, $path_to_root)
	{
		$name_for_db = quoteString(removeMagicQuotes($_POST['car_name']));
		$author_for_db = quoteString(removeMagicQuotes($_POST['car_author']));
		$width_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_width'])));
		$length_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_length'])));
		$maxfuel_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_maxfuel'])));
		$mass_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_mass'])));
		$cxa_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_cxa'])));
		$power_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_power'])));
		$type_for_db = quoteString(removeMagicQuotes($_POST['car_type']));
		$desc_for_db = isset($_POST['car_description']) ? quoteString(removeMagicQuotes($_POST['car_description'])) : "''";

		$file = $_FILES['car_image'];

		// Commit data.
		$sql = "INSERT INTO $car_tablename " .
			   "(name, author, mass, tank, cxa, power, width, length, train, description) VALUES " .
			   "($name_for_db, $author_for_db, $mass_for_db, $maxfuel_for_db, $cxa_for_db, " .
			   "$power_for_db, $width_for_db, $length_for_db, $type_for_db, $desc_for_db)";
		mysql_query($sql);

		// Move file (picture).
		if (mysql_affected_rows() > 0) {
			$sql = "SELECT LAST_INSERT_ID() AS lastid";
			$result = mysql_query($sql);
			if ($myrow = mysql_fetch_array($result)) {
				$carid = $myrow['lastid'];
				commitJPEGImage(
					$carid, $path_to_root, 'car_image', 40000, 'images/cars/',
					300, 379, 140, 177, 90
				);
			}
		}
	}


	function updateCarInput($car_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin' &&
			isset($_POST['car_id']))
		{
			$carid = intval(removeMagicQuotes($_POST['car_id']));
			$carid_for_db = quoteString($carid);
			$name_for_db = quoteString(removeMagicQuotes($_POST['car_name']));
			$author_for_db = quoteString(removeMagicQuotes($_POST['car_author']));
			$width_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_width'])));
			$length_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_length'])));
			$maxfuel_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_maxfuel'])));
			$mass_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_mass'])));
			$cxa_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_cxa'])));
			$power_for_db = quoteString(floatval(removeMagicQuotes($_POST['car_power'])));
			$type_for_db = quoteString(removeMagicQuotes($_POST['car_type']));
			$desc_for_db = isset($_POST['car_description']) ? quoteString(removeMagicQuotes($_POST['car_description'])) : "''";

			$file = $_FILES['car_image'];

			$sql = "UPDATE $car_tablename SET " .
				   "name=$name_for_db, author=$author_for_db, width=$width_for_db, length=$length_for_db, " .
				   "tank=$maxfuel_for_db, mass=$mass_for_db, cxa=$cxa_for_db, power=$power_for_db, " .
				   "train=$type_for_db, description=$desc_for_db " .
				   "WHERE carid=$carid_for_db";
			mysql_query($sql);

			// Move file (picture).
			if (mysql_affected_rows() > 0 || mysql_errno() == 0) {
				commitJPEGImage(
					$carid, $path_to_root, 'car_image', 40000, 'images/cars/',
					300, 379, 140, 177, 90
				);
				/*$path = getcwd() . '/' .$path_to_root . 'images/cars/' . $carid . '.jpg';
				if (is_uploaded_file($file['tmp_name'])) {
					move_uploaded_file($file['tmp_name'], $path);
				}*/
			}
		}
	}


	function deleteCar($car_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin' &&
			isset($_GET['deletecarid']))
		{
			$id = intval(removeMagicQuotes($_GET['deletecarid']));
			$id_for_db = quoteString($id);
			$sql = "DELETE FROM $car_tablename WHERE carid=" . $id_for_db;
			mysql_query($sql);
			if (mysql_affected_rows() > 0) {
				// Remove image.
				$path = getcwd() . '/' .$path_to_root . 'images/cars/' . $id . '.jpg';
				$tnpath = getcwd() . '/' .$path_to_root . 'images/cars/' . $id . '_tn.jpg';
				if (file_exists($path)) {
					unlink($path);
				}
				if (file_exists($tnpath)) {
					unlink($tnpath);
				}
			}
		}
	}

?>
