const dgram = require("dgram");
const socket = dgram.createSocket("udp4");

let msg = new Buffer("Install Gentoo UDP Receiver");


// socket.send(msg, 55000, "localhost")
socket.send(msg, 0, msg.length, 55000, "127.0.0.1", (err) => {
    if (err) {
        console.error("UDP Send error", err);
        return;
    }

    console.log("Success");
    socket.close();
});