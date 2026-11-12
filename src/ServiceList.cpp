#include "ServiceList.h"

#include <stdexcept>
#include <utility>

std::size_t ServiceList::copies_ = 0;
std::size_t ServiceList::moves_ = 0;

// ── Звичайний конструктор з виділенням пам'яті ──
ServiceList::ServiceList(std::size_t capacity)
    : items_(capacity > 0 ? new Service[capacity] : nullptr),
      size_(0),
      capacity_(capacity)
{
}

// ── Деструктор ──
ServiceList::~ServiceList()
{
    delete[] items_;
}

// ── Конструктор копіювання (глибока копія) ──
ServiceList::ServiceList(const ServiceList &other)
    : items_(other.capacity_ > 0 ? new Service[other.capacity_] : nullptr),
      size_(other.size_),
      capacity_(other.capacity_)
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        items_[i] = other.items_[i];
    }
    ++copies_;
}

// ── Присвоєння копіюванням ──
ServiceList &ServiceList::operator=(const ServiceList &other)
{
    if (this == &other)
        return *this;

    // strong exception guarantee: спочатку виділяємо, потім звільняємо старий
    Service *newItems = (other.capacity_ > 0)
                            ? new Service[other.capacity_]
                            : nullptr;
    for (std::size_t i = 0; i < other.size_; ++i)
    {
        newItems[i] = other.items_[i];
    }

    delete[] items_;
    items_ = newItems;
    size_ = other.size_;
    capacity_ = other.capacity_;

    ++copies_;
    return *this;
}

// ── Конструктор переміщення ──
ServiceList::ServiceList(ServiceList &&other) noexcept
    : items_(other.items_),
      size_(other.size_),
      capacity_(other.capacity_)
{
    other.items_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    ++moves_;
}

// ── Присвоєння переміщенням ──
ServiceList &ServiceList::operator=(ServiceList &&other) noexcept
{
    if (this != &other)
    {
        delete[] items_;
        items_ = other.items_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.items_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        ++moves_;
    }
    return *this;
}

// ── Вільна swap ──
void swap(ServiceList &a, ServiceList &b) noexcept
{
    using std::swap;
    swap(a.items_, b.items_);
    swap(a.size_, b.size_);
    swap(a.capacity_, b.capacity_);
}

// ── Додавання елемента ──
void ServiceList::add(Service s)
{
    if (size_ >= capacity_)
        throw std::out_of_range("ServiceList: capacity exceeded");
    items_[size_] = std::move(s);
    ++size_;
}

// ── Доступ за індексом із перевіркою межі ──
Service &ServiceList::at(std::size_t i)
{
    if (i >= size_)
        throw std::out_of_range("ServiceList::at: index out of range");
    return items_[i];
}

const Service &ServiceList::at(std::size_t i) const
{
    if (i >= size_)
        throw std::out_of_range("ServiceList::at: index out of range");
    return items_[i];
}
