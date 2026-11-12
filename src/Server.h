#pragma once

#include <string>
#include "ServiceList.h"

// Головний клас предметної області. Вбудовує клас-власник ServiceList.
// Rule of Zero для Server: жодних спеціальних членів не оголошуємо —
// компілятор згенерує їх коректно, бо ServiceList їх має.
class Server {
public:
    Server() = default;
    explicit Server(std::string hostname)
        : hostname_(std::move(hostname)) {}

    const std::string& hostname() const { return hostname_; }
    void setHostname(std::string h) { hostname_ = std::move(h); }

    void addService(Service s) { services_.add(std::move(s)); }

    std::size_t serviceCount() const { return services_.size(); }
    Service&       service(std::size_t i)       { return services_.at(i); }
    const Service& service(std::size_t i) const { return services_.at(i); }

    ServiceList&       services()       { return services_; }
    const ServiceList& services() const { return services_; }

private:
    std::string hostname_ = "(unnamed)";
    ServiceList services_{8};   // вбудований клас-власник
};