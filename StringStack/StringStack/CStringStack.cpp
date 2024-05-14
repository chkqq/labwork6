#include "cstringstack.h"

CStringStack::CStringStack() : data(new std::string[2]), capacity(2), size(0) {}

CStringStack::~CStringStack() noexcept
{
    delete[] data;
}

CStringStack::CStringStack(const CStringStack& other)
    : data(new std::string[other.capacity]), capacity(other.capacity), size(other.size) 
{
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }
}

CStringStack::CStringStack(CStringStack&& other) noexcept
    : data(other.data), capacity(other.capacity), size(other.size)
{
    other.data = nullptr;
    other.capacity = 0;
    other.size = 0;
}

CStringStack& CStringStack::operator=(const CStringStack& other)
{
    if (this != &other) 
    {
        CStringStack temp(other);
        std::swap(data, temp.data);
        std::swap(capacity, temp.capacity);
        std::swap(size, temp.size);
    }
    return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& other) noexcept
{
    if (this != &other)
    {
        delete[] data;
        data = other.data;
        capacity = other.capacity;
        size = other.size;
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

void CStringStack::push(const std::string& str)
{
    if (size == capacity)
    {
        resize(capacity * 2);
    }
    data[size] = str;
    ++size;
}

void CStringStack::push(std::string&& str) 
{
    if (size == capacity) 
    {
        resize(capacity * 2);
    }
    data[size] = std::move(str);
    ++size;
}

void CStringStack::pop()
{
    if (size == 0) 
    {
        throw std::out_of_range("Stack underflow: trying to pop from empty stack");
    }
    data[size - 1].clear();
    --size;
}

const std::string& CStringStack::top() const 
{
    if (size == 0) 
    {
        throw std::out_of_range("Stack is empty: trying to access top of empty stack");
    }
    return data[size - 1];
}

bool CStringStack::is_empty() const
{
    return size == 0;
}

void CStringStack::resize(size_t new_capacity)
{
    std::string* new_data = new std::string[new_capacity];
    for (size_t i = 0; i < size; ++i)
    {
        new_data[i] = std::move(data[i]);
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}
