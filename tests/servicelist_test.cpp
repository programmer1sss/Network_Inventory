#include <gtest/gtest.h>
#include <utility>
#include "ServiceList.h"

// 1. Глибока копія
TEST(ServiceListTest, DeepCopy) {
    ServiceList a(4);
    a.add(Service("nginx", 80, "tcp"));
    a.add(Service("ssh", 22, "tcp"));

    ServiceList b = a;

    ASSERT_EQ(b.size(), 2u);
    EXPECT_EQ(b.at(0), Service("nginx", 80, "tcp"));
    EXPECT_EQ(b.at(1), Service("ssh", 22, "tcp"));
}

// 2. Незалежність копій
TEST(ServiceListTest, CopiesAreIndependent) {
    ServiceList a(4);
    a.add(Service("nginx", 80, "tcp"));
    ServiceList b = a;

    a.add(Service("httpd", 8080, "tcp"));

    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 1u);
    EXPECT_EQ(b.at(0).name, "nginx");
}

// 3. Присвоєння копіюванням
TEST(ServiceListTest, CopyAssignment) {
    ServiceList a(4);
    a.add(Service("nginx", 80, "tcp"));

    ServiceList b(4);
    b.add(Service("ssh", 22, "tcp"));
    b.add(Service("dns", 53, "udp"));

    b = a;

    ASSERT_EQ(b.size(), 1u);
    EXPECT_EQ(b.at(0), Service("nginx", 80, "tcp"));
    EXPECT_EQ(a.size(), 1u);
}

// 4. Самоприсвоєння (через аліас, щоб уникнути -Wself-assign)
TEST(ServiceListTest, SelfAssignment) {
    ServiceList a(4);
    a.add(Service("nginx", 80, "tcp"));
    a.add(Service("ssh", 22, "tcp"));

    ServiceList& alias = a;
    a = alias;

    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(a.at(0).name, "nginx");
    EXPECT_EQ(a.at(1).name, "ssh");
}

// 5. Переміщення з обнуленням джерела
TEST(ServiceListTest, MoveConstructor) {
    ServiceList a(4);
    a.add(Service("nginx", 80, "tcp"));
    a.add(Service("ssh", 22, "tcp"));

    ServiceList b = std::move(a);

    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.at(0).name, "nginx");
    EXPECT_EQ(a.size(), 0u);
}

// 6. Присвоєння переміщенням
TEST(ServiceListTest, MoveAssignment) {
    ServiceList a(4);
    a.add(Service("nginx", 80, "tcp"));
    a.add(Service("ssh", 22, "tcp"));

    ServiceList b(4);
    b.add(Service("old", 1, "tcp"));

    b = std::move(a);

    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.at(0).name, "nginx");
    EXPECT_EQ(a.size(), 0u);
}

// 7. Перевірка меж
TEST(ServiceListTest, AtThrowsOnOutOfRange) {
    ServiceList a(2);
    a.add(Service("nginx", 80, "tcp"));

    EXPECT_THROW(a.at(1), std::out_of_range);
    EXPECT_THROW(a.at(100), std::out_of_range);
}