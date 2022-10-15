#include <iostream>
#include <pistache/endpoint.h>
#include "./mysql/mysql.h"

// class HelloHandler : public Pistache::Http::Handler {
// public:
//     HTTP_PROTOTYPE(HelloHandler);

//     void onRequest(const Pistache::Http::Request& request,
//                    Pistache::Http::ResponseWriter response) {
//         response.send(Pistache::Http::Code::Ok, "Install Gentoo\nAnd Keep C++\n");
//     }
// };

int main()
{
    // const uint16_t PORT = 36000;
    // const Address ADDR(Ipv4::any(), Port(PORT));

    // auto OPTIONS = Http::Endpoint::options().threads(1);
    // Http::Endpoint server(ADDR);
    // server.init(OPTIONS);
    // server.setHandler(Http::make_handler<HelloHandler>());
    // server.serve();

    // std::cout << "Server running on port: " << PORT << std::endl;

    MySQL sql("127.0.0.1", "han", "0225", "MinecraftRecipe");
    sql.select("SELECT * FROM `Item`", [](const char *str)
               { printf("%s\n", str); });

    return (0);
}