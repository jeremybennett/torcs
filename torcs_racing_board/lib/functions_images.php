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

	function commitJPEGImage(
		$im_id,
		$path_to_root,
		$postvar,
		$filesize,
		$locpath,
		$im_width,
		$im_height,
		$th_width,
		$th_height,
		$quality
	)
	{
		if (checkPostFile($postvar, $filesize, 'image/jpeg') == 0) {
			// Ok.
			$file = $_FILES[$postvar];
			if (is_uploaded_file($file['tmp_name'])) {
				$path = getcwd() . '/' . $path_to_root . $locpath . $im_id . '.jpg';
				$path_tn = getcwd() . '/' . $path_to_root . $locpath . $im_id . '_tn.jpg';
				// Check size and format.
				$size = getImageSize($file['tmp_name']);
				if ($size[0] != $im_width || $size[1] != $im_height || $size[2] != 2) {
					// Error, size or format wrong.
					return;
				}
				// Create thumbnail.
				$thumbnail = ImageCreateTrueColor($th_width, $th_height);
				$photo = ImageCreateFromJPEG($file['tmp_name']);
				if ($thumbnail && $photo) {
					ImageCopyResampled($thumbnail, $photo, 0, 0, 0, 0,
						$th_width, $th_height, $im_width, $im_height);
					ImageJPEG($thumbnail, $path_tn, $quality);
				}
				move_uploaded_file($file['tmp_name'], $path);
			}
		} else {
			// Remove Image.
			$path = getcwd() . '/' . $path_to_root . $locpath . $im_id . '.jpg';
			$path_tn = getcwd() . '/' . $path_to_root . $locpath . $im_id . '_tn.jpg';
			if (file_exists($path)) {
				unlink($path);
			}
			if (file_exists($path_tn)) {
				unlink($path_tn);
			}
		}
	}

?>
