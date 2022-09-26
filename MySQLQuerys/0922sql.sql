-- select distinct CountryCode from city where CountryCode="KOR";
-- distinct: 중복된 것들 하나만

-- select * from city where CountryCode="KOR" AND Population>=1000000;
-- select * from city where CountryCode="KOR" OR CountryCode="CHN" OR CountryCode="JPN";
-- select * from city where NOT CountryCode="KOR" AND Population>=1000000;

-- select * from city where CountryCode in("KOR","CHN","JPN");
-- IN(A,B,C); 로 감싼다. VALUE 처럼
-- select * from city where CountryCode="KOR" AND Population BETWEEN 1000000 AND 5000000;
-- select * from city where CountryCode="KOR" AND (Population >=1000000 AND Population <=5000000);

-- SELECT * FROM city WHERE CountryCode = "KOR" ORDER BY Population DESC;
-- SELECT CountryCode, Population FROM city ORDER BY CountryCode, Population DESC;


-- SELECT INTO 
-- CREATE TABLE => SELECT
-- CREATE TABLE sampleTable SELECT -- FROM -- WHERE;

-- CREATE TABLE city_new SELECT * FROM city WHERE CountryCode="KOR";
-- SELECT * FROM city_new;

-- desc city; -- 스키마가 나옴

-- INSERT INTO city_kor SELECT * FROM city WHERE CountryCode="KOR";
-- SELECT * FROM city_kor;

-- SHOW CREATE TABLE city;
-- 테이블 생성하는 구문을 돌려줌 (DDL 을 돌려줌)

-- CREATE TABLE city_popul SELECT `Name`, `Population` FROM city;
-- SELECT * FROM city_popul;
-- DROP TABLE city_popul;

-- CREATE TABLE `city_popul` (
--   `Name` char(35) NOT NULL DEFAULT '',
--   `Population` int NOT NULL DEFAULT '0'
-- ) ENGINE=InnoDB AUTO_INCREMENT=20001 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
-- INSERT INTO city_popul SELECT `Name`, `Population` FROM city;
-- SELECT * FROM city_popul;
-- DROP TABLE city_popul;



--  IF(a, b, c);
-- a 는 조건식
-- a == true, then return b, if not, c

-- SELECT IF(2>1, 1, 0) IF1, IF('A' = 'a', 'SAME', 'NOTSAME') IF2, IF(1 = 2, 1, 'A') IF3;
-- MYSQL 은 영어 대소문자 비교 안함

-- IFNULL(a, b);
-- if a == null,  returns b, if not a;

-- SELECT IFNULL(1, 0) IFNULL1,
-- IFNULL(NULL * 3, 0) IFNULL2;

-- NULLIF(a, b)
-- a == b return NULL, if not a

-- SELECT NULLIF(3, 3)  NULLIF1,
-- NULLIF (154, 1) NULLIF2,
-- NULLIF(NULL, NULL) NULLIF3;


-- SELECT AVG(LifeExpectancy) AS LifeExpectancyAvg FROM country;
-- SELECT AVG(IFNULL(LifeExpectancy, 0)) AS LifeExpectancyAvg_NullIsZero FROM country;

-- SELECT COUNT(LifeExpectancy) AS LifeExpectancy_ExcludeNull FROM country;
-- SELECT COUNT(IFNULL(LifeExpectancy, 0)) As LifeExpectancy_IncludeNull FROM country;

-- SELECT COUNT(*) FROM country WHERE LifeExpectancy IS NULL;
-- SELECT COUNT(*) FROM country WHERE LifeExpectancy IS NOT NULL;

-- SELECT
-- CASE 
-- 	WHEN LENGTH(`Name`) > 3 THEN UPPER(SUBSTRING(`Name`, 1, 3))
--     WHEN LENGTH(`Name`) <= 3 THEN UPPER(`Name`)
-- END AS "Name", `Population`
-- FROM city;


-- 서브쿼리
-- 단일행 (Single Row): 결과가  레코드 하나인 서브쿼리, 일반 연산자 사용 ( 논리 연산자 사용 가능함ㅁ)
-- 다중행 (Multi Row): 결과가 레코드 여러 개인 서브쿼리, 다중행 연산자 사용 (IN, ALL, ANY, EXISTS)
-- 멀티 컬럼 (Multi COlumn) 결과가 컬럼  여러  개인 서브쿼리

-- SELECT COUNT(*) FROM city
-- WHERE CountryCode = (
-- 	SELECT `Code` FROM country WHERE `Name` = "South Korea"
-- );

-- SELECT `Name`, `Population` FROM city
-- WHERE Population > (
-- 	SELECT AVG(Population) FROM city WHERE `CountryCode` = "KOR"
-- ) ORDER BY `Population`;

-- 다중행 연산자
-- ALL: Operator 와 같이 쓰임, 여러개의 레코드의 AND 효과 (예: 가장 큰 값보다 큰)
-- ANY: Operator 와 같이 쓰임, 여러 개의 레코드의 OR 효과 (예: 가장 작은 값보다 큰)
-- IN/EXISTS: 결과값 중에 있는 것 중에서의 의미
-- IN: 전체 레코드 스캔,  EXISTS는 존재여부만 확인 (상대적으로 빠름)
	-- TRUE: 존재, FALSE: 존재 x

-- SELECT `CountryCode`, COUNT(*) FROM `city`
-- WHERE `CountryCode` IN (
-- 	SELECT `Code` FROM `country` WHERE `Name` IN ("South Korea", "China", "Japan")
-- ) GROUP BY `CountryCode`;

-- SELECT `Name`, `CountryCode`, `Population` FROM `city`
-- WHERE Population > 5000000;

-- SELECT `Name`, `CountryCode`, `Population` FROM `city`
-- WHERE (`Name`, `CountryCode`) IN (
-- 	SELECT `Name`, `CountryCode` FROM `city` WHERE `Population` > 5000000
-- );

-- SELECT `Name`, `CountryCode`, `Population` FROM `city`
-- WHERE `Population` > ALL (
-- 	SELECT `Population` FROM `city` WHERE `CountryCode` = "KOR"
-- );

-- SELECT `Name`, `CountryCode`, `Population` FROM `city`
-- WHERE `Population` > ANY (
-- 	SELECT `Population` FROM `city` WHERE `CountryCode` = "KOR"
-- );

-- SELECT `Name`, `CountryCode`, `Population` FROM `city`
-- WHERE EXISTS ( -- 결과값에 하나라도 포함이 되어 있다면 선택됨? 믕
-- 	SELECT `CountryCode`
--     FROM `country`
--     WHERE `CountryCode` IN ("KOR", "CHN", "JPN")
-- );


-- SELECT *, (
-- 	CASE 
-- 		WHEN `Population` < 100000 THEN "small"
--         WHEN `Population` < 1000000 THEN "medium"
--         WHEN `Population` < 10000000 THEN "large"
--         ELSE "very large"
-- 	END
-- ) AS RS
-- FROM `city`

-- SELECT city.Name, city.CountryCode, country.GNP FROM city JOIN country ON city.CountryCode = country.Code

-- join 만 쓰면  inner join 임
-- JOIN a.x = b.x ON ... AND ... 여러개의 Join 가능

-- SELECT a.id, a.Name, a.CountryCode, b.Code, b.Name AS Country_Name, a.District
-- FROM city AS a INNER JOIN country AS b
-- ON a.CountryCode = b.Code

-- SELECT b.Name AS Country_Name, a.Language, a.IsOfficial
-- FROM countrylanguage AS a INNER JOIN country AS b
-- ON a.CountryCode = b.Code;

-- SELECT country.Name, COUNT(city.ID) AS "Cities"
-- FROM country JOIN city
-- ON country.Code = city.CountryCode
-- GROUP BY country.Name WITH ROLLUP;
-- WITH ROLLUP 붙이면 전체 데이터를 집계하는 기능, 맨 아레에 전체 데이터 겟수가 나온다


-- SELECT a.continent, COUNT(*)
-- FROM country AS a
-- JOIN city AS b
-- ON a.Code = b.CountryCode -- INNER JOIN 은 조건 일치하지 않은 친구들은 다 빠짐
-- GROUP BY a.continent;

-- SELECT a.continent, COUNT(*) AS 전체건수, COUNT(b.id) AS 도시수
-- FROM country AS a
-- LEFT JOIN city AS b
-- ON a.Code = b.CountryCode
-- GROUP BY a.continent;

-- SELECT a.continent, COUNT(*) AS 전체건수, COUNT(b.id) AS 도시수
-- FROM city AS b
-- RIGHT JOIN country AS a
-- ON a.Code = b.CountryCode
-- GROUP BY a.continent;

-- SELECT count(city.id) AS "국가코드 없는 도시" FROM city WHERE city.CountryCode IS NULL;

-- SELECT count(country.Code) - count(city.ID) AS "도시 없는 나라" FROM country
-- LEFT JOIN city ON country.Code = city.CountryCode;

-- SELECT COUNT(country.Code) - count(city.ID) AS "도시 없는 나라" FROM city
-- RIGHT JOIN country ON city.CountryCode = country.Code;

-- SELECT COUNT(*)
-- FROM city LEFT JOIN country ON city.CountryCode = country.Code;

-- SELECT COUNT(*)
-- FROM city RIGHT JOIN country ON city.CountryCode = country.Code;

-- 카테시안 곱
-- 내부 조인에서 ON 을 안 하면 a*b 연산이 아릅답게 일어남
-- 가능한 모든 조합을 만듬
-- 크로스 조인이라고도 부른다고 함
-- SELECT a.continent, COUNT(*) AS 전체건수, COUNT(b.id) AS 도시수
-- FROM city AS b
-- -- JOIN country AS a
-- CROSS JOIN country AS a
-- ON a.Code = b.CountryCode -- CROSS JOIN 에 ON 붙히면 INNER JOIN 에 ON 과 같다고 함
-- GROUP BY a.continent;

-- SELECT city.CountryCode, country.Name
-- FROM country LEFT JOIN city ON country.Code = city.CountryCode


-- USE market_db;

-- DROP TABLE tb1;
-- DROP TABLE tb2;
-- CREATE TABLE tb1 (col1 INT, col2 VARCHAR(20));
-- CREATE TABLE tb2 (col1 INT, col2 VARCHAR(20));

-- INSERT INTO tb1 VALUES(1, "가"), (2, "나"), (3, "다");
-- INSERT INTO tb2 VALUES(1, "A"), (1, "B");

-- UNION 키워드만 쓰면 DISTINCT 가 기본값, ALL 은 중복도 하용함
-- UNION 으로 SELECT 묶을 시 동일한 컬럼의 갯수로 맞춰줘야 함
-- SELECT col1 FROM tb1
-- UNION ALL
-- SELECT col1 FROM tb2
-- ORDER BY 1 DESC; -- ORDER BY 는 UNION 과 조합이 안됨, 그러니 뒤에다가 하면 됨

-- USE market_db;
-- EXPLAIN
-- (SELECT col1, col2 FROM tb1 LIMIT 3) -- 또는 서브쿼리로 만들 수 있음, but 이 친구만 정열이 된다
-- UNION
-- SELECT col1, col2 FROM tb2
-- ORDER BY 1 DESC; -- using filesort 가 이거 쓰면 들어감

-- EXPLAIN -- DBMS 내부에 어떤 순서대로 실행되는지 보임
-- SELECT `CountryCode` FROM `city`
-- WHERE `CountryCode` = "KOR"
-- UNION ALL
-- SELECT `CountryCode` FROM `city`
-- WHERE `CountryCode` = "CHN";

-- EXCEPT 쿼리 1 결과값에서 쿼리 2 결과값을 빼서 리턴
-- INTERSECT 두 쿼리 결과값 중 공통값을 찾아서 리턴
-- MySQL 에서는 지원 안 해서 IN 으로 서브쿼리 해서 대채할 수 있음

-- EXPLAIN
-- SELECT DISTINCT `CountryCode` FROM `city` WHERE `Population` > 5000000 AND `CountryCode` != "CHN";

-- EXPLAIN
-- SELECT DISTINCT `CountryCode` FROM `city`
-- WHERE `Population` > 5000000 AND `CountryCode`
-- NOT IN (SELECT DISTINCT `CountryCode` FROM `city` WHERE `CountryCode` = "CHN");
-- eq_ref 가 그리 나쁘지 않은 성능이라고 함 (하나의 행 조회)

-- LIKE 검색
-- 정확한 키워드를 모를 경우 일부만으로 검색하는 방법
-- SELECT * FROM TABLE WHERE * LIKE 패턴
-- 와일드카드 % = 0-n글자, _ = 1 글자
-- LIKE 의 검색은 DBMS에 부담이 많음 => LIKE 에 OR 과 같은 논리조건자 중복 x

-- SELECT * FROM `country`
-- WHERE `LocalName` LIKE "%s" AND `GovernmentForm` LIKE "%pe%";

-- EXPLAIN
-- SELECT * FROM `country`
-- WHERE `Continent` LIKE "A___"; -- _ 중첩 가능

-- SELECT DISTINCT `CountryCode` FROM `city` WHERE `CountryCode` LIKE "%K";
-- SELECT DISTINCT `CountryCode` FROM `city` WHERE `CountryCode` LIKE "K%";
-- SELECT DISTINCT `CountryCode` FROM `city` WHERE `CountryCode` LIKE "_K_";
-- SELECT DISTINCT `CountryCode` FROM `city` WHERE `CountryCode` LIKE "K__";

-- -128 ~ 127 / 255 TINYINT: 시스템 고유 ID, 크게 용량 늘어날 가능성 없는거
-- -21 ~ 21 / 43억 INT
-- -9 ~ 9 / 9억 BIGINT

-- TEXT (문자열)
-- BLOB (Binary Large Object)
-- 오브젝트 불러와서 변환 할 떄

-- 시간 관련
-- DATETIME
-- TIMESTAMP (1970-01-01 00:00:00 이후)


-- DROP TABLE `Salary`;
DROP TABLE `BusinessCard`;

-- CREATE TABLE `BusinessCard` (
-- 	`Name` varchar(255) PRIMARY KEY,
--     `Address` varchar(255)
-- );
CREATE TABLE `BusinessCard` (
	`ID` INT,
	`Name` varchar(255),
    `Address` varchar(255),
    PRIMARY KEY(`ID`)
);

ALTER TABLE `BusinessCard` CHANGE COLUMN `ID` `ID` INT NOT NULL AUTO_INCREMENT UNIQUE;
-- AUTO_INCREMENT 는  NOT NULL,  UNIQUE 여야 함

-- CREATE TABLE `Salary` (
-- 	`BusinessCard_ID` INT,
-- 	FOREIGN KEY(`BusinessCard_ID`) REFERENCES `BusinessCard`(`ID`)
-- );

DELETE FROM `city_kor` WHERE CountryCode = CountryCode;