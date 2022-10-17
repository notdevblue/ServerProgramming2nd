const dgram = require("dgram");
const socket = dgram.createSocket("udp4");

const PORT = 48000;
const MCAST_ADDR = "230.118.165.28";
// Multicast 영역 (D 클레스): 224.0.0.0 ~ 239.255.255.255

const server = dgram.createSocket("udp4");
server.bind(PORT, () => {
    server.setBroadcast(true);
    server.setMulticastTTL(128);
    server.addMembership(MCAST_ADDR);
});

setInterval(broadcastTest, 3000);

function broadcastTest() {
    let msg = new Buffer("Install Gentoo");
    server.send(msg, 0, msg.length, PORT, MCAST_ADDR);
}

socket.on("listening", () => {
    const addr = socket.address();
    console.log(`Server listening on ${addr.address}:${addr.port}`);
});

// info: 페킷 전송된 원격에 대한 정보
socket.on("message", (msg, rinfo) => {
    console.log(`Message received: ${msg}`);

    socket.send(msg, rinfo.port, rinfo.address, () => {
        console.log(`Message has been sent to ${rinfo.address}:${rinfo.port}`);
    });
});

socket.on("close", () => {
    console.log("Close event");
});

socket.on("error", err => {
    console.error("Error on server: " + error.message);
    socket.close();
});

socket.bind(55000);