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

	function checkPostString($cs, $min, $max)
	{
		$retval = intval(1); // assume error.
		if (isset($_POST[$cs])) {
			$rcs = removeMagicQuotes($_POST[$cs]);
			$len = strlen($rcs);
			if ($len >= $min && $len <= $max) {
				$retval = intval(0);
			}
		}
		return $retval;
	}


	function checkPostFloat($cs, $min, $max)
	{
		$retval = intval(1); // assume error.
		if (isset($_POST[$cs])) {
			$val = floatval(removeMagicQuotes($_POST[$cs]));
			if ($val >= $min && $val <= $max) {
				$retval = intval(0);
			}
		}
		return $retval;
	}


	function checkPostInt($cs, $min, $max)
	{
		$retval = intval(1); // assume error.
		if (isset($_POST[$cs])) {
			$val = intval(removeMagicQuotes($_POST[$cs]));
			if ($val >= $min && $val <= $max) {
				$retval = intval(0);
			}
		}
		return $retval;
	}


	function checkPostOddInt($cs, $min, $max)
	{
		$retval = intval(1); // assume error.
		if (isset($_POST[$cs])) {
			$val = intval(removeMagicQuotes($_POST[$cs]));
			if ($val >= $min && $val <= $max && ($val % 2 == 1)) {
				$retval = intval(0);
			}
		}
		return $retval;
	}


	function checkPostSet($cs, $values)
	{
		$retval = intval(1); // assume error.
		if (isset($_POST[$cs])) {
			$val = removeMagicQuotes($_POST[$cs]);
			foreach ($values as $value) {
				if (strcmp($value, $val) == 0) {
					$retval = intval(0);
				}
			}
		}
		return $retval;
	}


	function checkPostFile($cs, $size, $mimetype)
	{
		$retval = intval(1); // assume error.
		if (isset($_FILES[$cs])) {
			$val = $_FILES[$cs];
			if (strcmp($val['type'], $mimetype) == 0 &&
				$val['size'] <= $size
			) {
				$retval = intval(0);
			}
		}
		return $retval;
	}


	function checkPostDateTime($cs)
	{
		$retval = intval(1); // assume error.
		if (isset($_POST[$cs]) && strlen($_POST[$cs]) > 0) {
			$val = removeMagicQuotes($_POST[$cs]);
			$time = strtotime($val);
			if ($time != FALSE) {
				$retval = intval(0);
			}
		}
		return $retval;
	}

?>
