/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 14.16
 * ===============================================================
 * Шахматная доска состоит из M строк и N столбцов (1 ≤ M, N ≤ 15)
 * На доске расставлены кони, слоны и ладьи. По заданному
 * расположению фигур требуется определить количество клеток
 * доски, находящихся под боем. Клетки, занятые фигурами,
 * не учитываются.
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Linux, Ubuntu 20.04
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using Matrix = std::vector<std::pair<std::vector<int>, int>>;

void initFiles(std::ifstream& input, std::ofstream& output);
void initMatrix(Matrix& matrix, int height, int width);
void fillMatrix(std::istream& input, Matrix& matrix);
int getCountOfCellsUnderBattle(Matrix& matrix);
void setCellsUnderBattle(Matrix& matrix);
void setCellsUnderKnightBattle(Matrix& matrix, int height, int width);
void setCellsUnderBishopBattle(Matrix& matrix, int height, int width);
void setCellsUnderRookBattle(Matrix& matrix, int height, int width);

int main()
{
    std::ifstream input;
    std::ofstream output;
    Matrix matrix;

    try
    {
        int width = 0;
        int height = 0;
        initFiles(input, output);

        input >> height >> width;
        if (height < 1 || height > 15 || width < 1 || width > 15)
        {
            throw std::invalid_argument("Error, width and height should be in range 2 .. 12");
        }
        initMatrix(matrix, height, width);
        fillMatrix(input, matrix);

        output << getCountOfCellsUnderBattle(matrix) << std::endl;

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

void initMatrix(Matrix& matrix, int height, int width)
{
    for (auto indexHeight = 0; indexHeight < height; indexHeight++)
    {
        matrix.push_back(std::pair<std::vector<int>, int>({}, indexHeight));

        for (auto indexWidth = 0; indexWidth < width; indexWidth++)
        {
            matrix.at(indexHeight).first.push_back(0);
        }
    }
}

void fillMatrix(std::istream& input, Matrix& matrix)
{
    char symbol;

    for (auto height = 0; height < matrix.size(); height++)
    {
        for (auto width = 0; width < matrix.at(0).first.size(); width++)
        {
            input >> symbol;
            switch (symbol)
            {
                case 'K':
                    matrix.at(height).first.at(width) = 1;
                    break;
                case 'B':
                    matrix.at(height).first.at(width) = 2;
                    break;
                case 'R':
                    matrix.at(height).first.at(width) = 3;
                    break;
                case '.':
                    break;
                default:
                    throw std::invalid_argument("Error, wrong chess figure");
            }
        }
    }
}

int getCountOfCellsUnderBattle(Matrix& matrix)
{
    int countOfCellsUnderBattle = 0;

    setCellsUnderBattle(matrix);

    for (auto height = 0; height < matrix.size(); height++)
    {
        for (auto width = 0; width < matrix.at(0).first.size(); width++)
        {
            if (matrix.at(height).first.at(width) == -1)
            {
                countOfCellsUnderBattle++;
            }
        }
    }

    return countOfCellsUnderBattle;
}

void setCellsUnderBattle(Matrix& matrix)
{
    for (auto height = 0; height < matrix.size(); height++)
    {
        for (auto width = 0; width < matrix.at(0).first.size(); width++)
        {
            if (matrix.at(height).first.at(width) == 1)
            {
                setCellsUnderKnightBattle(matrix, height, width); //конь
                continue;
            }

            if (matrix.at(height).first.at(width) == 2)
            {
                setCellsUnderBishopBattle(matrix, height, width); //слон
                continue;
            }

            if (matrix.at(height).first.at(width) == 3)
            {
                setCellsUnderRookBattle(matrix, height, width); // ладья
                continue;
            }
        }
    }
}

void setCellsUnderKnightBattle(Matrix& matrix, int height, int width)
{
    const int matrixHeight = (int) matrix.size();
    const int matrixWidth = (int) matrix.at(0).first.size();
    std::cout << height << " " << width << std::endl;
    std::cout << (height - 1 > 0) << std::endl;
    std::cout << (width - 2 > 0) << std::endl;
    std::cout << (matrix.at(height - 1).first.at(width - 2) == 0) << std::endl;
    if (height - 1 >= 0 && width - 2 >= 0 && matrix.at(height - 1).first.at(width - 2) == 0)
    {
        matrix.at(height - 1).first.at(width - 2) = -1;
    }

    if (height - 2 >= 0 && width - 1 >= 0 && matrix.at(height - 2).first.at(width - 1) == 0)
    {
        matrix.at(height - 2).first.at(width - 1) = -1;
    }

    if (height + 2 < matrixHeight && width - 1 >= 0 && matrix.at(height + 2).first.at(width - 1) == 0)
    {
        matrix.at(height + 2).first.at(width - 1) = -1;
    }

    if (height + 1 < matrixHeight && width - 2 >= 0 && matrix.at(height + 1).first.at(width - 2) == 0)
    {
        matrix.at(height + 1).first.at(width - 2) = -1;
    }

    if (height + 1 < matrixHeight && width + 2 < matrixWidth && matrix.at(height + 1).first.at(width + 2) == 0)
    {
        matrix.at(height + 1).first.at(width + 2) = -1;
    }

    if (height + 2 < matrixHeight && width + 1 < matrixWidth && matrix.at(height + 2).first.at(width + 1) == 0)
    {
        matrix.at(height + 2).first.at(width + 1) = -1;
    }

    if (height - 1 >= 0 && width + 2 < matrixWidth && matrix.at(height - 1).first.at(width + 2) == 0)
    {
        matrix.at(height - 1).first.at(width + 2) = -1;
    }

    if (height - 2 >= 0 && width + 1 < matrixWidth && matrix.at(height - 2).first.at(width + 1) == 0)
    {
        matrix.at(height - 2).first.at(width + 1) = -1;
    }
}

void setCellsUnderBishopBattle(Matrix& matrix, int height, int width)
{
    const int matrixHeight = (int) matrix.size();
    const int matrixWidth = (int) matrix.at(0).first.size();

    for (auto index = 0; index < std::min(matrixWidth, matrixHeight); index++)
    {
        if (height + width - index >= 0 && height + width - index < matrix.size() && matrix.at(height + width - index).first.at(index) == 0)
        {
            matrix.at(height + width - index).first.at(index) = -1;
        }

        if (height - width + index >= 0 && height - width + index < matrix.size() && matrix.at(height - width + index).first.at(index) == 0)
        {
            matrix.at(height - width + index).first.at(index) = -1;
        }
    }
}

void setCellsUnderRookBattle(Matrix& matrix, int height, int width)
{
    const int matrixHeight = (int) matrix.size();
    const int matrixWidth = (int) matrix.at(0).first.size();

    for (auto index = 0; index < matrixWidth; index++)
    {
        if (matrix.at(index).first.at(width) == 0)
        {
            matrix.at(index).first.at(width) = -1;
        }
    }

    for (auto index = 0; index < matrixHeight; index++)
    {
        if (matrix.at(height).first.at(index) == 0)
        {
            matrix.at(height).first.at(index) = -1;
        }
    }
}