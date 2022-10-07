USE `world`;

-- mysql  Ver 8.0.27 for Linux on x86_64 (Gentoo Linux mysql-8.0.27)
-- 혹시 버전 이슈가 있을수도 있어서

-- 1번
SELECT * FROM `city` WHERE `CountryCode` = "KOR" ORDER BY `Population` DESC; 

-- 2번
SELECT * FROM `city` WHERE `Population` BETWEEN 8000000 AND 10000000 ORDER BY `Population` DESC;

-- 3번
SELECT `CountryCode`, COUNT(`id`) AS `CityCount` FROM `city` GROUP BY `CountryCode` ORDER BY `CityCount` DESC LIMIT 6;

-- 4번
SELECT * FROM `city` WHERE `CountryCode` = "USA" AND `Population` >= 100000;

-- 5번
SELECT `city`.`Name` FROM `city`
WHERE `CountryCode` = (
	SELECT DISTINCT `CountryCode` FROM `country` WHERE `Continent` = "Africa"
);

-- 6번
SELECT `country`.`Name`, COUNT(`city`.`id`) AS `CityCount`
FROM `country` INNER JOIN `city` ON `country`.`Code` = `city`.`CountryCode`
GROUP BY `city`.`CountryCode`;

-- 7번
SELECT `country`.`Name` FROM `country`
LEFT JOIN `countrylanguage` ON `country`.`Code` = `countrylanguage`.`CountryCode`
WHERE `country`.`Continent` = "Africa" AND `Language` IS NULL;

-- 8번
SELECT COUNT(`id`) AS `CityCount` FROM `city`
WHERE `CountryCode` = (
	SELECT DISTINCT `Code` FROM `country` WHERE `Name` = "South Korea"
);

-- 9번
SELECT * FROM `city` WHERE `CountryCode` = "KOR"
UNION 
SELECT * FROM `city` WHERE `CountryCode` = "CHN";