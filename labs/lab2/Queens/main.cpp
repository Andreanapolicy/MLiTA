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

//void write(Matrix& matrix)
//{
//    for (auto indexWidth = 0; indexWidth < matrix.size(); indexWidth++)
//    {
//        for (auto indexHeight = 0; indexHeight < matrix.at(0).first.size(); indexHeight++)
//        {
//            std::cout << matrix.at(indexWidth).first.at(indexHeight);
//        }
//
//        std::cout << std::endl;
//    }
//}

void initFiles(std::ifstream& input, std::ofstream& output);
void initMatrix(Matrix& matrix, int width);
void checkQueensCapacity(Matrix& matrix, std::ostream& output);
void setQueen(Matrix& matrix, int indexIX, int indexJX);
void removeQueen(Matrix& matrix, int indexIX, int indexJX);
void printQueensPosition(Matrix& matrix, std::ostream& output);
void addQueens(Matrix& matrix, int indexI, std::ostream& output, int& solutionsCount);

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
        initMatrix(matrix, numberOfQueens);
        std::cout << matrix.size() << std::endl;
        checkQueensCapacity(matrix, output);
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
                matrix.at(indexHeight).first.push_back(-2);
            }
            else
            {
                matrix.at(indexHeight).first.push_back(0);
            }
        }
    }
}

void checkQueensCapacity(Matrix& matrix, std::ostream& output)
{
    int solutionsCount = 0;
    addQueens(matrix, 1, output, solutionsCount);
    output << solutionsCount << " positions" << std::endl;
}

void addQueens(Matrix& matrix, int indexI, std::ostream& output, int& solutionsCount)
{
    for (auto indexJ = 1; indexJ < matrix.size() - 2; indexJ++)
    {
        if (matrix.at(indexI).first.at(indexJ) == 0)
        {
            setQueen(matrix, indexI, indexJ);

            if (indexJ != matrix.size() - 1)
            {
                std::cout << std::endl;
                write(matrix);
                addQueens(matrix, indexI + 1, output, solutionsCount);
            } else
            {
                solutionsCount++;
                printQueensPosition(matrix, output);
            }

            removeQueen(matrix, indexI, indexJ);
        }
    }
}

void setQueen(Matrix& matrix, int indexIX, int indexJX)
{
    for (auto indexI = 1; indexI < matrix.size() - 2; indexI++)
    {
        matrix.at(indexI).first.at(indexJX)++;
        matrix.at(indexIX).first.at(indexI)++;

        if (indexIX + indexJX - indexI >= 1 && indexIX + indexJX - indexI < matrix.size() - 1)
        {
            matrix.at(indexIX + indexJX - indexI).first.at(indexI)++;
        }

        if (indexIX - indexJX + indexI >= 1 && indexIX - indexJX + indexI < matrix.size() - 1)
        {
            matrix.at(indexIX - indexJX + indexI).first.at(indexI)++;
        }
    }

    matrix.at(indexIX).first.at(indexJX) = -1;
}

void removeQueen(Matrix& matrix, int indexIX, int indexJX)
{
    for (auto indexI = 1; indexI < matrix.size() - 2; indexI++)
    {
        matrix.at(indexI).first.at(indexJX)--;
        matrix.at(indexIX).first.at(indexI)--;

        if (indexIX + indexJX - indexI >= 1 && indexIX + indexJX - indexI < matrix.size() - 1)
        {
            matrix.at(indexIX + indexJX - indexI).first.at(indexI)--;
        }

        if (indexIX - indexJX + indexI >= 1 && indexIX - indexJX + indexI < matrix.size() - 1)
        {
            matrix.at(indexIX - indexJX + indexI).first.at(indexI)--;
        }
    }

    matrix.at(indexIX).first.at(indexJX) = 0;
}

void printQueensPosition(Matrix& matrix, std::ostream& output)
{
    for (auto indexI = 1; indexI < matrix.size() - 2; indexI++)
    {
        for (auto indexJ = 1; indexJ < matrix.size() - 2; indexJ++)
        {
            if (matrix.at(indexI).first.at(indexJ) == -1)
            {
                output << 'a' + (indexJ - 1) << indexI;

                if (indexI != matrix.size() - 1)
                {
                    output << ' ';
                }
            }
        }
    }

    output << std::endl;
}