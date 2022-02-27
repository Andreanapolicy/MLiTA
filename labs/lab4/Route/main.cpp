/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 4.5
 * ===============================================================
 * Дана матрица N × N, заполненная целыми положительными числами.
 * Путь по матрице начинается в левом верхнем углу. За один ход
 * можно пройти в соседнюю по вертикали или горизонтали клетку
 * (если она существует). Нельзя ходить по диагонали, нельзя
 * оставаться на месте. Требуется найти максимальную сумму
 * чисел, стоящих в клетках по пути длиной K клеток (клетку
 * можно посещать несколько раз).
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Linux, Ubuntu 20.04
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <fstream>
#include <iostream>
#include <vector>

using Matrix = std::vector<std::pair<std::vector<int>, int>>;

void initFiles(std::ifstream& input, std::ofstream& output);
void initMatrix(Matrix& matrix, int width);


int main()
{
    std::ifstream input;
    std::ofstream output;
    Matrix matrix;

    try
    {
        int size = 0;
        int stepsToTarget = 0;
        initFiles(input, output);

        input >> size >> stepsToTarget;
        if (size < 2 || size > 20)
        {
            throw std::invalid_argument("Error, size should be in range 2 .. 20");
        }

        if (stepsToTarget < 0 || stepsToTarget > 20)
        {
            throw std::invalid_argument("Error, steps to target should be in range 1 .. 20");
        }

        initMatrix(matrix, size);

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

void initMatrix(Matrix& matrix, int width)
{
    for (auto indexHeight = 0; indexHeight < width; indexHeight++)
    {
        matrix.push_back(std::pair<std::vector<int>, int>({}, indexHeight));

        for (auto indexWidth = 0; indexWidth < width; indexWidth++)
        {
            matrix.at(indexHeight).first.push_back(0);
        }
    }
}
