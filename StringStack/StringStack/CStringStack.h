#include <iostream>
#include <stdexcept>
#include <string>

class CStringStack 
{
private:
    std::string* data;
    size_t capacity;
    size_t size;

    void resize(size_t new_capacity);

public:
    CStringStack();
    ~CStringStack() noexcept;
    CStringStack(const CStringStack& other);
    CStringStack(CStringStack&& other) noexcept;

    CStringStack& operator=(const CStringStack& other);
    CStringStack& operator=(CStringStack&& other) noexcept;

    void push(const std::string& str);
    void push(std::string&& str);
    void pop();

    const std::string& top() const;
    bool is_empty() const;
};
