#include <iostream>
#include <pistache/endpoint.h>
#include "./Query/query.h"

class HelloHandler : public Pistache::Http::Handler {
public:
    HTTP_PROTOTYPE(HelloHandler);

    void onRequest(const Pistache::Http::Request& request,
                   Pistache::Http::ResponseWriter response) {
        response.send(Pistache::Http::Code::Ok, "Install Gentoo\nAnd Keep C++\n");
    }
};

int main()
{
    // const uint16_t PORT = 36000;
    // const Address ADDR(Ipv4::any(), Port(PORT));
    const char *DB_ADDR = "localhost";
    const char *DB_ID = "han";
    const char *DB_PW = "0225";

    // auto OPTIONS = Http::Endpoint::options().threads(1);
    // Http::Endpoint server(ADDR);
    // server.init(OPTIONS);
    // server.setHandler(Http::make_handler<HelloHandler>());
    // server.serve();

    // std::cout << "Server running on port: " << PORT << std::endl;
    std::cout << "MySQL client version: " << mysql_get_client_info();

    MYSQL *con = mysql_init(NULL);
    if (con == nullptr) {
        std::cerr << mysql_error(con) << std::endl;
        return (1);
    }

    if (mysql_real_connect(con, DB_ADDR, DB_ID, DB_PW,
                           NULL, 0, NULL, 0) == NULL) {
        std::cerr << mysql_error(con) << std::endl;
    }

    

    mysql_close(con);
    return (0);
}