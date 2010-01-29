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
-- Create schema jaguardata
--

CREATE DATABASE IF NOT EXISTS jaguardata;
USE jaguardata;

--
-- Definition of table `jaguardata`.`key_table`
--

DROP TABLE IF EXISTS `jaguardata`.`key_table`;
CREATE TABLE  `jaguardata`.`key_table` (
  `id` varchar(50) NOT NULL,
  `value` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `jaguardata`.`key_table`
--

/*!40000 ALTER TABLE `key_table` DISABLE KEYS */;
LOCK TABLES `key_table` WRITE;
INSERT INTO `jaguardata`.`key_table` VALUES  ('token',250),
 ('processinstance',100);
UNLOCK TABLES;
/*!40000 ALTER TABLE `key_table` ENABLE KEYS */;


--
-- Definition of table `jaguardata`.`processinstance`
--

DROP TABLE IF EXISTS `jaguardata`.`processinstance`;
CREATE TABLE  `jaguardata`.`processinstance` (
  `id` int(11) NOT NULL,
  `idprocessdef` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  `idmasterent` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `jaguardata`.`processinstance`
--

/*!40000 ALTER TABLE `processinstance` DISABLE KEYS */;
LOCK TABLES `processinstance` WRITE;
INSERT INTO `jaguardata`.`processinstance` VALUES  (1,1,0,1),
 (2,1,0,1),
 (3,1,0,1),
 (4,1,0,1),
 (5,1,0,1),
 (6,1,0,1),
 (51,1,0,1),
 (52,1,0,1);
UNLOCK TABLES;
/*!40000 ALTER TABLE `processinstance` ENABLE KEYS */;


--
-- Definition of table `jaguardata`.`tokens`
--

DROP TABLE IF EXISTS `jaguardata`.`tokens`;
CREATE TABLE  `jaguardata`.`tokens` (
  `id` int(11) NOT NULL,
  `idtask` int(11) NOT NULL,
  `idprocessinst` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `jaguardata`.`tokens`
--

/*!40000 ALTER TABLE `tokens` DISABLE KEYS */;
LOCK TABLES `tokens` WRITE;
INSERT INTO `jaguardata`.`tokens` VALUES  (1,1,1,4),
 (2,1,2,2),
 (3,1,3,2),
 (4,1,4,2),
 (5,1,5,2),
 (6,1,6,2),
 (151,1,1,2),
 (201,1,51,2),
 (202,1,52,2);
UNLOCK TABLES;
/*!40000 ALTER TABLE `tokens` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
