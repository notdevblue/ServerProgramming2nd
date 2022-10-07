const net = require("net");

const ip = "127.0.0.1";
const port = 36000;

const socket = new net.Socket();

socket.connect({
    host: ip,
    port: port
}, () => {
    console.log("Connected with server");
    socket.write("Install Gentoo\n");

    socket.on("data", chunk => { // 데이터 도착시 호출됨
        console.log("Server: ", chunk.toString());
    });

    socket.on("end", () => { // Remote 가 close
        console.log("Connection closed");
    });
});