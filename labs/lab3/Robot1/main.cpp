/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 3.2
 * ===============================================================
 * Робот находится на расстоянии X шагов от цели. За один ход он
 * продвигается либо к цели, либо в противоположном направлении.
 * Если он достигает цели, то немедленно останавливается.
 * Найти количество способов достижения цели ровно за Y шагов.
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Linux, Ubuntu 20.04
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <fstream>
#include <iostream>
#include <map>

void initFiles(std::ifstream& input, std::ofstream& output);
long long getCountOfSolutions(int stepsToTarget, int stepsNumber);
long long runSolutionsSearcher(int stepsToTarget, int stepsNumber, std::map<std::pair<int, int>, long long>& countedExpressions);

int main()
{
    std::ifstream input;
    std::ofstream output;

    try
    {
        int stepsToTarget = 0;
        int stepsNumber = 0;
        initFiles(input, output);

        input >> stepsToTarget >> stepsNumber;
        if (stepsToTarget < 0 || stepsToTarget > 50 || stepsNumber < 0 || stepsNumber > 50)
        {
            throw std::invalid_argument("Error, width and height should be in range 1 .. 50");
        }

        output << getCountOfSolutions(stepsToTarget, stepsNumber);

        if (!output.flush())
        {
            throw std::runtime_error("Error, can't flush output");
        }

        output.close();
    }
    catch (const std::exception& exception)
    {
        std::cout << "Message: " << exception.what() << std::endl;
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

long long getCountOfSolutions(int stepsToTarget, int stepsNumber)
{
    std::map<std::pair<int, int>, long long> countedExpressions; // {stepsToTarget, stepsNumber} : count

    return runSolutionsSearcher(stepsToTarget, stepsNumber, countedExpressions);
}

long long runSolutionsSearcher(int stepsToTarget, int stepsNumber, std::map<std::pair<int, int>, long long>& countedExpressions)
{
    if ((stepsToTarget == 0 && stepsNumber != 0) || (stepsToTarget != 0 && stepsNumber == 0))
    {
        return 0;
    }

    if (stepsToTarget > stepsNumber)
    {
        return 0;
    }

    if (stepsToTarget == stepsNumber)
    {
        return 1;
    }

    long long countForBackStep = 0;
    auto countedExpressionForBackStep = countedExpressions.find(std::pair<int, int>{stepsToTarget + 1, stepsNumber - 1});

    if (countedExpressionForBackStep != countedExpressions.end())
    {
        countForBackStep = countedExpressionForBackStep->second;
    }
    else
    {
        countForBackStep = runSolutionsSearcher(stepsToTarget + 1, stepsNumber - 1, countedExpressions);
        countedExpressions.emplace(std::pair<int, int>{stepsToTarget + 1, stepsNumber - 1}, countForBackStep);
    }

    long long countForForwardStep = 0;
    auto countedExpressionForForwardStep = countedExpressions.find(std::pair<int, int>{stepsToTarget - 1, stepsNumber - 1});

    if (countedExpressionForForwardStep != countedExpressions.end())
    {
        countForForwardStep = countedExpressionForForwardStep->second;
    }
    else
    {
        countForForwardStep = runSolutionsSearcher(stepsToTarget - 1, stepsNumber - 1, countedExpressions);
        countedExpressions.emplace(std::pair<int, int>{stepsToTarget - 1, stepsNumber - 1}, countForForwardStep);
    }

    return countForBackStep + countForForwardStep;
}