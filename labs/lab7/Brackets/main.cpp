/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 7.2
 * ===============================================================
 * Последовательность круглых скобок называют правильной,
 * если можно добавить в нее числа и знаки арифметических
 * операций так, что полученное алгебраическое выражение станет
 * корректным. Например, скобочная последовательность (())()
 * является правильной, а (())) и ())(() такими не являются.
 * Пустая последовательность также считается правильной.
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Linux, Ubuntu 20.04
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <fstream>
#include <iostream>
#include <vector>

void InitFiles(std::ifstream& input, std::ofstream& output);
void FillBrackets(std::istream& input, std::vector<int>& brackets);
int countOfExternalBrackets(std::vector<int>& brackets);

int main()
{
    std::ifstream input;
    std::ofstream output;

    try
    {
        int size;
        InitFiles(input, output);
        input >> size;
        std::vector<int> brackets(size * 2, 0);
        FillBrackets(input, brackets);
        output << countOfExternalBrackets(brackets) << std::endl;
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

void InitFiles(std::ifstream& input, std::ofstream& output)
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

void FillBrackets(std::istream& input, std::vector<int>& brackets)
{
    char symbol;
    int bracketsNestingCounter = 0;

    for (auto index = 0; index < brackets.size(); index++)
    {
        input >> symbol;
        if (symbol == '(')
        {
            bracketsNestingCounter++;
        }
        else
        {
            bracketsNestingCounter--;
        }
        brackets[index] = bracketsNestingCounter;
    }
}

int countOfExternalBrackets(std::vector<int>& brackets)
{
    std::vector<int> countOfRepeatedExternalBrackets(brackets.size() / 2, 0);

    for (auto index = 0; index < brackets.size(); index++)
    {
        countOfRepeatedExternalBrackets[brackets[index]]++;
    }

    for (auto index = 0; index < countOfRepeatedExternalBrackets.size(); index++)
    {
        if (countOfRepeatedExternalBrackets[index] > 2 || (index == 0 && countOfRepeatedExternalBrackets[index] > 1))
        {
            return index;
        }
    }

    return countOfRepeatedExternalBrackets.size();
}
