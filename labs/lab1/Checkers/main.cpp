/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 1.7
 * ===============================================================
 * На шахматном поле расположены N черных и одна белая шашка.
 * Требуется написать программу, которая по заданному расположению
 * шашек определяет, какое максимальное количество шашек может
 * взять белая шашка за один ход.
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Linux, Ubuntu 20.04
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using CheckerField = std::vector<std::pair<std::vector<int>, int>>;

void initFiles(std::ifstream& input, std::ofstream& output);

void initCheckerField(CheckerField& checkerField);
void fillCheckerField(std::ifstream& input, CheckerField& checkerField, int& indexWidthPos, int& indexHeightPos);
void checkCheckers(CheckerField& garden, int indexWidth, int indexHeight, int countOfDefeatCheckers, int& maxDefeatCheckers);
int getCountOfDefeatedCheckers(CheckerField& checkerField, int indexWidthPos, int indexHeightPos);

int main()
{
    std::ifstream input;
    std::ofstream output;
    CheckerField checkerField;

    try
    {
        int indexWidthPos = 0;
        int indexHeightPos = 0;
        initFiles(input, output);
        initCheckerField(checkerField);
        fillCheckerField(input, checkerField, indexWidthPos, indexHeightPos);
        output << getCountOfDefeatedCheckers(checkerField, indexWidthPos, indexHeightPos);
        if (!output.flush())
        {
            throw std::runtime_error("Error, can't flush output");
        }

        output.close();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
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

void initCheckerField(CheckerField& checkerField)
{
    const int WIDTH = 8;
    const int HEIGHT = 8;

    for (auto indexHeight = 0; indexHeight < HEIGHT + 2; indexHeight++)
    {
        checkerField.push_back(std::pair<std::vector<int>, int>({}, indexHeight));

        for (auto indexWidth = 0; indexWidth < WIDTH + 2; indexWidth++)
        {
            if (indexWidth == 0 || indexWidth == WIDTH + 1 || indexHeight == 0 || indexHeight == HEIGHT + 1)
            {
                checkerField.at(indexHeight).first.push_back(-1);
            }
            else
            {
                checkerField.at(indexHeight).first.push_back(0);
            }
        }
    }
}

void fillCheckerField(std::ifstream& input, CheckerField& checkerField, int& indexWidthPos, int& indexHeightPos)
{
    char symbol;
    for (auto indexHeight = 1; indexHeight < checkerField.size() - 1; indexHeight++)
    {
        for (auto indexWidth = 1; indexWidth < checkerField.at(1).first.size() - 1; indexWidth++)
        {
            input >> symbol;
            switch (symbol)
            {
                case '1':
                    checkerField.at(indexHeight).first.at(indexWidth) = 1;
                    break;
                case '2':
                    checkerField.at(indexHeight).first.at(indexWidth) = 2;
                    indexWidthPos = indexWidth;
                    indexHeightPos = indexHeight;
                    break;
            }
        }
    }
}

int getCountOfDefeatedCheckers(CheckerField& checkerField, int indexWidthPos, int indexHeightPos)
{
    int maxDefeatCheckers = 0;
    int countOfDefeatCheckers = 0;
    checkCheckers(checkerField, indexWidthPos, indexHeightPos, countOfDefeatCheckers, maxDefeatCheckers);

    return maxDefeatCheckers;
}

void checkCheckers(CheckerField& garden, int indexWidth, int indexHeight, int countOfDefeatCheckers, int& maxDefeatCheckers)
{
    if (garden.at(indexHeight - 1).first.at(indexWidth - 1) == 1 && garden.at(indexHeight - 2).first.at(indexWidth - 2) == 0)
    {
        garden.at(indexHeight - 1).first.at(indexWidth - 1) = 0;
        garden.at(indexHeight - 2).first.at(indexWidth - 2) = 2;
        garden.at(indexHeight).first.at(indexWidth) = 0;
        countOfDefeatCheckers++;
        checkCheckers(garden, indexWidth - 2, indexHeight - 2, countOfDefeatCheckers, maxDefeatCheckers);

        garden.at(indexHeight - 1).first.at(indexWidth - 1) = 1;
        garden.at(indexHeight - 2).first.at(indexWidth - 2) = 0;
        garden.at(indexHeight).first.at(indexWidth) = 2;
        maxDefeatCheckers = std::max(maxDefeatCheckers, countOfDefeatCheckers);
        countOfDefeatCheckers--;
    }

    if (garden.at(indexHeight + 1).first.at(indexWidth - 1) == 1 && garden.at(indexHeight + 2).first.at(indexWidth - 2) == 0)
    {
        garden.at(indexHeight + 1).first.at(indexWidth - 1) = 0;
        garden.at(indexHeight + 2).first.at(indexWidth - 2) = 2;
        garden.at(indexHeight).first.at(indexWidth) = 0;
        countOfDefeatCheckers++;
        checkCheckers(garden, indexWidth - 2, indexHeight + 2, countOfDefeatCheckers, maxDefeatCheckers);

        garden.at(indexHeight + 1).first.at(indexWidth - 1) = 1;
        garden.at(indexHeight + 2).first.at(indexWidth - 2) = 0;
        garden.at(indexHeight).first.at(indexWidth) = 2;
        maxDefeatCheckers = std::max(maxDefeatCheckers, countOfDefeatCheckers);
        countOfDefeatCheckers--;
    }

    if (garden.at(indexHeight + 1).first.at(indexWidth + 1) == 1 && garden.at(indexHeight + 2).first.at(indexWidth + 2) == 0)
    {
        garden.at(indexHeight + 1).first.at(indexWidth + 1) = 0;
        garden.at(indexHeight + 2).first.at(indexWidth + 2) = 2;
        garden.at(indexHeight).first.at(indexWidth) = 0;
        countOfDefeatCheckers++;
        checkCheckers(garden, indexWidth + 2, indexHeight + 2, countOfDefeatCheckers, maxDefeatCheckers);

        garden.at(indexHeight + 1).first.at(indexWidth + 1) = 1;
        garden.at(indexHeight + 2).first.at(indexWidth + 2) = 0;
        garden.at(indexHeight).first.at(indexWidth) = 2;
        maxDefeatCheckers = std::max(maxDefeatCheckers, countOfDefeatCheckers);
        countOfDefeatCheckers--;
    }

    if (garden.at(indexHeight - 1).first.at(indexWidth + 1) == 1 && garden.at(indexHeight - 2).first.at(indexWidth + 2) == 0)
    {
        garden.at(indexHeight - 1).first.at(indexWidth + 1) = 0;
        garden.at(indexHeight - 2).first.at(indexWidth + 2) = 2;
        garden.at(indexHeight).first.at(indexWidth) = 0;
        countOfDefeatCheckers++;
        checkCheckers(garden, indexWidth + 2, indexHeight - 2, countOfDefeatCheckers, maxDefeatCheckers);

        garden.at(indexHeight - 1).first.at(indexWidth + 1) = 1;
        garden.at(indexHeight - 2).first.at(indexWidth + 2) = 0;
        garden.at(indexHeight).first.at(indexWidth) = 2;
        maxDefeatCheckers = std::max(maxDefeatCheckers, countOfDefeatCheckers);
        countOfDefeatCheckers--;
    }
}