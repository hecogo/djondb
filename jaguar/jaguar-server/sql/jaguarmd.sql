-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.1.37-1ubuntu5


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema jaguarmd
--

CREATE DATABASE IF NOT EXISTS jaguarmd;
USE jaguarmd;
CREATE TABLE  `jaguarmd`.`activities` (
  `id` int(11) NOT NULL DEFAULT '0',
  `activitytype` int(11) DEFAULT NULL,
  `startquantity` int(11) NOT NULL DEFAULT '1',
  `looptype` int(11) NOT NULL,
  `idprocessdef` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
INSERT INTO `jaguarmd`.`activities` VALUES  (1,0,1,0,1);
CREATE TABLE  `jaguarmd`.`events` (
  `id` int(11) NOT NULL,
  `eventtype` int(11) NOT NULL,
  `idpool` int(11) NOT NULL,
  `idprocessdef` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
INSERT INTO `jaguarmd`.`events` VALUES  (1,0,1,1);
CREATE TABLE  `jaguarmd`.`pools` (
  `id` int(11) NOT NULL,
  `poolname` varchar(20) NOT NULL,
  `idparticipant` int(11) DEFAULT NULL,
  `idprocessdef` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
INSERT INTO `jaguarmd`.`pools` VALUES  (1,'users',NULL,1);
CREATE TABLE  `jaguarmd`.`processdef` (
  `id` int(11) NOT NULL,
  `defname` varchar(100) NOT NULL,
  `processType` smallint(6) NOT NULL,
  `masterent` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Process Definition';
INSERT INTO `jaguarmd`.`processdef` VALUES  (1,'def1',1,'temp'),
 (2,'def2',1,'temp'),
 (3,'def3',1,'temp'),
 (4,'def4',1,'temp'),
 (5,'def5',1,'temp'),
 (6,'def6',1,'temp');
CREATE TABLE  `jaguarmd`.`sequenceflows` (
  `id` int(11) NOT NULL,
  `connectorname` varchar(20) NOT NULL,
  `idtasksource` int(11) DEFAULT NULL,
  `idtasktarget` int(11) DEFAULT NULL,
  `ideventsource` int(11) DEFAULT NULL,
  `ideventtarget` int(11) DEFAULT NULL,
  `sourcetype` int(11) NOT NULL,
  `targettype` int(11) NOT NULL,
  `conditiontype` int(11) NOT NULL,
  `expression` int(11) DEFAULT NULL,
  `quantity` int(11) NOT NULL,
  `idprocessdef` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
INSERT INTO `jaguarmd`.`sequenceflows` VALUES  (1,'',NULL,1,1,NULL,1,0,0,NULL,1,1);
CREATE TABLE  `jaguarmd`.`task` (
  `id` int(11) NOT NULL DEFAULT '0',
  `idactivity` int(11) DEFAULT NULL,
  `taskname` varchar(20) DEFAULT NULL,
  `tasktype` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
INSERT INTO `jaguarmd`.`task` VALUES  (1,1,'test',5);



/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
