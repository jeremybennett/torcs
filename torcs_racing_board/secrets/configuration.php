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

	$db_host = 'localhost';		// <-- CHANGE!
	$db_name = 'mydb';			// <-- CHANGE!
	$db_user = 'mydb';			// <-- CHANGE!
	$db_passwd = 'mydb';		// <-- CHANGE!
	$db_prefix = 'test_';		// <-- CHANGE!

	// Version
	define('TRB_VERSION', '0.0.0');

	// Table with user data.
	define('TBL_USERS', 'users');

	// Table with accounts that need e-mail confirmation to become activated.
	define('TBL_CONFIRM', 'confirm');

	// Table with forum entries.
	define('TBL_FORUM', 'forum');
	define('TBL_FORUM_TOPICDATA', 'topicdata');
	define('TBL_FORUM_POLL', 'forum_poll');
	define('MAX_FORUM_RECURSION', 30);
	define('LISTENTRIES', 25);
	define('IMAGELISTENTRIES', 6);
	define('NEWSENTRIES', 5);
	define('SSHOTLISTROWS', 3);
	define('OVRIMGENTRIES', 8);

	// Tables for statisics.
	define('TBL_HITCOUNT', 'hitcount');
	define('TBL_SESSIONCOUNT', 'sessioncount');
	define('TBL_STATS', 'statistics');
	define('SESSION_STATS_EXPIRE', 21600); // 6 hours.

	// Tables for logging.
	define('TBL_LOGIN_LOG', 'loginlog');
	define('LOGIN_LOG_EXPIRE', 7776000); // 3 Months.
	define('LOGIN_LOG_NEWENTRY', 60); // Collect login entries from the same address when the last attemt was less than 60s ago.

	// Table for lost password activation.
	define('TBL_LOSTPASSWORD', 'lostpassword');
	define('PASSWORD_REQUEST_EXPIRE', 86400); // 24 hours.

	// Tables for quizzes and polls.
	define('TBL_QUIZZ', 'quizz');
	define('TBL_ANSWERS', 'quizz_answers');
	define('TBL_QUESTIONS', 'quizz_questions');
	define('TBL_QUIZZQUESTIONS', 'quizz_quizzquestions');
	define('TBL_POLL', 'poll');
	define('TBL_POLLANSWERS', 'poll_answers');
	define('TBL_POLLVOTERS', 'poll_voters');

	// Tables for tracks, cars, races and teams.
	define('TBL_TRACK', 'track');
	define('TBL_CAR', 'car');
	define('TBL_TEAM', 'team');
	define('TBL_DRIVER', 'driver');
	define('TBL_RACE', 'race');
	define('TBL_EVENT', 'event');						// Event: A championship, a container for a race, ...
	define('TBL_EVENT_CAR', 'event_car');
	define('TBL_EVENTTEAM', 'event_team');				// Registrations of teams for events.
	define('TBL_RAWRESULT', 'rawresult');				// Unprocessed submitted results.
	define('TBL_RESULTSUBMITTED', 'resultsubmitted');	// Keep track of submissions.
	define('TBL_RACE_REPORT_DRIVER', 'race_report_driver');
	define('TBL_RACE_REPORT_TEAM', 'race_report_team');
	define('TBL_EVENT_REPORT_DRIVER', 'event_report_driver');
	define('TBL_EVENT_REPORT_TEAM', 'event_report_team');

	define('TBL_SCREENSHOT', 'screenshot');
	define('TBL_NEWS', 'news');

	// System settings/limits
	define('TEAMS_PER_USER', 5);
	define('TEAMS_PER_EVENT', 40);
	define('ROBOT_MODULE_SIZE', 500000);
	define('ROBOT_RESULT_SIZE', 80000);

	// Cookie settings.
	define('COOKIE_NAME', 'berniw');
	define('COOKIE_DIR', '/trb/');							// <-- CHANGE!
	define('COOKIE_DOMAIN', 'www.??????.???');				// <-- CHANGE!
	define('COOKIE_EXPIRE', 31536000);	// [s] -> 360 days

	// Limits for input fields and data.
	define('MIN_PASSWORD_LENGTH', 6);
	define('MIN_USERNAME_LENGTH', 3);
	define('MAX_USERNAME_LENGTH', 20);
	define('MAX_EMAIL_LENGTH', 40);

	// Server stuff.
	define('REGISTER_EMAIL', '?????@?????.???');			// <-- CHANGE
	define('ADMIN_EMAIL', '????????@??????.???');			// <-- CHANGE
	define('SERVER_NAME', 'www.?????.????');				// <-- CHANGE

	// Account activation.
	define('ACTIVATION_EXPIRE', 86400); // 24 hours.

	// Colors
	define('COLOR_TB1', '#e8e8e8');
	define('COLOR_TB2', '#f0f0f0');
	define('COLOR_TB3', '#f8f8f8');
	define('COLOR_TB_ERR', '#ff8888');

	// Poll default duration.
	define('POLL_DURATION', 31536000);

?>
