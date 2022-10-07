// 소켓 통신을 위한 기본 모듈
const net = require("net");

const server = net.createServer(socket => {
    console.log("Client joined");
    socket.write("Welcome to socket server");

    socket.on("data", chunk => {
        console.log("Client: ", chunk.toString());
    });
});

server.on("listening", () => {
    console.log("Server is listening");
});

server.on("close", () => { // Client 의 end 와 같이 호출됨
    console.log("Server closed");
});

server.listen(36000);