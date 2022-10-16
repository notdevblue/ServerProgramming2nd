#include "./server/server.h"

int main()
{
    Server(38000, Pistache::Address(Pistache::Ipv4::any(), 38000)).serve();
    return (0);
}