#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "../mysql/mysql.h"

class Server {
private:
    uint16_t m_port;
    Pistache::Address m_addr;
    MySQL *m_sql;
    Pistache::Http::Endpoint* m_endpoint;

    void get_item(const Pistache::Rest::Request &req,
                  Pistache::Http::ResponseWriter res);
                  
    void get_all_item(const Pistache::Rest::Request &req,
                      Pistache::Http::ResponseWriter res);

    void insert_item(const Pistache::Rest::Request &req,
                     Pistache::Http::ResponseWriter res);

public:
    Server(const uint16_t &_port, const Pistache::Address &_addr);
    ~Server();

    void serve();
};