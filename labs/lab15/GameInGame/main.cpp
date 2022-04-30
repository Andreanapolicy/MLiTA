/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 15.1
 * ===============================================================
 * Вася и Петя любят игры со спичками. Несколько дней они играли
 * в следующую игру. Два игрока поочередно забирают из кучки,
 * содержащей N спичек, от 1 до M спичек. Выигрывает игрок,
 * после хода которого кучка спичек опустеет. Доведя до
 * совершенства свое мастерство, они решили изменить правила.
 * Первый игрок задает значение N. Потом второй игрок указывает
 * величину M. Далее игроки поочередно берут спички, начиная с
 * первого игрока. По жребию первым игроком оказался Вася.
 * Для продления удовольствия Петя при любых дальнейших ответах
 * Васи собирается выиграть так, чтобы партия состояла из
 * наибольшего числа ходов. Укажите правильный ответ Пети.
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Windows 10
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <iostream>
#include <fstream>
#include <cmath>

constexpr long long MIN_STEP = 2;
constexpr long long BORDERLINE_STEP = 1000000000;
constexpr long long MAX_STEP = 1000000000000;

void InitFiles(std::ifstream& input, std::ofstream& output);
long long GetMinStepForWin(long long matchesCount);
bool isAvailableMatchesCount(long long matchesCount);
bool isAvailableStep(long long step);

int main()
{
    std::ifstream input;
    std::ofstream output;

    try
    {
        InitFiles(input, output);

        long long matchesCount = 0;
        long long step;

        input >> matchesCount;

        if (!isAvailableMatchesCount(matchesCount))
        {
            throw std::invalid_argument("Error, matches count should be in range of [2, 10^12]");
        }

        step = GetMinStepForWin(matchesCount);
        output << step << std::endl;

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

long long GetMinStepForWin(long long matchesCount)
{
    long long upperBound;
    if (matchesCount >= BORDERLINE_STEP)
    {
        upperBound = static_cast<long long>(std::sqrt(matchesCount) + 1);
    }
    else
    {
        upperBound = static_cast<long long>(matchesCount / 2);
    }

    for (long long index = 3; index <= upperBound; index++)
    {
        if (matchesCount % index == 0)
        {
            return index - 1;
        }
    }

    if (isAvailableStep(matchesCount - 1))
    {
        return matchesCount - 1;
    }

    return 0;
}

bool isAvailableStep(long long step)
{
    return step >= MIN_STEP;
}

bool isAvailableMatchesCount(long long int matchesCount)
{
    return matchesCount >= MIN_STEP && matchesCount <= MAX_STEP;
}
