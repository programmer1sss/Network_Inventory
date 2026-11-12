#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>
#include "Service.h"

// Версія за правилом нуля: жодного спеціального члена.
class ServiceListV2 {
public:
    void add(Service s) { items_.push_back(std::move(s)); }

    Service& at(std::size_t i) {
        if (i >= items_.size())
            throw std::out_of_range("ServiceListV2::at: index out of range");
        return items_[i];
    }
    const Service& at(std::size_t i) const {
        if (i >= items_.size())
            throw std::out_of_range("ServiceListV2::at: index out of range");
        return items_[i];
    }

    std::size_t size() const { return items_.size(); }

private:
    std::vector<Service> items_;
};