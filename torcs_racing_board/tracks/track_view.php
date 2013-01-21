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

	session_start();
	$path_to_root = '../';
	require_once($path_to_root . 'secrets/configuration.php');
	require_once($path_to_root . 'lib/functions.php');
	require_once($path_to_root . 'lib/functions_reports.php');
	require_once($path_to_root . 'lib/classes.php');
	require_once($path_to_root . 'lib/template.inc');

	if (!isset($_SESSION['uid']) ) {
		session_defaults();
	}

	$db = mysql_connect($db_host, $db_user, $db_passwd) or die;
	mysql_select_db($db_name, $db) or die;
	$user_tablename = $db_prefix . TBL_USERS;
	$forum_tablename = $db_prefix . TBL_FORUM;
	$topic_tablename = $db_prefix . TBL_FORUM_TOPICDATA;
	$stats_hitcount_tablename = $db_prefix . TBL_HITCOUNT;
	$stats_sessioncount_tablename = $db_prefix . TBL_SESSIONCOUNT;
	$stats_tablename = $db_prefix . TBL_STATS;
	$loginlog_tablename = $db_prefix . TBL_LOGIN_LOG;
	$track_tablename = $db_prefix . TBL_TRACK;
	$version_tablename = $db_prefix . TBL_VERSION;

	$race_report_driver_table = $db_prefix . TBL_RACE_REPORT_DRIVER;
	$driver_tablename = $db_prefix . TBL_DRIVER;
	$event_tablename = $db_prefix . TBL_EVENT;
	$car_tablename = $db_prefix . TBL_CAR;
	$race_tablename = $db_prefix . TBL_RACE;
	$rawresult_tablename = $db_prefix . TBL_RAWRESULT;

	countSession(session_id(), $stats_sessioncount_tablename, $stats_tablename);
	countHit($_SERVER['PHP_SELF'], $stats_hitcount_tablename);

	// The creation checks the login.
	$user = new User($db, $user_tablename, $loginlog_tablename);

	// Login?
	checkLogin($user);
	// Logout?
	checkLogout();

	if ($_SESSION['logged'] == TRUE) {
		// Login template for statusbar.
		$page_statusbar = 'page_statusbar_logged_in.ihtml';
	} else {
		// Status view template for statusbar.
		$page_statusbar = 'page_statusbar.ihtml';
	}

	// Create template instance for page layout.
	$page = new Template($path_to_root . 'templates', 'keep');

	// Define template file(s).
	$page->set_file(array(
		'page'				=> 'page.ihtml',
		'PAGE_BEGIN_T'		=> 'page_begin.ihtml',
		'PAGE_TITLEBAR_T'	=> 'page_titlebar.ihtml',
		'PAGE_STATUSBAR_T'	=> $page_statusbar,
		'PAGE_NAVIGATION_T'	=> 'page_navigation.ihtml',
		'PAGE_CONTENT_T'	=> 'admin_no_access.ihtml',
		'PAGE_FOOTER_T'		=> 'page_footer.ihtml',
		'PAGE_END_T'		=> 'page_end.ihtml'
	));

	// Set up page header.
	$page->set_var(array(
		'PB_PAGETITLE'		=> 'The TORCS Racing Board Track View',
		'PB_DESCRIPTION'	=> 'View track of the TORCS racing board',
		'PB_AUTHOR'			=> 'Bernhard Wymann',
		'PB_KEYWORDS'		=> 'TORCS, racing, berniw, Bernhard, Wymann, Championship, World, Board, Track, View, Show',
		'ROOTPATH'			=> $path_to_root,
	));

	if ($_SESSION['logged'] == TRUE) {
		// Variables if logged in.
		$page->set_var(array(
			'PS_USERNAME'		=> $_SESSION['username'],
			'PS_ACCOUNT_TYPE'	=> $_SESSION['usergroup'],
			'PS_IPADSRESS'		=> $_SERVER['REMOTE_ADDR'],
			'PS_LOGOUTPAGE'		=> $path_to_root . 'index.php'
		));
	} else {
		// Variables if NOT logged in.
		$page->set_var(array(
			'PS_PASSWORD_SIZE'	=> MAX_USERNAME_LENGTH,
			'PS_USERNAME_SIZE'	=> MAX_USERNAME_LENGTH,
			'PS_LOGINPAGE'		=> $_SERVER['PHP_SELF'],
			'PS_HOSTNAME'		=> SERVER_NAME
		));
	}

	if (isset($_GET['viewtrackid'])) {
		$trackid = intval(removeMagicQuotes($_GET['viewtrackid']));
		$trackid_for_db = quoteString($trackid);
		$sql = "SELECT * FROM $track_tablename WHERE trackid=" . $trackid_for_db;
		$result = mysql_query($sql);
		if ($myrow = mysql_fetch_array($result)) {
			$page->set_file('PAGE_CONTENT_T', 'track_view.ihtml');
			$page->set_var(array(
				'PC_TRACK_ID'			=> $myrow['trackid'],
				'PC_TRACK_NAME'			=> htmlentities($myrow['name']),
				'PC_TRACK_NBPITS'		=> $myrow['nbpits'],
				'PC_TRACK_WIDTH'		=> sprintf("%01.2f", $myrow['width']),
				'PC_TRACK_LENGTH'		=> sprintf("%01.2f", $myrow['length']),
				'PC_TRACK_AUTHOR'		=> htmlentities($myrow['author']),
				'PC_TRACK_TYPE'			=> htmlentities($myrow['type']),
				'PC_TRACK_DESCRIPTION'	=> htmlentities($myrow['description']),
				'PC_TRACK_IMG_SRC'		=> $path_to_root . 'images/tracks/' . $trackid . '.jpg'
			));

			// Define the block template for a table row (fastest qualy times).
			$page->set_block("PAGE_CONTENT_T", "timerow", "timerows");
	
			$sql = "SELECT  v.name AS vname, c.name AS cname, p.carid, e.name AS ename, r.raceid, d.name AS dname, d.teamid, p.quali_laptime FROM " .
				" $race_report_driver_table AS p, $driver_tablename AS d, $event_tablename AS e, $car_tablename AS c, " .
				" $race_tablename AS r JOIN (SELECT uu.raceid, MIN(p.quali_laptime) AS quali_laptime FROM " .
				" $race_tablename AS uu JOIN (SELECT driverid, raceid, MIN(quali_laptime) AS qlt FROM " .
				" $rawresult_tablename GROUP BY driverid,raceid) AS x ON (uu.raceid=x.raceid), " .
				" $race_report_driver_table AS p WHERE x.driverid=p.driverid AND x.qlt > 0 AND x.qlt <= p.quali_laptime AND " .
				" uu.trackid = $trackid AND uu.raceid=p.raceid AND p.quali_laptime > 0 GROUP BY uu.raceid) as vv ON (vv.raceid=r.raceid) " .
				" LEFT JOIN $version_tablename AS v ON r.versionid = v.id WHERE " .
				" p.quali_laptime=vv.quali_laptime AND p.driverid=d.driverid AND " .
				" r.eventid=e.eventid AND c.carid=p.carid AND r.trackid=$trackid ORDER BY e.eventid DESC";
			$result = mysql_query($sql);

			$results = 0;
			while ($myrow = mysql_fetch_array($result)) {
				$page->set_var(array(
					'PC_EVENT'		=> htmlentities($myrow['ename']),
					'PC_RACE_ID'	=> $myrow['raceid'],
					'PC_TIME'		=> secondsToLaptime($myrow['quali_laptime']),
					'PC_TEAM_ID'	=> $myrow['teamid'],
					'PC_DRIVER'		=> htmlentities($myrow['dname']),
					'PC_CAR'		=> htmlentities($myrow['cname']),
					'PC_CAR_ID'		=> $myrow['carid'],
					'PC_VERSION'	=> is_null($myrow['vname']) ? '-' : htmlentities($myrow['vname']) 
				));
				$page->parse("timerows", "timerow", true);
				$results++;
			}

			if ($results == 0) {
				$page->set_var("timerows", "");
			}
		}
	}

	require_once($path_to_root . 'lib/functions_navigation.php');
	setupNavigationAndFooter($page, $stats_tablename, $stats_hitcount_tablename);

	$page->parse('PAGE_BEGIN', 'PAGE_BEGIN_T');
	$page->parse('PAGE_TITLEBAR', 'PAGE_TITLEBAR_T');
	$page->parse('PAGE_STATUSBAR', 'PAGE_STATUSBAR_T');
	$page->parse('PAGE_NAVIGATION', 'PAGE_NAVIGATION_T');
	$page->parse('PAGE_CONTENT', 'PAGE_CONTENT_T');
	$page->parse('PAGE_FOOTER', 'PAGE_FOOTER_T');
	$page->parse('PAGE_END', 'PAGE_END_T');

	$page->parse('OUTPUT', array(
		'PAGE_BEGIN',
		'PAGE_TITLEBAR',
		'PAGE_NAVIGATION',
		'PAGE_STATUSBAR',
		'PAGE_CONTENT',
		'PAGE_FOOTER',
		'PAGE_END',
		'page'
	));

	$page->p('OUTPUT');
?>
