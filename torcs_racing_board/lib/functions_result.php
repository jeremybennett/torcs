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


	function checkarray($i, &$string, &$error, &$errorarray, &$data, &$checklist)
	{
		foreach ($checklist as $value) {
			if (!isset($data[$value])) {
				$errorarray[$error] = $string . '/' . $i . ': ' . $value . ' missing.';
				$error++;
			}
		}
	}

?>
