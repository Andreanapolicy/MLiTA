#include "Number.h"

Number::Number(const std::string& number)
{
    if (number.empty())
    {
        return;
    }

    if (number[0] == '-')
    {
        m_isNegative = true;
    }

    for (auto index = 0; index < number.size(); index++)
    {
        m_container.push_back(number[index]);
    }
}

bool Number::IsNegative() const
{
    return m_isNegative;
}

size_t Number::Size() const
{
    return m_container.size();
}
