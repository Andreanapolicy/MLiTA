/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 10.5
 * ===============================================================
 * Задана неубывающая последовательность целых чисел. Найти
 * количество пар чисел с заданной разностью D.
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Linux, Ubuntu 20.04
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <fstream>
#include <iostream>
#include <vector>

void initFiles(std::ifstream& input, std::ofstream& output);
void fillSequence(std::istream& input, std::vector<int>& sequence);
int countPairWithDifference(const std::vector<int>& sequence, int difference);
int getValue(int firstValue, int secondValue, int tempValue, const std::vector<int>& sequence);

int main()
{
    std::ifstream input;
    std::ofstream output;

    try
    {
        int size = 0;
        int difference = 0;
        initFiles(input, output);

        input >> size >> difference;
        if (size < 2 || size > 1000000)
        {
            throw std::invalid_argument("Error, size should be in range 2 .. 1000000");
        }

        if (difference < 1 || difference > 1000000000)
        {
            throw std::invalid_argument("Error, difference should be in range 1 .. 1000000000");
        }
        std::vector<int> sequence(size);

        fillSequence(input, sequence);
        output << countPairWithDifference(sequence, difference) << std::endl;
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

void fillSequence(std::istream& input, std::vector<int>& sequence)
{
    for (auto index = 0; index < sequence.size(); index++)
    {
        input >> sequence[index];
    }
}

int countPairWithDifference(const std::vector<int>& sequence, int difference)
{
    int counter = 0;
    int supportCounter;

    for (auto index = 0; index < sequence.size() - 1; index++)
    {
        int tempValue = sequence[index] + difference;

        if (tempValue > sequence[sequence.size() - 1])
        {
            break;
        }

        int identifiedValue = getValue(index + 1, sequence.size() - 1, tempValue, sequence);
        if (identifiedValue == -1)
        {
            continue;
        }

        counter++;
        supportCounter = identifiedValue + 1;
        while(supportCounter < sequence.size() && sequence[supportCounter] == tempValue)
        {
            supportCounter++;
            counter++;
        }

        supportCounter = identifiedValue - 1;
        while(sequence[supportCounter] == tempValue)
        {
            supportCounter--;
            counter++;
        }
    }

    return counter;
}

int getValue(int firstValue, int secondValue, int tempValue, const std::vector<int>& sequence)
{
    if (secondValue - firstValue < 2)
    {
        return sequence[firstValue] == tempValue ? firstValue : (sequence[secondValue] == tempValue ? secondValue : -1);
    }

    if (sequence[(secondValue + firstValue) / 2] > tempValue)
    {
        return getValue(firstValue, (secondValue + firstValue) / 2, tempValue, sequence);
    }

    return getValue((secondValue + firstValue) / 2, secondValue, tempValue, sequence);
}
