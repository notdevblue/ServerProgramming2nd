const pool = require("./connectPool.js");

pool.getConnection((err, conn) => {
    if (err) {
        console.error(err);
        return;
    }

    // let sql4 = "DELETE FROM `city` WHERE ID = 20000;";
    // conn.query(sql4, (err, results) => {
    //     if (err) {
    //         console.error("sql4 err:", err);
    //         return;
    //     } else {
    //         console.log(results.affectedRows);
    //     }
    // });
    let input = "AGO";
    let sql = "SELECT * FROM `country` WHERE `Code`=" + conn.escape(input);
    conn.query(sql, (err, results) => {
        if (err) {
            console.error("sql err:", err);
            // conn.rollback();
            return;
        } else {
            console.log(results);
        }
    });

    // let sql3 = "DELETE FROM `city_kor`;";
    // conn.query(sql3, (err, results) => {
    //     if (err) {
    //         console.error("sql3 err:", err);
    //         return;
    //     } else {
    //         console.log(results.affectedRows);
    //     }
    // });

    // let sql2 = "INSERT INTO `city_kor` SELECT * FROM `city` WHERE `CountryCode`=\"KOR\";";
    // conn.query(sql2, (err, results) => {
    //     if (err) {
    //         console.error("sql2 err:", err);
    //         return;
    //     } else {
    //         console.log(results.insertId);
    //     }
    // });

    conn.release();
});
// affectedRows: 영향을 받은 열의 갯수
// insertID: 새로 추가한 경우 PK
// changedRow: 변경된 열의 수