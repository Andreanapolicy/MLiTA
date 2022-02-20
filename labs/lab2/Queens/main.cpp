/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 2.12
 * ===============================================================
 * Методом поиска в ширину расставить на шахматной доске размером
 * N × N  клеток N  ферзей  (1 ≤ N ≤ 12) так, чтобы они не
 * атаковали один другого. Иными словами, они должны стоять
 * на разных горизонталях, вертикалях и диагоналях.
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
void initMatrix(Matrix& matrix, int width, int height);
void checkQueensCapacity(Matrix& matrix, int numberOfQueens, std::ofstream& output);

int main()
{
    std::ifstream input;
    std::ofstream output;
    Matrix matrix;

    try
    {
        int numberOfQueens = 0;
        initFiles(input, output);

        input >> numberOfQueens;
        initMatrix(matrix, numberOfQueens, numberOfQueens);
        checkQueensCapacity(matrix, numberOfQueens, output);
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

void initMatrix(Matrix& matrix, int width)
{
    for (auto indexHeight = 0; indexHeight < width + 2; indexHeight++)
    {
        matrix.push_back(std::pair<std::vector<int>, int>({}, indexHeight));

        for (auto indexWidth = 0; indexWidth < width + 2; indexWidth++)
        {
            if (indexWidth == 0 || indexWidth == width + 1 || indexHeight == 0 || indexHeight == width + 1)
            {
                matrix.at(indexHeight).first.push_back(-1);
            }
            else
            {
                matrix.at(indexHeight).first.push_back(0);
            }
        }
    }
}

void checkQueensCapacity(Matrix& matrix, int numberOfQueens, std::ofstream& output)
{
    Matrix locationMatrix;

}
