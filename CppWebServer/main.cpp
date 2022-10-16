#include "./server/server.h"

int main()
{
    Server(36000, Pistache::Address(Pistache::Ipv4::any(), 36000)).serve();
    return (0);
}