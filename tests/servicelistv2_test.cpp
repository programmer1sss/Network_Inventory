#include <gtest/gtest.h>
#include <utility>
#include "ServiceListV2.h"

TEST(ServiceListV2Test, DeepCopy) {
    ServiceListV2 a;
    a.add(Service("nginx", 80, "tcp"));
    a.add(Service("ssh", 22, "tcp"));
    ServiceListV2 b = a;
    ASSERT_EQ(b.size(), 2u);
    EXPECT_EQ(b.at(0), Service("nginx", 80, "tcp"));
}

TEST(ServiceListV2Test, CopiesAreIndependent) {
    ServiceListV2 a;
    a.add(Service("nginx", 80, "tcp"));
    ServiceListV2 b = a;
    a.add(Service("httpd", 8080, "tcp"));
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 1u);
}

TEST(ServiceListV2Test, CopyAssignment) {
    ServiceListV2 a;
    a.add(Service("nginx", 80, "tcp"));
    ServiceListV2 b;
    b.add(Service("ssh", 22, "tcp"));
    b = a;
    ASSERT_EQ(b.size(), 1u);
    EXPECT_EQ(b.at(0), Service("nginx", 80, "tcp"));
}

TEST(ServiceListV2Test, SelfAssignment) {
    ServiceListV2 a;
    a.add(Service("nginx", 80, "tcp"));
    ServiceListV2& alias = a;
    a = alias;
    EXPECT_EQ(a.size(), 1u);
}

TEST(ServiceListV2Test, MoveConstructor) {
    ServiceListV2 a;
    a.add(Service("nginx", 80, "tcp"));
    ServiceListV2 b = std::move(a);
    EXPECT_EQ(b.size(), 1u);
    EXPECT_EQ(a.size(), 0u);
}

TEST(ServiceListV2Test, MoveAssignment) {
    ServiceListV2 a;
    a.add(Service("nginx", 80, "tcp"));
    ServiceListV2 b;
    b.add(Service("old", 1, "tcp"));
    b = std::move(a);
    EXPECT_EQ(b.size(), 1u);
    EXPECT_EQ(a.size(), 0u);
}