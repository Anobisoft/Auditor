--                 
-- ReferenceBooks
--

USE inspectordb;

CREATE TABLE `budget_level` (
  `id_lvl` tinyint NOT NULL AUTO_INCREMENT,
  `level` varchar(19) DEFAULT NULL,
  PRIMARY KEY (`id_lvl`)
) ENGINE=MyISAM;

CREATE TABLE `data_gr1` (
  `id` tinyint NOT NULL AUTO_INCREMENT,
  `name` varchar(81) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM;

CREATE TABLE `data_gr2` (
  `id` tinyint NOT NULL AUTO_INCREMENT,
  `name` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM;

CREATE TABLE `contraventions` (
  `id` tinyint NOT NULL AUTO_INCREMENT,
  `name` varchar(31) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM;

CREATE TABLE `reasons` (
  `id` tinyint NOT NULL AUTO_INCREMENT,
  `name` varchar(94) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM;

INSERT INTO `budget_level` (level) VALUES
('Федеральный'),
('Региональный'),
('Местный'),
('Прочее');

INSERT INTO `data_gr1` (name) VALUES
('Недостача денежных средств'),
('Недостача ТМЦ'),
('Излишки денежных средств'),
('Излишки ТМЦ'),
('Нецелевые расходы'),
('Неэффективное использование бюджетных средств'),
('Неправильное списание, расходование денежных средств'),
('Неправильное списание, расходование материальных запасов, в том числе ГСМ'),
('Неправильная выплата (переплата) зарплаты, авансов, премий, отпускных, мат.помощи'),
('Недоплата зарплаты, премий, мат.помощи'),
('Недопоступление доходов'),
('Завышение СМР'),
('Прочие Финансовые нарушения'),
('Прочие Нефинансовые нарушения'),
('Нарушения Федерального закона №94-ФЗ'),
('Общий объем проверенных средств');

INSERT INTO `data_gr2` (name) VALUES
('Устранено нарушений: зачет нецелевых'),
('Устранено нарушений: возмещено в бюджеты'),
('Внесены изменения в РЦП'),
('Неустранимые'),
('Не устранено'),
('Налож штрафы'),
('Уплачены штрафы');


INSERT INTO `contraventions` (name) VALUES
('Общий объем проверенных средств'),
('Общая сумма нарушений'),
('В том числе, нецелевые'),
('Финансовые нарушения'),
('Прочие Нефинансовые нарушения'),
('Нарушения  94-ФЗ'),
('Устранено нарушений'),
('Неустранимые'),
('Не устранено'),
('Зачет нецелевых'),
('Возмещено в бюджет'),
('Наложено штрафов'),
('Уплачено штрафов');

INSERT INTO `reasons` (name) VALUES
('Плановая проверка'),
('По заданию (постановлению, распоряжению) Правительства РТ'),
('По обращению правоохранительных органов'),
('По обращениям граждан, включая обращения должностных лиц и бюджетных учреждений и организаций');
