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

	define('TXML_PARM_RESULTS',				'Results');

	define('TXML_SECT_DRIVERS',				'Drivers');
	define('TXML_SECT_RESULTS',				'Results');
	define('TXML_SECT_RANK',				'Rank');
	define('TXML_SECT_QUALIFICATION',		'Qualifications');
	define('TXML_SECT_RACE1',				'Race');

	define('TXML_ATTS_MODULENAME',			'dll name');
	define('TXML_ATTS_MODULE',				'module');
	define('TXML_ATTS_CAR',					'car');
	define('TXML_ATTS_NAME',				'name');

	define('TXML_ATTN_MODULE_INDEX',		'idx');
	define('TXML_ATTN_START_MODULE_INDEX',	'index');
	define('TXML_ATTN_LAPS',				'laps');
	define('TXML_ATTN_TIME',				'time');
	define('TXML_ATTN_BEST_LAP_TIME',		'best lap time');
	define('TXML_ATTN_TOPSPEED',			'top speed');
	define('TXML_ATTN_DAMAGE',				'dammages');
	define('TXML_ATTN_PITSTOPS',			'pits stops');

	define('TXML_NAME',						'name');
	define('TXML_VALUE',					'val');


	// Return root of DOM tree.
	function getRoot($filename)
	{
		$result = NULL;
		$dom = new DOMDocument();

		if ($dom->load($filename)) {
			$result = $dom->documentElement;
		}
		return $result;
	}


	// Get all XML_ELEMENT_NODES and build an "indexed" array.
	function children(&$parent, &$path, &$nodes)
	{
		$ch = $parent->childNodes;
		foreach ($ch as $node) {
			if ($node->nodeType == XML_ELEMENT_NODE) {
				$namenode = $node->getAttributeNode(TXML_NAME);
				$name = $namenode->value;
				$p = $path . "/" . $name;
				$nodes[$p] = $node;
				children($node, $p, $nodes);
			}
		}
	}


	// Get attribute "val" value of a specific element.
	function getval(&$key, &$nodes)
	{
		if (isset($nodes[$key]) && $nodes[$key]->nodeType == XML_ELEMENT_NODE) {
			$node = $nodes[$key];
			$valnode = $node->getAttributeNode(TXML_VALUE);
			return $valnode->value;
		}
		return NULL;
	}


	// Return all attributes of specific element as array.
	function getvalarray(&$key, &$nodes)
	{
		$result = NULL;
		if (isset($nodes[$key]) && $nodes[$key]->nodeType == XML_ELEMENT_NODE) {
			$ch = $nodes[$key]->childNodes;
			foreach ($ch as $node) {
				if ($node->nodeType == XML_ELEMENT_NODE) {
					$namenode = $node->getAttributeNode(TXML_NAME);
					$name = $namenode->value;
					$valnode = $node->getAttributeNode(TXML_VALUE);
					$val = $valnode->value;
					$result[$name] = $val;
				}
			}
		}
		return $result;
	}


	// Return all quali results in an array.
	function getStartlistArray($trackname, &$nodes)
	{
		$result = array();
		$key = TXML_SECT_RESULTS . "/" . $trackname . "/" . TXML_SECT_DRIVERS;
		$i = 1;
		$k = $key . "/" . "1";
		while ($val = getvalarray($k, $nodes)) {
			$result[$i] = $val;
			$i++;
			$k = $key . "/" . $i;
		}
		return $result;
	}


	function getQualiresultArray($trackname, &$nodes)
	{
		$result = array();
		$key = TXML_SECT_RESULTS . "/" . $trackname . "/" . TXML_SECT_RESULTS . "/" .
			   TXML_SECT_QUALIFICATION . "/" . TXML_SECT_RANK;
		$i = 1;
		$k = $key . "/" . "1";
		while ($val = getvalarray($k, $nodes)) {
			$result[$i] = $val;
			$i++;
			$k = $key . "/" . $i;
		}
		return $result;
	}


	function getRaceresultArray($trackname, &$nodes)
	{
		$result = array();
		$key = TXML_SECT_RESULTS . "/" . $trackname . "/" . TXML_SECT_RESULTS . "/" .
			   TXML_SECT_RACE1 . "/" . TXML_SECT_RANK;
		$i = 1;
		$k = $key . "/" . "1";
		while ($val = getvalarray($k, $nodes)) {
			$result[$i] = $val;
			$i++;
			$k = $key . "/" . $i;
		}
		return $result;
	}


?>
