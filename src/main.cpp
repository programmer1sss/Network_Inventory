
#include <iostream>
#include <utility>
#include <vector>
#include "Server.h"
#include "ServiceList.h"

// Допоміжна функція для гарного виводу розділювачів
void printSeparator(const std::string &title)
{
    std::cout << "\n==========================================\n";
    std::cout << " " << title << "\n";
    std::cout << "==========================================\n";
}


int main()
{
    std::cout << "ДЕМОНСТРАЦІЯ RULE OF FIVE (ServiceList)\n";

    // ────────────────────────────────────────────────────────────
    // 1. Звичайний конструктор (і неявний деструктор)
    // ────────────────────────────────────────────────────────────
    printSeparator("1. Створення об'єктів (звичайний конструктор)");
    ServiceList list1(4);
    list1.add(Service("nginx", 80, "tcp"));
    list1.add(Service("ssh", 22, "tcp"));

    ServiceList list2(2);
    list2.add(Service("dns", 53, "udp"));

    std::cout << "list1 size: " << list1.size() << "\n";
    std::cout << "list2 size: " << list2.size() << "\n";
    std::cout << "Лічильники (на початку): copies=" << ServiceList::copies()
              << ", moves=" << ServiceList::moves() << "\n";

    // ────────────────────────────────────────────────────────────
    // 2. Конструктор копіювання (Copy Constructor)
    // ────────────────────────────────────────────────────────────
    printSeparator("2. Конструктор копіювання (Copy Constructor)");
    ServiceList copyList = list1; // викликається ServiceList(const ServiceList&)

    std::cout << "copyList size: " << copyList.size() << "\n";
    std::cout << "Лічильники: copies=" << ServiceList::copies()
              << ", moves=" << ServiceList::moves() << "\n";

    // Демонстрація незалежності копій
    list1.add(Service("httpd", 8080, "tcp"));
    std::cout << "Після зміни оригіналу:\n";
    std::cout << "  list1 size: " << list1.size() << "\n";
    std::cout << "  copyList size: " << copyList.size() << " (не змінився)\n";

    // ────────────────────────────────────────────────────────────
    // 3. Оператор присвоєння копіюванням (Copy Assignment)
    // ────────────────────────────────────────────────────────────
    printSeparator("3. Присвоєння копіюванням (Copy Assignment)");
    std::cout << "list2 (до присвоєння) size: " << list2.size() << "\n";

    list2 = list1; // викликається ServiceList& operator=(const ServiceList&)

    std::cout << "list2 (після присвоєння) size: " << list2.size() << "\n";
    std::cout << "Лічильники: copies=" << ServiceList::copies()
              << ", moves=" << ServiceList::moves() << "\n";

    // ────────────────────────────────────────────────────────────
    // 4. Конструктор переміщення (Move Constructor)
    // ────────────────────────────────────────────────────────────
    printSeparator("4. Конструктор переміщення (Move Constructor)");
    ServiceList movedList = std::move(copyList); // викликається ServiceList(ServiceList&&)

    std::cout << "movedList size: " << movedList.size() << "\n";
    std::cout << "copyList (після переміщення) size: " << copyList.size() << " (має бути 0)\n";
    std::cout << "Лічильники: copies=" << ServiceList::copies()
              << ", moves=" << ServiceList::moves() << "\n";

    // ────────────────────────────────────────────────────────────
    // 5. Оператор присвоєння переміщенням (Move Assignment)
    // ────────────────────────────────────────────────────────────
    printSeparator("5. Присвоєння переміщенням (Move Assignment)");

    ServiceList targetList(5);
    targetList.add(Service("old-service", 9999, "tcp"));
    std::cout << "targetList (до) size: " << targetList.size() << "\n";

    targetList = std::move(movedList); // викликається ServiceList& operator=(ServiceList&&)

    std::cout << "targetList (після) size: " << targetList.size() << "\n";
    std::cout << "movedList (після переміщення) size: " << movedList.size() << " (має бути 0)\n";
    std::cout << "Лічильники: copies=" << ServiceList::copies()
              << ", moves=" << ServiceList::moves() << "\n";

    // ────────────────────────────────────────────────────────────
    // 6. Демонстрація роботи Server (вбудований клас)
    // ────────────────────────────────────────────────────────────
    printSeparator("6. Вбудований клас Server (Rule of Zero)");
    Server myServer("web-01");
    myServer.addService(Service("nginx", 80, "tcp"));
    myServer.addService(Service("ssh", 22, "tcp"));

    std::cout << "Сервер: " << myServer.hostname() << "\n";
    std::cout << "Кількість сервісів: " << myServer.serviceCount() << "\n";
    for (std::size_t i = 0; i < myServer.serviceCount(); ++i)
    {
        const auto &s = myServer.service(i);
        std::cout << "  - " << s.name << " (port " << s.port << "/" << s.protocol << ")\n";
    }

    // Копіювання сервера
    Server copiedServer = myServer;
    std::cout << "Скопійовано сервер: " << copiedServer.hostname()
              << " (сервісів: " << copiedServer.serviceCount() << ")\n";

    // Переміщення сервера
    Server movedServer = std::move(myServer);
    std::cout << "Переміщено сервер: " << movedServer.hostname()
              << " (сервісів: " << movedServer.serviceCount() << ")\n";

    printSeparator("ДЕМОНСТРАЦІЯ ЗАВЕРШЕНА");
    return 0;
}