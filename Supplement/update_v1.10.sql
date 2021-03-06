
ALTER TABLE `inspectordb`.`inspection_budget_year`
CHANGE COLUMN `d1` `d1` DOUBLE NULL DEFAULT NULL  ,
CHANGE COLUMN `d2` `d2` DOUBLE NULL DEFAULT NULL  ,
CHANGE COLUMN `d3` `d3` DOUBLE NULL DEFAULT NULL  ,
CHANGE COLUMN `d4` `d4` DOUBLE NULL DEFAULT NULL  ,
CHANGE COLUMN `d5` `d5` DOUBLE NULL DEFAULT NULL  ,
CHANGE COLUMN `d6` `d6` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d7` `d7` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d8` `d8` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d9` `d9` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d10` `d10` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d11` `d11` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d12` `d12` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d13` `d13` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d14` `d14` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d15` `d15` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d16` `d16` DOUBLE NULL DEFAULT NULL  ;

ALTER TABLE `inspectordb`.`inspection_budget`
CHANGE COLUMN `d1` `d1` DOUBLE NULL DEFAULT NULL  ,
CHANGE COLUMN `d2` `d2` DOUBLE NULL DEFAULT NULL  ,
CHANGE COLUMN `d3` `d3` DOUBLE NULL DEFAULT NULL  ,
CHANGE COLUMN `d4` `d4` DOUBLE NULL DEFAULT NULL  ,
CHANGE COLUMN `d5` `d5` DOUBLE NULL DEFAULT NULL  ,
CHANGE COLUMN `d6` `d6` DOUBLE NULL DEFAULT NULL  , 
CHANGE COLUMN `d7` `d7` DOUBLE NULL DEFAULT NULL  ;

ALTER TABLE `inspectordb`.`inspection` CHANGE COLUMN `id_inspection` `id_inspection` INT(11) NOT NULL,
CHANGE COLUMN `id_target` `name` TEXT NOT NULL,
DROP INDEX `fk_inspection_target`,
ADD COLUMN `n_inspection` VARCHAR(16) NULL AFTER `dtm_modif`,
ADD UNIQUE INDEX `n_inspection_UNIQUE` (`n_inspection` ASC);

DROP TABLE `company`;
