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



	function checkNewsInput()
	{
		$formerrors = intval(0);

		// Check title.
		$formerrors += checkPostString('news_title', 2, 100);
		// Check text.
		$formerrors += checkPostString('news_text', 2, 10000);
		return $formerrors;
	}


	function commitNewsInput($news_tablename, $path_to_root)
	{
		$title_for_db = quoteString(removeMagicQuotes($_POST['news_title']));
		$text_for_db = quoteString(removeMagicQuotes($_POST['news_text']));
		$uid_for_db = quoteString($_SESSION['uid']);

		// Commit data.
		$sql = "INSERT INTO $news_tablename " .
			   "(title, text, author) VALUES ($title_for_db, $text_for_db, $uid_for_db)";
		mysql_query($sql);
	}


	function deleteNews($news_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin' &&
			isset($_GET['deletenewsid']))
		{
			$id = intval(removeMagicQuotes($_GET['deletenewsid']));
			$id_for_db = quoteString($id);
			$sql = "DELETE FROM $news_tablename WHERE id=" . $id_for_db;
			mysql_query($sql);
		}
	}


	function updateNewsInput($news_tablename, $path_to_root)
	{
		if ($_SESSION['usergroup'] == 'admin' &&
			isset($_POST['news_id']))
		{
			$id_for_db = quoteString(intval(removeMagicQuotes($_POST['news_id'])));
			$title_for_db = quoteString(removeMagicQuotes($_POST['news_title']));
			$text_for_db = quoteString(removeMagicQuotes($_POST['news_text']));
			$uid_for_db = quoteString($_SESSION['uid']);
			$sql = "UPDATE $news_tablename SET title=$title_for_db, text=$text_for_db, " .
				   "author=$uid_for_db WHERE id=$id_for_db";
			mysql_query($sql);
		}

	}
?>
