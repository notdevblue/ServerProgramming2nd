#include "./server.h"
#include <stdio.h>
#include <pistache/http.h>
#include <string>

Server::Server(const uint16_t &_port, const Address &_addr)
    : m_port(_port)
    , m_addr(_addr) {
    m_endpoint = new Http::Endpoint(m_addr);
    m_endpoint->init(Http::Endpoint::options().threads(1));
    m_sql = new MySQL("127.0.0.1", "han", "0225", "MinecraftRecipe");

    // using namespace Rest;
    {
        using namespace Rest;
        Router router;

        Routes::Get(router, "/get/byitemname/", Routes::bind(&Server::get_item_by_name, this));

        m_endpoint->setHandler(router.handler());
    }
}

Server::~Server() {
    delete m_endpoint;
    delete m_sql;
}

void Server::serve() {
    printf("Server running on port %ud", m_port);
    m_endpoint->serve();
}

// query 스트링 잘 작동함.
// TODO: query 스트링으로 아이템 검색 기능
void Server::get_item_by_name(const Rest::Request& req, Http::ResponseWriter res) {
    Http::Uri::Query query = req.query();
    std::string name = query.get("name").value();

    m_sql->select(
        get_item_by_name_query(name).c_str(),
        [&res, &name](const char *str)
        { res.send(Http::Code::Ok, name); });
}