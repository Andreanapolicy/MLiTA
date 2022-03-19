#pragma once
#include <string>
#include <vector>

class Number
{
public:
    Number() = default;
    explicit Number(const std::string& number);

    bool IsNegative() const;

    size_t Size() const;

    friend Number operator+(const Number& first, const Number& second);

private:
    std::vector<int> m_container;
    bool m_isNegative = false;
};