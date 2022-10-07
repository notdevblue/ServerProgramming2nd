#include <iostream>
#include <pistache/endpoint.h>

using namespace Pistache;
using namespace std;

class HelloHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(HelloHandler);

    void onRequest(const  Http::Request& request, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "Install Gentoo\nAnd Keep C++\n");
    }
};

int main()
{
    Address addr(Ipv4::any(), Port(36000));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<HelloHandler>());
    server.serve();

    // Http::listenAndServe<HelloHandler>("*:38000");

    return (0);
}