#include <gtest/gtest.h>
#include <utility>
#include "Server.h"

// Server вбудовує ServiceList. Перевіряємо, що копіювання Server
// робить глибоку копію сервісів, а зміна оригіналу не впливає на копію.
TEST(ServerTest, DeepCopyOfServer) {
    Server a("web-01");
    a.addService(Service("nginx", 80, "tcp"));
    a.addService(Service("ssh", 22, "tcp"));

    Server b = a;

    ASSERT_EQ(b.hostname(), "web-01");
    ASSERT_EQ(b.serviceCount(), 2u);
    EXPECT_EQ(b.service(0), Service("nginx", 80, "tcp"));

    // Змінюємо оригінал — копія не повинна змінитися
    a.addService(Service("httpd", 8080, "tcp"));

    EXPECT_EQ(a.serviceCount(), 3u);
    EXPECT_EQ(b.serviceCount(), 2u);
}

TEST(ServerTest, MoveOfServer) {
    Server a("web-01");
    a.addService(Service("nginx", 80, "tcp"));

    Server b = std::move(a);

    EXPECT_EQ(b.hostname(), "web-01");
    EXPECT_EQ(b.serviceCount(), 1u);
}