#include "./server.h"
#include "../han.h"
#include <stdio.h>
#include <pistache/http.h>
#include <string>

using namespace Pistache;

Server::Server(const uint16_t &_port, const Address &_addr)
    : m_port(_port)
    , m_addr(_addr) {
    m_endpoint = new Http::Endpoint(m_addr);
    m_endpoint->init(Http::Endpoint::options().threads(1));
    m_sql = new MySQL("127.0.0.1", "han", "0225", "MinecraftRecipe");

    {
        using namespace Rest;
        Router router;

        Routes::Get(router, "/get/item/", Routes::bind(&Server::get_item, this));
        Routes::Get(router, "/get/allitem/", Routes::bind(&Server::get_all_item, this));
        Routes::Get(router, "/set/item/", Routes::bind(&Server::insert_item, this));

        m_endpoint->setHandler(router.handler());
    }
}

Server::~Server() {
    m_endpoint->shutdown();
    delete m_endpoint;
    delete m_sql;
}

void Server::serve() {
    printf("Server running on port %u\n", m_port);
    m_endpoint->serve();
}

void Server::get_item(const Rest::Request& req, Http::ResponseWriter res) {
    const Http::Uri::Query query = req.query();
    const std::string name = query.get("name").value();

    if (name.length()) {
        search_item_by_name(*m_sql, name,
                            [&res](const char *str)
                            { res.send(Http::Code::Ok, str); });
    }
    else {
        res.send(Http::Code::Bad_Request, "param missing");
    }
}

void Server::get_all_item(const Rest::Request& req, Http::ResponseWriter res) {
    get_items(*m_sql,
              [&res](const char *str)
              { res.send(Http::Code::Ok, str); });
}

void Server::insert_item(const Rest::Request& req, Http::ResponseWriter res) {
    const Http::Uri::Query query = req.query();

    if (!query.has("name") ||
        !query.has("explanation") ||
        !query.has("creatername") ||
        !query.has("tabledata")) {
        res.send(Http::Code::Bad_Request, "param missing");
        return;
    }

    const std::string item_name = query.get("name").value();
    const std::string item_explanation = query.get("explanation").value();
    const std::string creater_name = query.get("creatername").value();
    const std::string table_data = query.get("tabledata").value();

    insert_new_item(
        *m_sql, item_name, item_explanation, creater_name, table_data,
        [&res](const char *err)
        { res.send(Http::Code::Bad_Request, err); },
        [&res]()
        { res.send(Http::Code::Ok, "ok"); });
}