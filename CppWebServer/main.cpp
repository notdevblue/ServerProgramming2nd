#include <iostream>
#include <pistache/endpoint.h>
#include "./server/server.h"

int main()
{
    // MySQL sql("127.0.0.1", "han", "0225", "MinecraftRecipe");

    Server server(38000, Address(Ipv4::any(), 38000));
    server.serve();

    // sql.select("SELECT * FROM `Item`",
    //            [](const char *str)
    //            { printf("%s\n", str); });
    // sql.insert(
    //     "INSERT INTO `Item`(ItemName, Explanation) VALUES(\"12시간 가까이 C++ 하고 있는 고통스러운 우앱\", \"재목이 곧 내용입니다. 힘들게 더미로 넣고 있는데 이거 개 빡시네 내가 왜 C++ 로 시작했지 이거\")",
    //     [](const char *err)
    //     { puts(err); },
    //     []()
    //     { puts("Success"); });
    // sql.insert(
    //     "INSERT INTO `CreaterData`(ItemName, Name) VALUES(\"12시간 가까이 C++ 하고 있는 고통스러운 우앱\", \"우앱\")",
    //     [](const char *err)
    //     { puts(err); },
    //     []()
    //     { puts("Success"); });

    return (0);
}