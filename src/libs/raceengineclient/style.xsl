<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:output method="html"/>

<!--  Author Eugen Treise -->

<!--	This xsl file was made to format results-*.xml files, which are created by torcs
		after a race, into readable html files.
-->
<!--	Usage: Open results-*.xml file (it must have a reference to this file) in your browser,
		or use an xslt processor to convert the xml file to a html file.
-->

<!-- Template for the params element -->
<xsl:template match="/params">

	<html>
	<head><title>TORCS Race Results</title></head>
	<body>

	<p><A HREF="http://www.torcs.org">TORCS Home Page</A></p>

	<!-- print Params attributes -->
	<xsl:for-each select="@*">
		<xsl:value-of select="name()"/> = <xsl:value-of select="."/><br/>
	</xsl:for-each>

	<!-- select the template by section name and call it -->
	<xsl:for-each select="section">
		<xsl:variable name="Section" select="@name"/>
		<HR/>
		<xsl:choose>
			<xsl:when test="$Section = 'Header' or $Section = 'Current'">
				<xsl:call-template name="Header"/>
			</xsl:when>
			<xsl:when test="$Section = 'Standings'">
				<xsl:call-template name="Standings"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="Track"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:for-each>

	</body>
	</html>
</xsl:template>


<!-- Template for Header and Current sections -->
<xsl:template name="Header">
	<h4>Section <xsl:value-of select="@name"/>: </h4>
	<!-- print all attributes and their values of all child elements in the current section -->
	<xsl:for-each select="*">
		<xsl:value-of select="@name"/> = <xsl:value-of select="@val"/> <br/>
	</xsl:for-each>
</xsl:template>


<!-- Template for "Trackname" sections -->
<!-- Call different templates for Practice and other Race sessions. -->
<xsl:template name="Track">
	<h2>
	Track: <xsl:value-of select="@name"/>
	</h2>
	<xsl:choose>
		<xsl:when test="section[@name='Results']/section[1]/@name = 'Practice'">
			<xsl:call-template name="Practice"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:call-template name="Race"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>


<!-- Template for Race sections with several drivers -->
<xsl:template name="Race">
	<xsl:for-each select="section[@name='Results']/section">
		<h3><xsl:value-of select="@name"/> </h3>
		<xsl:for-each select="*[@val]">
			<xsl:value-of select="@name"/> = <xsl:value-of select="@val"/> <br/>
		</xsl:for-each>
		<p>
		<table border="1">
		<!-- Table Head -->
		<tr>
		<td><b>Position</b></td>
		<xsl:for-each select="section[@name='Rank']/section[1]/*">
			<th><xsl:value-of select="@name"/></th>
		</xsl:for-each>
		</tr>
		<xsl:for-each select="section[@name='Rank']/section">

			<!-- choose an other format for human driver, for drivers with points and for drivers with high damage -->
			<xsl:variable name="FontWeight">
				<xsl:choose>
					<xsl:when test="attstr[@name='module' and @val='human']">
						<xsl:value-of select="'bold'"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="'normal'"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>

			<xsl:variable name="TextColor">
				<xsl:choose>
					<xsl:when test="attnum[@name='points' and @val>0]">
						<xsl:value-of select="'blue'"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="'black'"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>

			<xsl:variable name="BGColor">
				<xsl:choose>
					<xsl:when test="attnum[@name='damages' and @val>=10000]">
						<xsl:value-of select="'lightgrey'"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="'white'"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>

			<!-- set format for the next row -->
			<tr>
			<xsl:attribute name="style">
				<xsl:text>font-weight:</xsl:text>
				<xsl:value-of select="$FontWeight"/>
				<xsl:text>; color:</xsl:text>
				<xsl:value-of select="$TextColor"/>
				<xsl:text>; background-color:</xsl:text>
				<xsl:value-of select="$BGColor"/>
			</xsl:attribute>

			<!-- Table content (row) -->
			<td> <xsl:value-of select="@name"/> </td>
			<xsl:for-each select="*">
				<td>
				<xsl:call-template name="FormatedOutput"/>
				</td>
			</xsl:for-each>
			</tr>
		</xsl:for-each>
		</table>
		</p>
	</xsl:for-each>
</xsl:template>


<!-- Template for Practice section -->
<xsl:template name="Practice">
	<xsl:for-each select="section[@name='Results']/section">
		<h3><xsl:value-of select="@name"/> </h3>
		<!-- print all attributes with a value -->
		<xsl:for-each select="*[@val]">
			<xsl:value-of select="@name"/> = <xsl:value-of select="@val"/> <br/>
		</xsl:for-each>
		<xsl:value-of select="count(section)"/> laps <br/>
		<xsl:variable name="TotalTime" select="sum(//attnum[@name='time']/@val)"/>
		total practice time: <xsl:value-of select="floor($TotalTime div 60)"/> min <xsl:value-of select="round($TotalTime mod 60)"/> s<br/>
		<p>
		<table border="1">
		<!-- Table Head -->
		<tr>
		<th>Lap</th>
		<xsl:for-each select="section[1]/*">
			<th><xsl:value-of select="@name"/></th>
		</xsl:for-each>
		</tr>

		<!-- Table content (row) -->
		<xsl:for-each select="section">
			<tr>
			<td><xsl:value-of select="@name"/></td>
			<xsl:for-each select="*">
				<td>
				<xsl:call-template name="FormatedOutput"/>
				</td>
			</xsl:for-each>
			</tr>
		</xsl:for-each>
		</table>
		</p>
	</xsl:for-each>
</xsl:template>


<!-- Template for Standings section -->
<xsl:template name="Standings">
	<h3><xsl:value-of select="@name"/></h3>
	<p>
	<table border="1">
	<!-- Table header -->
	<tr>
		<th>Position</th>
		<th>Name</th>
		<th>Points</th>
	</tr>

	<xsl:for-each select="*">

		<!-- choose an other format for human driver and for drivers with points -->
		<xsl:variable name="FontWeight">
			<xsl:choose>
				<xsl:when test="attstr[@name='module' and @val='human'] or attnum[@name='points' and @val>0]">
					<xsl:value-of select="'bold'"/>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="'normal'"/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<xsl:variable name="TextColor">
			<xsl:choose>
				<xsl:when test="attstr[@name='module' and @val='human']">
					<xsl:value-of select="'red'"/>
				</xsl:when>
				<xsl:when test="attnum[@name='points' and @val>0]">
					<xsl:value-of select="'blue'"/>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="'black'"/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<!-- set format for the next row -->
		<tr>
		<xsl:attribute name="style">
			<xsl:text>font-weight:</xsl:text>
			<xsl:value-of select="$FontWeight"/>
			<xsl:text>; color:</xsl:text>
			<xsl:value-of select="$TextColor"/>
		</xsl:attribute>

		<!-- Table content (row) -->
		<td> <xsl:value-of select="@name"/> </td>
		<td> <xsl:value-of select="attstr[@name='name']/@val"/> </td>
		<td> <xsl:value-of select="number(attnum[@name='points']/@val)"/> </td>
		</tr>
	</xsl:for-each>

	</table>
	</p>
</xsl:template>


<!-- Print values, speed and time will be formated. -->
<xsl:template name="FormatedOutput">
	<xsl:choose>
		<xsl:when test="contains(@name,'speed')">
			<!-- convert speed from m/s to km/h -->
			<xsl:value-of select="round(3.6*@val)"/>
		</xsl:when>
		<xsl:when test="contains(@name,'time')">
			<!-- convert time from s to min:s -->
			<!-- (mod returns not exact values, therefore round to have 3 numbers behind the decimal point) -->
			<xsl:value-of select="floor(@val div 60)"/>:<xsl:value-of select="round((@val mod 60)*1000) div 1000"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="@val"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

</xsl:stylesheet>
