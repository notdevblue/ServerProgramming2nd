#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "../mysql/mysql.h"
#include "../han.h"

using namespace Pistache;



class Server {
private:
    uint16_t m_port;
    Address m_addr;
    MySQL *m_sql;
    Http::Endpoint* m_endpoint;

    void get_item_by_name(const Rest::Request& req, Http::ResponseWriter res);

public:
    Server(const uint16_t &_port, const Address &_addr);
    ~Server();

    void serve();
};