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

	require_once('secrets/configuration.php');
	require_once('lib/functions.php');

	// Try to connect to db, if failed terminate silently.
	// All values come from configuration.php and should be safe therefore.
	$db = mysql_connect($db_host, $db_user, $db_passwd) or die;
	mysql_select_db($db_name, $db) or die;

	// Create user table.
	$tablename = $db_prefix . TBL_USERS;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_USERS table.
		$sql =  "CREATE TABLE $tablename (" .
			"id INT NOT NULL AUTO_INCREMENT, " .
			"username VARCHAR(20) NOT NULL DEFAULT '', " .
			"password CHAR(32) BINARY NOT NULL DEFAULT '', " .
			"cookie CHAR(32) BINARY NOT NULL DEFAULT '', " .
			"session CHAR(32) BINARY NOT NULL DEFAULT '', " .
			"ip VARCHAR(15) BINARY NOT NULL DEFAULT '', " .
			"email VARCHAR(40) NOT NULL DEFAULT '', " .
			"firstname VARCHAR(20) NOT NULL DEFAULT '', " .
			"lastname VARCHAR(20) NOT NULL DEFAULT '', " .
			"active ENUM('activated','pending','disabled') NOT NULL DEFAULT 'pending', " .  // for email activation
			"registered DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " . // for email activation
			"lastlogin DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " . // login, not yet used
			"lastvisit DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " . // session, not yet used
			"account ENUM('spectator','racer','admin') NOT NULL DEFAULT 'spectator', " .
			"postings INT NOT NULL DEFAULT '0', " .
			"PRIMARY KEY (id), " .
			"UNIQUE KEY username (username), " .
			"UNIQUE KEY email (email))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}


	// Create account confirmation/activation table.
	$tablename = $db_prefix . TBL_CONFIRM;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_CONFIRM table.
		$sql = "CREATE TABLE $tablename (" .
			"id INT NOT NULL, " .
			"activationkey CHAR(32) BINARY NOT NULL, " .
			"UNIQUE KEY id (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}


	// Create forum table.
	$tablename = $db_prefix . TBL_FORUM;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_FORUM table.
		$sql =  "CREATE TABLE $tablename (" .
			"id INT NOT NULL AUTO_INCREMENT, " .
			"id_parent INT DEFAULT 0, " .
			"id_thread INT DEFAULT 0, " .
			"id_article INT DEFAULT 0, " .
			"author INT NOT NULL, " .
			"last_editor INT NOT NULL, " .
			"created DATETIME NOT NULL, " .
			"last_edited DATETIME NOT NULL, " .
			"subject VARCHAR(255) NOT NULL, " .
			"text TEXT NOT NULL, " .
			"state ENUM('visible','hidden') NOT NULL DEFAULT 'visible', " .
			"PRIMARY KEY (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// Create forum table with data related to "topics".
	$tablename = $db_prefix . TBL_FORUM_TOPICDATA;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_FORUM_TOPICDATA table.
		$sql =  "CREATE TABLE $tablename (" .
			"id INT NOT NULL, " .
			"replies INT DEFAULT 0, " .
			"lastpost TIMESTAMP, " .
			"PRIMARY KEY (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// Create table for page hit counts.
	$tablename = $db_prefix . TBL_HITCOUNT;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_HITCOUNT table.
		$sql =  "CREATE TABLE $tablename (" .
			"page VARCHAR(255) NOT NULL, " .
			"hits INT DEFAULT 0, " .
			"PRIMARY KEY (page))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// Create table for counting visits.
	$tablename = $db_prefix . TBL_SESSIONCOUNT;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_SESSIONCOUNT table.
		$sql =  "CREATE TABLE $tablename (" .
			"session CHAR(32) BINARY NOT NULL, " .
			"start TIMESTAMP, " .
			"PRIMARY KEY (session))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// Create statistics summary table.
	$tablename = $db_prefix . TBL_STATS;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_STATS table.
		$sql =  "CREATE TABLE $tablename (" .
			"name VARCHAR(255) NOT NULL, " .
			"value VARCHAR(255) NOT NULL, " .
			"PRIMARY KEY (name))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	$sql = "INSERT INTO " . $tablename . " (name, value) VALUES ('visits', '0')";
	mysql_query($sql);

	// Create login log table
	$tablename = $db_prefix . TBL_LOGIN_LOG;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_LOGIN_LOG table.
		$sql =  "CREATE TABLE $tablename (" .
			"id INT NOT NULL DEFAULT '0', " .
			"ip VARCHAR(15) BINARY NOT NULL DEFAULT '', " .
			"time TIMESTAMP, " .
			"username VARCHAR(20), " .
			"count INT NOT NULL DEFAULT '1', " .
			"pf ENUM('passed','failed') NOT NULL)";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// Create lost password activation table.
	$tablename = $db_prefix . TBL_LOSTPASSWORD;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_LOSTPASSWORD table.
		$sql = "CREATE TABLE $tablename (" .
			"id INT NOT NULL, " .
			"activationkey CHAR(32) BINARY NOT NULL, " .
			"requestdate TIMESTAMP, " .
			"UNIQUE KEY id (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// -------------------------- QUIZZ ------------------------------------------

	// Create quizz tables.
	$tablename = $db_prefix . TBL_QUIZZ;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_QUIZZ table.
		$sql = "CREATE TABLE $tablename (" .
			"quizzid INT NOT NULL AUTO_INCREMENT, " .
			"description TEXT NOT NULL, " .
			"allowederrors INT NOT NULL, " .	// number of allowed errors to pass.
			"nbquestions INT NOT NULL, " .		// select n random questions if != 0
			"PRIMARY KEY (quizzid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// Create quizz question table.
	$tablename = $db_prefix . TBL_QUESTIONS;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_QUESTIONS table.
		$sql = "CREATE TABLE $tablename (" .
			"questionid INT NOT NULL, " .
			"question VARCHAR(255) NOT NULL, " .
			"PRIMARY KEY (questionid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// Create quizz answers table.
	$tablename = $db_prefix . TBL_ANSWERS;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_ANSWERS table.
		$sql = "CREATE TABLE $tablename (" .
			"answerid INT NOT NULL AUTO_INCREMENT, " .
			"questionid INT NOT NULL, " .
			"answer VARCHAR(255) NOT NULL, " .
			"true TINYINT NOT NULL, " .
			"PRIMARY KEY (answerid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// Define the concrete quizz, associate a quizz with questions.
	$tablename = $db_prefix . TBL_QUIZZQUESTIONS;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_QUIZZQUESTIONS table.
		$sql = "CREATE TABLE $tablename (" .
			"quizzid INT NOT NULL, " .
			"questionid INT NOT NULL)";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}


	// -------------------------- POLL ------------------------------------------

	// Create poll tables.
	// Describe the poll and its properties itself (duration, who is allowed to vote, ...).
	$tablename = $db_prefix . TBL_POLL;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_POLL table.
		$sql = "CREATE TABLE $tablename (" .
			"pollid INT NOT NULL AUTO_INCREMENT, " .
			"question TEXT NOT NULL, " .
			"start DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .	// voting enabled at this time
			"end DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .	// voting disabled at this time
			"groups SET('spectator','racer','admin','anonymous') NOT NULL, " .
			"owner INT NOT NULL, " .
			"PRIMARY KEY (pollid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// Create poll answer table.
	// The possible answers of the polls and the answer count.
	$tablename = $db_prefix . TBL_POLLANSWERS;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_POLLANSWERS table.
		$sql = "CREATE TABLE $tablename (" .
			"pollanswerid INT NOT NULL AUTO_INCREMENT, " .
			"pollid INT NOT NULL, " .
			"answer VARCHAR(255) NOT NULL, " .
			"count INT NOT NULL DEFAULT '0', " .
			"PRIMARY KEY (pollanswerid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// Create voters table.
	// Who has already voted and for what?
	$tablename = $db_prefix . TBL_POLLVOTERS;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_POLLVOTERS table.
		$sql = "CREATE TABLE $tablename (" .
			"pollid INT NOT NULL, " .
			"pollanswerid INT NOT NULL, " .
			"userid INT NOT NULL)";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}


	// Create poll-message connection table.
	$tablename = $db_prefix . TBL_FORUM_POLL;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_FORUM_POLL table.
		$sql = "CREATE TABLE $tablename (" .
			"threadid INT NOT NULL, " .
			"pollid INT NOT NULL, " .
			"PRIMARY KEY (threadid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}


	// -------------------------------- TRACKS -------------------------------------
	// Create tracks table.
	$tablename = $db_prefix . TBL_TRACK;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_TRACK table.
		$sql = "CREATE TABLE $tablename (" .
			"trackid INT NOT NULL AUTO_INCREMENT, " .
			"name VARCHAR(40) NOT NULL, " .
			"nbpits INT NOT NULL, " .
			"width FLOAT NOT NULL, " .
			"length FLOAT NOT NULL, " .
			"author VARCHAR(40) NOT NULL, " .
			"type ENUM('road', 'dirt', 'oval') NOT NULL, " .
			"description TEXT NOT NULL, " .
			"UNIQUE KEY (name) , " .
			"PRIMARY KEY (trackid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// -------------------------------- CARS -------------------------------------
	// Create cars table.
	$tablename = $db_prefix . TBL_CAR;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_CAR table.
		$sql = "CREATE TABLE $tablename (" .
			"carid INT NOT NULL AUTO_INCREMENT, " .
			"name VARCHAR(40) NOT NULL, " .
			"author VARCHAR(40) NOT NULL, " .
			"mass FLOAT NOT NULL, " .
			"tank FLOAT NOT NULL, " .
			"cxa FLOAT NOT NULL, " .
			"power FLOAT NOT NULL, " .
			"width FLOAT NOT NULL, " .
			"length FLOAT NOT NULL, " .
			"train ENUM('rwd', 'fwd', '4wd') NOT NULL, " .
			"description TEXT NOT NULL, " .
			"UNIQUE KEY (name) , " .
			"PRIMARY KEY (carid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// -------------------------------- TEAMS -------------------------------------
	// Create team table.
	$tablename = $db_prefix . TBL_TEAM;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_TEAM table.
		$sql = "CREATE TABLE $tablename (" .
			"teamid INT NOT NULL AUTO_INCREMENT, " .
			"name VARCHAR(40) NOT NULL, " .
			"description TEXT NOT NULL, " .
			"modulename VARCHAR(40) NOT NULL, " .
			"carid INT NOT NULL, " .
			"created DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .
			"owner INT NOT NULL, " .
			"races INT NOT NULL DEFAULT '0', " .
			"distance FLOAT NOT NULL DEFAULT '0.0', " .
			"points FLOAT NOT NULL DEFAULT '0', " .
			"UNIQUE KEY (name) , " .
			"UNIQUE KEY (modulename) , " .
			"PRIMARY KEY (teamid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// -------------------------------- DRIVERS -------------------------------------
	// Create driver table.
	$tablename = $db_prefix . TBL_DRIVER;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_DRIVER table.
		$sql = "CREATE TABLE $tablename (" .
			"driverid INT NOT NULL AUTO_INCREMENT, " .
			"teamid INT NOT NULL, " .
			"racenumber INT NOT NULL, " .
			"name VARCHAR(40) NOT NULL, " .
			"distance FLOAT NOT NULL DEFAULT '0.0', " .
			"points FLOAT NOT NULL DEFAULT '0', " .
			"races INT NOT NULL DEFAULT '0', " .
			"created DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .
			"UNIQUE KEY (name) , " .
			"UNIQUE KEY (racenumber) , " .
			"PRIMARY KEY (driverid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// ------------------------------- TEAM-EVENT -----------------------------------
	// Which teams subscribed which event?
	$tablename = $db_prefix . TBL_EVENTTEAM;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_EVENTTEAM table.
		$sql = "CREATE TABLE $tablename (" .
			"teamid INT NOT NULL, " .
			"eventid INT NOT NULL, " .
			"UNIQUE KEY (teamid, eventid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// ------------------------------- EVENT-CAR -----------------------------------
	// Which cars are allowed for which event?
	$tablename = $db_prefix . TBL_EVENT_CAR;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_EVENT_CAR table.
		$sql = "CREATE TABLE $tablename (" .
			"carid INT NOT NULL, " .
			"eventid INT NOT NULL, " .
			"UNIQUE KEY (carid, eventid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// ------------------------------- EVENT -----------------------------------
	$tablename = $db_prefix . TBL_EVENT;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_EVENT table.
		$sql = "CREATE TABLE $tablename (" .
			"eventid INT NOT NULL AUTO_INCREMENT, " .
			"name VARCHAR(60) NOT NULL, " .
			"description TEXT NOT NULL, " .
			"signin_start DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .
			"signin_end DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .
			"startdate  DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .
			"enddate  DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .
			"maxteams INT NOT NULL DEFAULT '0', " .
			"pointsystem INT NOT NULL, " .
			"PRIMARY KEY (eventid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// ---------------------------- RACE ---------------------------------------
	$tablename = $db_prefix . TBL_RACE;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_RACE table.
		$sql = "CREATE TABLE $tablename (" .
			"raceid INT NOT NULL AUTO_INCREMENT, " .
			"eventid INT NOT NULL, " .
			"trackid INT NOT NULL, " .
			"robot_submission_start DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .
			"robot_submission_end DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .
			"result_submission_start DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .
			"result_submission_end DATETIME NOT NULL DEFAULT '0000-00-00 00:00:00', " .
			"report_updated ENUM('yes','no') NOT NULL DEFAULT 'no', " .
			"PRIMARY KEY (raceid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// -------------------------- RESULTSUBMITTED --------------------------------
	$tablename = $db_prefix . TBL_RESULTSUBMITTED;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create TBL_RESULTSUBMITTED table.
		$sql = "CREATE TABLE $tablename (" .
			   "raceid INT NOT NULL, " .
			   "submitterid INT NOT NULL, " .
			   "runrace ENUM('ok','failed') NOT NULL, " .
			   "PRIMARY KEY (raceid, submitterid))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// -------------------------- RAWRESULT ----------------------------------------
	$tablename = $db_prefix . TBL_RAWRESULT;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create RAWRESULT table.
		$sql = "CREATE TABLE $tablename (" .
			   "id INT NOT NULL AUTO_INCREMENT, " .
			   "raceid INT NOT NULL, " .
			   "teamid INT NOT NULL, " .
			   "submitterid INT NOT NULL, " .
			   "driverid INT NOT NULL, " .
			   "carid INT NOT NULL, " .
			   "quali_laptime FLOAT NOT NULL, " .
			   "quali_rank INT NOT NULL, " .
			   "race_laptime FLOAT NOT NULL, " .
			   "race_rank INT NOT NULL, " .
			   "race_laps INT NOT NULL, " .
			   "race_topspeed FLOAT NOT NULL, " .
			   "race_damage INT NOT NULL, " .
			   "race_pitstops INT NOT NULL, " .
			   "race_time FLOAT NOT NULL, " .
			   "UNIQUE KEY(submitterid, raceid, driverid), " .
			   "PRIMARY KEY (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// The reports are "cache" and do undermine the referential integrity. TODO: Explore the possibility
	// of a page cache instead of caching into the db.

	// -------------------- TBL_RACE_REPORT_DRIVER ----------------------------------
	$tablename = $db_prefix . TBL_RACE_REPORT_DRIVER;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create RAWRESULT table.
		$sql = "CREATE TABLE $tablename (" .
			   "id INT NOT NULL AUTO_INCREMENT, " .
			   "raceid INT NOT NULL, " .
			   "driverid INT NOT NULL, " .
			   "carid INT NOT NULL, " .
			   "quali_laptime FLOAT NOT NULL, " .
			   "quali_rank FLOAT NOT NULL, " .
			   "race_laptime FLOAT NOT NULL, " .
			   "race_rank FLOAT NOT NULL, " .
			   "points FLOAT NOT NULL, " .
			   "race_laps FLOAT NOT NULL, " .
			   "race_topspeed FLOAT NOT NULL, " .
			   "race_damage FLOAT NOT NULL, " .
			   "race_pitstops FLOAT NOT NULL, " .
			   "race_time FLOAT NOT NULL, " .
			   "UNIQUE KEY(raceid, driverid), " .
			   "PRIMARY KEY (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// ----------------------------- TBL_RACE_REPORT_TEAM ----------------------------
	$tablename = $db_prefix . TBL_RACE_REPORT_TEAM;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create RAWRESULT table.
		$sql = "CREATE TABLE $tablename (" .
			   "id INT NOT NULL AUTO_INCREMENT, " .
			   "raceid INT NOT NULL, " .
			   "teamid INT NOT NULL, " .
			   "points FLOAT NOT NULL, " .
			   "UNIQUE KEY(raceid, teamid), " .
			   "PRIMARY KEY (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// --------------------------- TBL_EVENT_REPORT_DRIVER ------------------------------
	$tablename = $db_prefix . TBL_EVENT_REPORT_DRIVER;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create RAWRESULT table.
		$sql = "CREATE TABLE $tablename (" .
			   "id INT NOT NULL AUTO_INCREMENT, " .
			   "eventid INT NOT NULL, " .
			   "driverid INT NOT NULL, " .
			   "points FLOAT NOT NULL, " .
			   "UNIQUE KEY(eventid, driverid), " .
			   "PRIMARY KEY (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}

	// ----------------------------- TBL_EVENT_REPORT_TEAM --------------------------------
	$tablename = $db_prefix . TBL_EVENT_REPORT_TEAM;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create RAWRESULT table.
		$sql = "CREATE TABLE $tablename (" .
			   "id INT NOT NULL AUTO_INCREMENT, " .
			   "eventid INT NOT NULL, " .
			   "teamid INT NOT NULL, " .
			   "points FLOAT NOT NULL, " .
			   "UNIQUE KEY(eventid, teamid), " .
			   "PRIMARY KEY (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}


	// ----------------------------- TBL_SCREENSHOT --------------------------------
	$tablename = $db_prefix . TBL_SCREENSHOT;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create RAWRESULT table.
		$sql = "CREATE TABLE $tablename (" .
			   "id INT NOT NULL AUTO_INCREMENT, " .
			   "description VARCHAR(100) NOT NULL DEFAULT '', " .
			   "time TIMESTAMP, " .
			   "PRIMARY KEY (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}


	// ----------------------------- TBL_NEWS --------------------------------
	$tablename = $db_prefix . TBL_NEWS;
	if (existsTable($tablename)) {
		echo "Table $tablename already exists, doing nothing.<br>\n";
	} else {
		// Create RAWRESULT table.
		$sql = "CREATE TABLE $tablename (" .
			   "id INT NOT NULL AUTO_INCREMENT, " .
			   "title VARCHAR(100) NOT NULL DEFAULT '', " .
			   "text TEXT NOT NULL, " .
			   "author INT NOT NULL, " .
			   "time TIMESTAMP, " .
			   "PRIMARY KEY (id))";
		$result = mysql_query($sql);
		echo "Created Table $tablename: " . mysql_error() . "<br>\n";
	}


	// ----------------------------- INDICES --------------------------------
	$tablename = $db_prefix . TBL_LOGIN_LOG;
	$sql = "ALTER TABLE $tablename ADD INDEX `login` ( `id` , `ip` , `pf` , `username` , `time` )";
	$result = mysql_query($sql);
	$sql = "ALTER TABLE $tablename ADD INDEX ( `time` )";
	$result = mysql_query($sql);

	$tablename = $db_prefix . TBL_USERS;
	$sql = "ALTER TABLE $tablename ADD INDEX `user` ( `username` , `password` , `active` )";
	$result = mysql_query($sql);
	$sql = "ALTER TABLE $tablename ADD INDEX ( `username` , `cookie` , `active` )";
	$result = mysql_query($sql);
	$sql = "ALTER TABLE $tablename ADD INDEX ( `username` , `cookie` , `session` , `ip` , `active` )";
	$result = mysql_query($sql);

	$tablename = $db_prefix . TBL_FORUM;
	$sql = "ALTER TABLE $tablename ADD INDEX ( `id` , `id_thread` )";
	$result = mysql_query($sql);
	$sql = "ALTER TABLE $tablename ADD INDEX ( `id_parent` )";
	$result = mysql_query($sql);
	$sql = "ALTER TABLE $tablename ADD INDEX ( `id_parent` , `id_thread` )";
	$result = mysql_query($sql);
	$sql = "ALTER TABLE $tablename ADD INDEX ( `created` )";
	$result = mysql_query($sql);
	$sql = "ALTER TABLE $tablename ADD INDEX ( `author` )";
	$result = mysql_query($sql);
	$sql = "ALTER TABLE $tablename ADD FULLTEXT `subjecttext` (`subject`,`text`)";
	$result = mysql_query($sql);
	$sql = "ALTER TABLE $tablename ADD FULLTEXT `subject` (`subject`)";
	$result = mysql_query($sql);

	$tablename = $db_prefix . TBL_FORUM_TOPICDATA;
	$sql = "ALTER TABLE $tablename ADD INDEX ( `lastpost` )";
	$result = mysql_query($sql);

	$tablename = $db_prefix . TBL_SESSIONCOUNT;
	$sql = "ALTER TABLE $tablename ADD INDEX ( `start` )";
	$result = mysql_query($sql);

	$tablename = $db_prefix . TBL_SESSIONCOUNT;
	$sql = "ALTER TABLE $tablename CHANGE `session` `session` VARCHAR( 255 ) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL DEFAULT ''";
	$result = mysql_query($sql);

	$tablename = $db_prefix . TBL_USERS;
	$sql = "ALTER TABLE $tablename CHANGE `session` `session` VARCHAR( 255 ) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL DEFAULT ''";
	$result = mysql_query($sql);

?>
