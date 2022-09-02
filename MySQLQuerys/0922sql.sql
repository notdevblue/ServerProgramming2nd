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
SELECT CountryCode, Population FROM city ORDER BY CountryCode, Population DESC;