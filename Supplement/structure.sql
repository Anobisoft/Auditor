
DROP DATABASE IF EXISTS `inspectordb`;
CREATE DATABASE `inspectordb` DEFAULT CHARSET=utf8;
USE inspectordb;

--
-- Foreign key checks OFF 
--

SET foreign_key_checks = 0; 


--
-- Table structure for table `inspector`
--

CREATE TABLE `inspector` (
  `id_inspector` int(11) NOT NULL AUTO_INCREMENT,
  `surname` varchar(45) DEFAULT NULL,
  `name` varchar(45) DEFAULT NULL,
  `patronymic` varchar(45) DEFAULT NULL,
  `pwd` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id_inspector`)
) ENGINE=InnoDB;

--
-- Table structure for table `inspection`
--

CREATE TABLE `inspection` (
  `id_inspection` int(11) NOT NULL AUTO_INCREMENT,
  `dt_inspection` date NOT NULL,
  `dt_pbegin` date NOT NULL,
  `dt_pend` date NOT NULL,
  `name` text,
  `motivation` tinyint,
  `id_director` int(11),
  `id_inspector_m` int(11) NOT NULL,
  `comment` text,
  `dtm_modif` datetime NOT NULL,
  `n_inspection` VARCHAR(16) DEFAULT NULL,
  PRIMARY KEY (`id_inspection`),
  UNIQUE KEY `n_inspection_UNIQUE` (`n_inspection`),
  KEY `fk_inspection_director` (`id_director`),
  KEY `fk_inspection_inspector_m` (`id_inspector_m`),
  CONSTRAINT `fk_inspection_director` FOREIGN KEY (`id_director`) REFERENCES `inspector` (`id_inspector`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_inspection_inspector_m` FOREIGN KEY (`id_inspector_m`) REFERENCES `inspector` (`id_inspector`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;

--
-- Table structure for table `inspection_budget_year`
--

CREATE TABLE `inspection_budget_year` (
  `id_inspection` int(11) NOT NULL,
  `id_budget_lvl` int(11) NOT NULL,
  `year` year(4) NOT NULL,
  `d1` DOUBLE DEFAULT NULL,
  `d2` DOUBLE DEFAULT NULL,
  `d3` DOUBLE DEFAULT NULL,
  `d4` DOUBLE DEFAULT NULL,
  `d5` DOUBLE DEFAULT NULL,
  `d6` DOUBLE DEFAULT NULL,
  `d7` DOUBLE DEFAULT NULL,
  `d8` DOUBLE DEFAULT NULL,
  `d9` DOUBLE DEFAULT NULL,
  `d10` DOUBLE DEFAULT NULL,
  `d11` DOUBLE DEFAULT NULL,
  `d12` DOUBLE DEFAULT NULL,
  `d13` DOUBLE DEFAULT NULL,
  `d14` DOUBLE DEFAULT NULL,
  `d15` DOUBLE DEFAULT NULL,
  `d16` DOUBLE DEFAULT NULL,
  PRIMARY KEY (`id_inspection`,`id_budget_lvl`,`year`),
  KEY `fk_inspection_budget_year_inspection` (`id_inspection`),
  CONSTRAINT `fk_inspection_budget_year_inspection` FOREIGN KEY (`id_inspection`) REFERENCES `inspection` (`id_inspection`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;

--
-- Table structure for table `inspection_budget`
--

CREATE TABLE `inspection_budget` (
  `id_inspection` int(11) NOT NULL,
  `id_budget_lvl` int(11) NOT NULL,
  `d1` DOUBLE DEFAULT NULL,
  `d2` DOUBLE DEFAULT NULL,
  `d3` DOUBLE DEFAULT NULL,
  `d4` DOUBLE DEFAULT NULL,
  `d5` DOUBLE DEFAULT NULL,
  `d6` DOUBLE DEFAULT NULL,
  `d7` DOUBLE DEFAULT NULL,
  PRIMARY KEY (`id_inspection`,`id_budget_lvl`),
  KEY `fk_inspection_budget_year_inspection` (`id_inspection`),
  CONSTRAINT `fk_inspection_budget_inspection` FOREIGN KEY (`id_inspection`) REFERENCES `inspection` (`id_inspection`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;

--
-- Table structure for table `inspection_group`
--

CREATE TABLE `inspection_group` (
  `id_inspection` int(11) NOT NULL,
  `id_inspector` int(11) NOT NULL,
  PRIMARY KEY (`id_inspection`,`id_inspector`),
  KEY `fk_inspection_group_inspection` (`id_inspection`),
  KEY `fk_inspection_group_inspector` (`id_inspector`),
  CONSTRAINT `fk_inspection_group_inspection` FOREIGN KEY (`id_inspection`) REFERENCES `inspection` (`id_inspection`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_inspection_group_inspector` FOREIGN KEY (`id_inspector`) REFERENCES `inspector` (`id_inspector`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;


--
-- Foreign key checks ON 
--

SET foreign_key_checks = 1; 






















