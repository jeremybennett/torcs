-- phpMyAdmin SQL Dump
-- version 2.6.0-pl2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Nov 08, 2004 at 09:17 PM
-- Server version: 3.23.55
-- PHP Version: 4.3.1
--
-- Database: `mydb`
--

-- --------------------------------------------------------

--
-- Table structure for table `trb_car`
--

DROP TABLE IF EXISTS `trb_car`;
CREATE TABLE `trb_car` (
  `carid` int(11) NOT NULL auto_increment,
  `name` varchar(40) NOT NULL default '',
  `author` varchar(40) NOT NULL default '',
  `mass` float NOT NULL default '0',
  `tank` float NOT NULL default '0',
  `cxa` float NOT NULL default '0',
  `power` float NOT NULL default '0',
  `width` float NOT NULL default '0',
  `length` float NOT NULL default '0',
  `train` enum('rwd','fwd','4wd') NOT NULL default 'rwd',
  `description` text NOT NULL,
  PRIMARY KEY  (`carid`),
  UNIQUE KEY `name` (`name`)
) TYPE=MyISAM AUTO_INCREMENT=21 ;

--
-- Dumping data for table `trb_car`
--

INSERT INTO `trb_car` VALUES (1, 'Alfa Romeo 155 DTM', 'Andrea Alfieri', 1100, 100, 0.576, 336, 1.9, 4.8, '4wd', '');
INSERT INTO `trb_car` VALUES (2, 'Viper GTS-R', 'asdas asda (ViPeR)', 1250, 100, 0.578, 419, 2, 4.9, 'rwd', '');
INSERT INTO `trb_car` VALUES (3, 'Mercedes CLK DTM', 'Christophe Guionneau', 1050, 100, 0.646, 350, 1.96, 4.76, 'rwd', '');
INSERT INTO `trb_car` VALUES (4, 'Porsche GT3 RS', 'Eric Espié', 1150, 100, 0.36, 298, 1.9, 4.43, 'rwd', '');
INSERT INTO `trb_car` VALUES (5, 'Ferrari 360 Modena', 'Eric Espié', 1200, 100, 0.532, 328, 1.922, 4.48, 'rwd', '');
INSERT INTO `trb_car` VALUES (6, 'NASCAR RWD', 'Eric Espié', 1150, 100, 0.646, 455, 2, 5, 'rwd', '');
INSERT INTO `trb_car` VALUES (8, 'Lotus GT1', 'asdas asda (ViPeR)', 1000, 100, 0.448, 435, 2, 4.45, 'rwd', '');
INSERT INTO `trb_car` VALUES (9, 'McLaren F1', 'asdas asda (ViPeR)', 1060, 100, 0.648, 509, 2, 4.41, 'rwd', '');
INSERT INTO `trb_car` VALUES (10, 'Baja Bug', 'Jean-Christophe Durieu', 600, 50, 0.9, 82, 1.8, 3.8, 'rwd', '');
INSERT INTO `trb_car` VALUES (11, 'Ford Focus WRC', 'Patrick Wisselo', 850, 100, 0.77, 321, 1.91, 3.89, '4wd', '');
INSERT INTO `trb_car` VALUES (12, 'Peugeot 206 WRC', 'Patrick Wisselo', 850, 100, 0.77, 344, 1.91, 3.89, '4wd', '');
INSERT INTO `trb_car` VALUES (13, 'Peugeot 306 Maxi', 'Patrick Wisselo', 950, 100, 0.77, 246, 2, 3.89, '4wd', '');
INSERT INTO `trb_car` VALUES (14, 'Mitsubishi Lancer EVO VI WRC', 'Patrick Wisselo', 900, 100, 0.6, 321, 2.02, 4.2, '4wd', '');
INSERT INTO `trb_car` VALUES (15, 'Mitsubishi Lancer EVO V WRC', 'Patrick Wisselo', 900, 100, 0.6, 321, 2.02, 4.2, '4wd', '');
INSERT INTO `trb_car` VALUES (16, 'Subaru Impreza WRC', 'Patrick Wisselo', 900, 100, 0.6, 329, 1.98, 4.12, '4wd', '');
INSERT INTO `trb_car` VALUES (17, 'Toyota Corolla WRC', 'Patrick Wisselo', 950, 100, 0.77, 329, 1.98, 3.81, '4wd', '');
INSERT INTO `trb_car` VALUES (18, 'Porsche GT1', 'Christophe Guionneau', 950, 100, 0.684, 586, 2, 4.7, 'rwd', '');
INSERT INTO `trb_car` VALUES (19, 'Acura NSX type S-Zero', 'asdas asda (ViPeR)', 1200, 100, 0.612, 285, 1.92, 5, 'rwd', '');
INSERT INTO `trb_car` VALUES (20, 'Buggy', 'Eric Espié', 650, 30, 1.14, 190, 2, 4, 'rwd', '');


-- --------------------------------------------------------

--
-- Table structure for table `trb_track`
--

DROP TABLE IF EXISTS `trb_track`;
CREATE TABLE `trb_track` (
  `trackid` int(11) NOT NULL auto_increment,
  `name` varchar(40) NOT NULL default '',
  `nbpits` int(11) NOT NULL default '0',
  `width` float NOT NULL default '0',
  `length` float NOT NULL default '0',
  `author` varchar(40) NOT NULL default '',
  `type` enum('road','dirt','oval') NOT NULL default 'road',
  `description` text NOT NULL,
  PRIMARY KEY  (`trackid`),
  UNIQUE KEY `name` (`name`)
) TYPE=MyISAM AUTO_INCREMENT=35 ;

--
-- Dumping data for table `trb_track`
--

INSERT INTO `trb_track` VALUES (3, 'E-Track 1', 20, 15, 3243.64, 'Eric Espié', 'road', 'Track with a ''Bus Stop'' like chicane.');
INSERT INTO `trb_track` VALUES (4, 'E-Track 2', 15, 12, 3147.47, 'Eric Espié', 'road', 'A narrow track with a lot of tight turns and almost no opportunities to overtake.');
INSERT INTO `trb_track` VALUES (5, 'E-Track 3', 20, 18, 4799.34, 'Eric Espié', 'road', 'A fast track with difficult height profile.');
INSERT INTO `trb_track` VALUES (6, 'E-Track 4', 20, 15, 7041.68, 'Eric Espié', 'road', 'A very fast track with good opportunities to overtake.');
INSERT INTO `trb_track` VALUES (7, 'E-Track 5', 0, 20, 1621.73, 'Eric Espié', 'oval', '');
INSERT INTO `trb_track` VALUES (8, 'E-Track 6', 20, 13, 4441.29, 'Eric Espié', 'road', '');
INSERT INTO `trb_track` VALUES (9, 'E-Road', 26, 16, 3260.43, 'Eric Espié', 'road', '');
INSERT INTO `trb_track` VALUES (10, 'CG Speedway number 1', 0, 15, 2057.53, 'Christophe Guionneau', 'road', '');
INSERT INTO `trb_track` VALUES (11, 'CG track 2', 16, 15, 3185.83, 'Christophe Guionneau', 'road', '');
INSERT INTO `trb_track` VALUES (12, 'CG track 3', 18, 10, 2843.1, 'Christophe Guionneau', 'road', 'A beautiful track with difficult surfaces and bumps.');
INSERT INTO `trb_track` VALUES (13, 'Spring', 40, 12, 22129.8, 'Eric Espié', 'road', 'A very long and interesting track.');
INSERT INTO `trb_track` VALUES (14, 'Wheel 1', 20, 16, 4257.62, 'Eric Espié', 'road', '');
INSERT INTO `trb_track` VALUES (15, 'Aalborg', 0, 12, 2505.46, 'Torben Thellefsen', 'road', 'This track has been ported from RARS.');
INSERT INTO `trb_track` VALUES (16, 'Alpine 1', 16, 12, 6355.65, 'Eric Espié', 'road', 'Beautiful and difficult track.');
INSERT INTO `trb_track` VALUES (17, 'Michigan Speedway', 13, 18, 2529.88, 'Eric Espié', 'oval', '');
INSERT INTO `trb_track` VALUES (18, 'A-Speedway', 20, 25, 1908.32, 'Eric Espié', 'oval', '');
INSERT INTO `trb_track` VALUES (19, 'B-Speedway', 20, 30, 3999.12, 'Eric Espié', 'oval', '');
INSERT INTO `trb_track` VALUES (20, 'C-Speedway', 20, 30, 3294.4, 'Eric Espié', 'oval', '');
INSERT INTO `trb_track` VALUES (21, 'D-Speedway', 20, 30, 3427.43, 'Eric Espié', 'oval', '');
INSERT INTO `trb_track` VALUES (22, 'E-Speedway', 20, 30, 4103.84, 'Eric Espié', 'oval', '');
INSERT INTO `trb_track` VALUES (23, 'F-Speedway', 20, 30, 3703.83, 'Eric Espié', 'oval', '');
INSERT INTO `trb_track` VALUES (24, 'G-Speedway', 20, 30, 2977.6, 'Eric Espié', 'oval', '');
INSERT INTO `trb_track` VALUES (25, 'Hill', 0, 12, 4844.14, 'Thomas Strub', 'road', '');
INSERT INTO `trb_track` VALUES (26, 'Dirt 1', 0, 10, 1072.93, 'Eric Espié', 'dirt', '');
INSERT INTO `trb_track` VALUES (27, 'Dirt 2', 0, 10, 1005.58, 'Eric Espié', 'dirt', 'Track with high jumps and woops.');
INSERT INTO `trb_track` VALUES (28, 'Dirt 3', 8, 20, 1621.73, 'Eric Espié', 'dirt', '');
INSERT INTO `trb_track` VALUES (29, 'Dirt 4', 26, 16, 3260.43, 'Eric Espié', 'dirt', '');
INSERT INTO `trb_track` VALUES (30, 'Dirt 5', 0, 10, 1072.93, 'Eric Espié', 'dirt', '');
INSERT INTO `trb_track` VALUES (31, 'Dirt 6', 0, 15, 3147.46, 'Eric Espié', 'dirt', '');
INSERT INTO `trb_track` VALUES (32, 'Mixed 1', 0, 10, 1014.22, 'Eric Espié', 'dirt', '');
INSERT INTO `trb_track` VALUES (33, 'Mixed 2', 0, 10, 1412.9, 'Eric Espié', 'dirt', '');
INSERT INTO `trb_track` VALUES (34, 'Rainbow Road', 0, 20, 4262.45, 'bytex64', 'road', '');
