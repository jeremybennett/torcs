/*
	copyright   : (C) 2004 Bernhard Wymann
	email       : berniw@bluewin.ch
	version     : $Id$

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
*/

/* exchange image inr through iobject */
function imgchange(inr, iobjekt)
{
    window.document.images[inr].src = iobjekt.src;
}

/* change two frames at once */
function changetwoframes(uri1, dest1, uri2, dest2)
{
  var frame1 = eval("parent." + dest1);
  var frame2 = eval("parent." + dest2);
  frame1.location.href = uri1;
  frame2.location.href = uri2;
}


/* DOM available? */
function isDOM() {
	return document.getElementById;
}


function removeChildren(element, n)
{
	for (; n > 0; n--) {
		element.removeChild(element.firstChild);
	}
}


/* remove the #selector after selection */
function removeSelectBox(id)
{
	var e = document.getElementById(id);
	e.parentNode.removeChild(e);
}

/* place n time the given string in element */
function insertTextInput(n, s, id, idselector)
{
	if (isDOM()) {
		/*removeSelectBox(idselector);*/
		var element = document.getElementById(id);
		if (typeof element == "object") {
			/* search for <tr>, create a template */
			var i = 0;
			var tb = element.childNodes[0];
			while (i < element.childNodes.length && tb.nodeName != "TBODY") {
				i++;
				tb = element.childNodes[i];
			}
			var deletechildren = tb.childNodes.length;

			var j = 0;
			var tr = tb.childNodes[0];
			while (j < tb.childNodes.length && tr.nodeName != "TR") {
				j++;
				tr = tb.childNodes[j];
			}

			for (var i = 0; i < n; i++) {
				var nc = tr.cloneNode(true);
				tb.appendChild(nc);
				var k = 0;
				var td = nc.childNodes[0];
				while (k < nc.childNodes.length && td.nodeName != "TD") {
					k++;
					td = nc.childNodes[k];
				}
				td.childNodes[0].nodeValue = "Answer " + (i+1) + ":";

			}
			removeChildren(tb, deletechildren);
		}
	}
}
