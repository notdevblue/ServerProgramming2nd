const mysql = require("mysql");
const dbConf = require("./secret.js");

const con = mysql.createConnection(dbConf);
con.connect(err => {
    if (err) {
        console.error(err);
        return;
    }
    console.log("connection id: " + con.threadId);

    con.end(err => {
        if (err) {
            console.error(err);
            return;
        }
    });
});

con.query("SELECT DISTINCT `CountryCode` FROM `city` WHERE `Population` > 5000000 AND `CountryCode` != \"CHN\";", (err, rows, fields) => {
    if (err) {
        throw err;
    }

    console.log("City info: ", rows);
});