/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 5.3
 * ===============================================================
 * Найти суммарное число цифр во всех целых числах от M до N
 * включительно.
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Linux, Ubuntu 20.04
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <fstream>
#include <iostream>
#include <cmath>

void initFiles(std::ifstream& input, std::ofstream& output);
long long countDigitInRange(const std::string& firstLine, const std::string& secondLine);

int main()
{
    std::ifstream input;
    std::ofstream output;

    try
    {
        std::string firstLine;
        std::string secondLine;
        initFiles(input, output);

        input >> firstLine >> secondLine;
        if (firstLine.empty() || firstLine.size() > 16 || secondLine.empty() || secondLine.size() > 16)
        {
            throw std::invalid_argument("Error, numbers should be in range 2 .. 1 000 000 000 000 000");
        }

        output << countDigitInRange(firstLine, secondLine) << std::endl;
        if (!output.flush())
        {
            throw std::runtime_error("Error, can't flush output");
        }

        output.close();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return 1;
    }

    return 0;
}

void initFiles(std::ifstream& input, std::ofstream& output)
{
    const std::string INPUT_FILE_NAME = "INPUT.TXT";
    const std::string OUTPUT_FILE_NAME = "OUTPUT.txt";

    input.open(INPUT_FILE_NAME, std::ios_base::in);
    output.open(OUTPUT_FILE_NAME, std::ios_base::out);
    if (!input.is_open())
    {
        throw std::invalid_argument("Error, can't open INPUT.TXT");
    }

    if (!output.is_open())
    {
        throw std::invalid_argument("Error, can't open OUTPUT.TXT");
    }
}

long long countDigitInRange(const std::string& firstLine, const std::string& secondLine)
{
    auto firstNumberSize = firstLine.size();
    auto secondNumberSize = secondLine.size();
    long long firstNumber = std::stoll(firstLine);
    long long secondNumber = std::stoll(secondLine);
    long long result = 0;

    if (firstNumberSize == secondNumberSize)
    {
        return (secondNumber - firstNumber + 1) * firstNumberSize;
    }

    for (auto index = firstNumberSize; index <= secondNumberSize; index++)
    {
        if (index != secondNumberSize)
        {
            if (index == firstNumberSize)
            {
                result = (std::pow(10, index) - firstNumber) * index;
            }
            else
            {
                result += (std::pow(10, index) - std::pow(10, index - 1)) * index;
            }
        }
        else
        {
            result += (secondNumber - std::pow(10, index - 1) + 1) * index;
        }
    }

    return result;
}
