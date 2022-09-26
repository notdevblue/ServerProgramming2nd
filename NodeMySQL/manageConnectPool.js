const pool = require("./connectPool.js");

pool.getConnection((err, conn) => {
    if (err) {
        console.error(err);
        return;
    }

    let sql = "SELECT a.continent, COUNT(b.id) AS CityCount FROM city AS b RIGHT JOIN country AS a ON a.Code = b.CountryCode GROUP BY a.continent;";
    conn.query(sql, (err, results) => {
        if (err) {
            console.error("sql err:", err);
            conn.release();
            return;
        }

        for (let i = 0; i < results.length; ++i) {
            let countryInfo = results[i];
            console.log(`Continent: ${countryInfo.continent} / CityCount: ${countryInfo.CityCount}`);
        }


        conn.release();
    });
});