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

	function setupNavigationAndFooter(&$page, &$stats_tablename, &$stats_hitcount_tablename)
	{
		$page->set_block("PAGE_NAVIGATION_T", "anonymous_nav", "anonymous_nav_var");
		$page->set_block("PAGE_NAVIGATION_T", "spectator_nav", "spectator_nav_var");
		$page->set_block("PAGE_NAVIGATION_T", "racer_nav", "racer_nav_var");
		$page->set_block("PAGE_NAVIGATION_T", "admin_nav", "admin_nav_var");

		if ($_SESSION['usergroup'] == 'anonymous') {
			$page->parse("anonymous_nav_var", "anonymous_nav");
		} else {
			$page->set_var("anonymous_nav_var", "");
		}
		if ($_SESSION['usergroup'] == 'spectator') {
			$page->parse("spectator_nav_var", "spectator_nav");
		} else {
			$page->set_var("spectator_nav_var", "");
		}
		if ($_SESSION['usergroup'] == 'racer') {
			$page->parse("racer_nav_var", "racer_nav");
		} else {
			$page->set_var("racer_nav_var", "");
		}
		if ($_SESSION['usergroup'] == 'admin') {
			$page->parse("admin_nav_var", "admin_nav");
		} else {
			$page->set_var("admin_nav_var", "");
		}

		// Footer.
		// Get page hits.
		$hits = 0;
		$page_for_db = quoteString($_SERVER['PHP_SELF']);
		$sql = "SELECT * FROM $stats_hitcount_tablename WHERE page=$page_for_db";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
			$hits = $myrow['hits'];
		}

		$visits = 0;
		$sql = "SELECT * FROM $stats_tablename WHERE name='visits'";
		$result = mysql_query($sql);
		if (mysql_num_rows($result) == 1 && $myrow = mysql_fetch_array($result)) {
			$visits = $myrow['value'];
		}

		$page->set_var(array(
			'PF_HITS'			=> $hits,
			'PF_VISITS'			=> $visits,
			'PF_SERVERTIME'		=> date("r"),
			'TRB_VERSION'		=> TRB_VERSION
		));
	}


?>
