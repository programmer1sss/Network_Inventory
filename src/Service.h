#pragma once

#include <string>
#include <utility>

// Елемент масиву — проста структура з кількох полів.
// Rule of Zero: жодного сирого ресурсу, усі поля керуються std::string.
// Компілятор генерує коректні копіювання/переміщення.
struct Service {
    std::string name;      // напр. "nginx"
    int         port = 0;  // напр. 80
    std::string protocol;  // "tcp" / "udp"

    Service() = default;

    Service(std::string n, int p, std::string proto)
        : name(std::move(n)), port(p), protocol(std::move(proto)) {}

    bool operator==(const Service& other) const {
        return name == other.name
            && port == other.port
            && protocol == other.protocol;
    }
};