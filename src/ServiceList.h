#pragma once

#include <cstddef>
#include <string>
#include "Service.h"

// Клас-власник динамічного масиву Service з ручним керуванням пам'яттю.
// Реалізує Rule of Five (правило п'яти).
class ServiceList {
public:
    // ── Конструктори та деструктор ──
    ServiceList() = default;
    explicit ServiceList(std::size_t capacity);
    ~ServiceList();

    // ── Копіювання ──
    ServiceList(const ServiceList& other);
    ServiceList& operator=(const ServiceList& other);

    // ── Переміщення ──
    ServiceList(ServiceList&& other) noexcept;
    ServiceList& operator=(ServiceList&& other) noexcept;

    // ── Методи предметної області ──
    void add(Service s);                       // додає елемент
    Service&       at(std::size_t i);          // доступ з перевіркою межі
    const Service& at(std::size_t i) const;

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }

    // ── Лічильники ──
    static std::size_t copies() { return copies_; }
    static std::size_t moves()  { return moves_; }
    static void resetCounters() { copies_ = 0; moves_ = 0; }

private:
    Service*     items_    = nullptr;   // сирий масив
    std::size_t  size_     = 0;
    std::size_t  capacity_ = 0;

    static std::size_t copies_;
    static std::size_t moves_;

    friend void swap(ServiceList& a, ServiceList& b) noexcept;
};
