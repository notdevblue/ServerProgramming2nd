const mysql = require("mysql");
const dbConf = require("./secret.js");
dbConf.connectionLimit = 50;
dbConf.queueLimit = 5;
dbConf.acquireTimeout = 10;
dbConf.waitForConnections = true; // false , false 라면 queueLimit 크기 상관없이 요청 안 받음

const pool = mysql.createPool(dbConf);

module.exports = pool;