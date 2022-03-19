/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 6.1
 * ===============================================================
 * Номера автобусных билетов состоят из 2N цифр, включая
 * незначащие нули (1 ≤ N ≤ 500). Минимальный возможный номер
 * состоит из 2N нулей, а максимальный – из 2N девяток. Студент
 * Вася ездит в университет на автобусе и коллекционирует
 * счастливые билеты, в которых сумма первых N цифр совпадает с
 * суммой последних N цифр. Как и всякий настоящий коллекционер,
 * Вася готов пойти на все для пополнения своей коллекции. Вместе
 * с тем ему пока приходится учитывать свои финансовые
 * возможности. Каждый раз после приобретения билета Вася
 * определяет, какое минимальное количество билетов нужно купить
 * еще, чтобы среди них обязательно оказался счастливый билет.
 * Если у него оказывается достаточно денег, он тут же покупает
 * необходимое число билетов. Иногда он не успевает закончить
 * расчеты, проезжает свою остановку и опаздывает на занятия.
 * Помогите Васе.
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Linux, Ubuntu 20.04
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <fstream>
#include <iostream>
#include <vector>
#include "src/Number/Number.h"

void initFiles(std::ifstream& input, std::ofstream& output);
Number countOfStepsToClosestLuckyNumber(const Number& number);

int main()
{
    std::ifstream input;
    std::ofstream output;

    try
    {
        int size = 0;
        std::string numberLine;
        initFiles(input, output);

        input >> size >> numberLine;
        if (size < 1 || size > 500)
        {
            throw std::invalid_argument("Error, size should be in range 1 .. 500");
        }

        if (numberLine.empty() || numberLine.size() > 500)
        {
            throw std::invalid_argument("Error, size should be in range 1 .. 500");
        }

        Number number(numberLine);
        output << countOfStepsToClosestLuckyNumber(number);
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

Number countOfStepsToClosestLuckyNumber(const Number& number)
{

    return Number();
}
