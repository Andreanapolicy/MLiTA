/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 10.5
 * ===============================================================
 * Задана неубывающая последовательность целых чисел. Найти
 * количество пар чисел с заданной разностью D.
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Windows 10
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <fstream>
#include <iostream>
#include <vector>

void initFiles(std::ifstream& input, std::ofstream& output);
void fillSequence(std::istream& input, std::vector<int>& sequence);
int countPairWithDifference(const std::vector<int>& sequence, int difference);
int binarySearch(const std::vector<int>& sequence, int lowerBound, int upperBound, int searchedValue);

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
    const std::string INPUT_FILE_NAME = "input5.txt";
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
        int desiredValue = sequence[index] + difference;

        if (desiredValue > sequence[sequence.size() - 1])
        {
            break;
        }

        int desiredIndex = binarySearch(sequence, index + 1, sequence.size() - 1, desiredValue);
        if (desiredIndex == -1)
        {
            continue;
        }

        counter++;

        for(supportCounter = desiredIndex + 1; supportCounter < sequence.size() && sequence[supportCounter] == desiredValue; supportCounter++)
        {
            counter++;
        }

        for(supportCounter = desiredIndex - 1; supportCounter >= 0 && sequence[supportCounter] == desiredValue; supportCounter--)
        {
            counter++;
        }
    }

    return counter;
}

int binarySearch(const std::vector<int>& sequence, int lowerBound, int upperBound, int searchedValue)
{
    while (lowerBound <= upperBound)
    {
        int index = (lowerBound + upperBound) / 2;

        if (sequence[index] == searchedValue)
        {
            return index;
        }

        if (searchedValue > sequence[index])
        {
            lowerBound = index + 1;
        }

        if (searchedValue < sequence[index])
        {
            upperBound = index - 1;
        }
    }

    return -1;
}
