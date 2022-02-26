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

const std::vector<char> ALPHABET = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};

struct Position
{
    int y = 0;
    int x = 0;
};

struct SolutionTree
{
    Position position = {};
    int height = -1;
    SolutionTree* parent = nullptr;
    std::vector<SolutionTree*> sons;
};

using Matrix = std::vector<std::pair<std::vector<int>, int>>;
using SolutionsQueue = std::vector<SolutionTree*>;

void initFiles(std::ifstream& input, std::ofstream& output);
void initMatrix(Matrix& matrix, int width);
void checkQueensCapacity(Matrix& matrix, std::ostream& output);
void setQueenToPosition(Matrix& matrix, int indexIX, int indexJX);
void addQueens(Matrix& matrix, int indexHeight, SolutionTree* solutionTree, SolutionsQueue& solutionsToCheck);
void checkPositions(Matrix& matrix, SolutionTree* solutionTree, SolutionsQueue& solutionsToCheck);
void fillMatrixForCurrentSolution(Matrix& matrix, SolutionTree* solutionTree);
void printAllSolutions(SolutionTree* solutionTree, int& countOfSolutions, int height, std::ostream& output);
void printSolution(SolutionTree* solutionTree, std::ostream& output);
void printPosition(Position& position, std::ostream& output);
void check(Matrix& matrix, SolutionTree* solutionTree);

int main()
{
    std::ifstream input;
    std::ofstream output;
    Matrix matrix;
    SolutionTree solutionTree;

    try
    {
        int numberOfQueens = 0;
        initFiles(input, output);

        input >> numberOfQueens;
        if (numberOfQueens < 1 || numberOfQueens > 13)
        {
            throw std::invalid_argument("Error, number of queens should be in range 2 .. 12");
        }
        initMatrix(matrix, numberOfQueens);
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

void checkQueensCapacity(Matrix& matrix, std::ostream& output)
{
    SolutionTree solutionTree;
    int countOfSolutions = 0;
    check(matrix, &solutionTree);
    printAllSolutions(&solutionTree, countOfSolutions, (int) matrix.size() - 1, output);
    output << countOfSolutions << " positions" << std::endl;
}

void check(Matrix& matrix, SolutionTree* solutionTree)
{
    SolutionsQueue solutionsToCheck;
    solutionsToCheck.push_back(solutionTree);

    while (!solutionsToCheck.empty())
    {
        checkPositions(matrix, solutionsToCheck.at(0), solutionsToCheck);
        solutionsToCheck.erase(solutionsToCheck.begin());
    }
}

void checkPositions(Matrix& matrix, SolutionTree* solutionTree, SolutionsQueue& solutionsToCheck)
{
    if (solutionTree->height == -1)
    {
        addQueens(matrix, 0, solutionTree, solutionsToCheck);
    }
    else
    {
        addQueens(matrix, solutionTree->height + 1, solutionTree, solutionsToCheck);
    }
}

void addQueens(Matrix& matrix, int indexHeight, SolutionTree* solutionTree, SolutionsQueue& solutionsToCheck)
{
    Matrix matrixForCurrentSolution = matrix;
    fillMatrixForCurrentSolution(matrixForCurrentSolution, solutionTree);

    for (auto indexWidth = 0; indexWidth < matrix.size(); indexWidth++)
    {
        if (matrixForCurrentSolution.at(indexHeight).first.at(indexWidth) == 0)
        {
            auto solution = new SolutionTree();
            solution->position = {indexHeight, indexWidth};
            solution->parent = solutionTree;
            solution->height = indexHeight;

            solutionTree->sons.push_back(solution);
            if (indexHeight != matrix.size() - 1)
            {
                solutionsToCheck.push_back(solution);
            }
        }
    }
}

void fillMatrixForCurrentSolution(Matrix& matrix, SolutionTree* solutionTree)
{
    if (solutionTree->parent == nullptr)
    {
        return;
    }

    auto solution = solutionTree;

    while (solution != nullptr && solution->height != -1)
    {
        setQueenToPosition(matrix, solution->position.y, solution->position.x);
        solution = solution->parent;
    }
}

void setQueenToPosition(Matrix& matrix, int indexIX, int indexJX)
{
    for (auto indexI = 0; indexI < matrix.size(); indexI++)
    {
        matrix.at(indexI).first.at(indexJX)++;
        matrix.at(indexIX).first.at(indexI)++;

        if (indexIX + indexJX - indexI >= 0 && indexIX + indexJX - indexI < matrix.size())
        {
            matrix.at(indexIX + indexJX - indexI).first.at(indexI)++;
        }

        if (indexIX - indexJX + indexI >= 0 && indexIX - indexJX + indexI < matrix.size())
        {
            matrix.at(indexIX - indexJX + indexI).first.at(indexI)++;
        }
    }

    matrix.at(indexIX).first.at(indexJX) = -1;
}

void printAllSolutions(SolutionTree* solutionTree, int& countOfSolutions, int height, std::ostream& output)
{
    if (solutionTree == nullptr)
    {
        return;
    }

    if (solutionTree->sons.empty() && solutionTree->height == height)
    {
        countOfSolutions++;
        printSolution(solutionTree, output);
        output << std::endl;
    }
    else
    {
        for (auto solution : solutionTree->sons)
        {
            printAllSolutions(solution, countOfSolutions, height, output);
        }
    }
}

void printSolution(SolutionTree* solutionTree, std::ostream& output)
{
    if (solutionTree->parent != nullptr)
    {
        printSolution(solutionTree->parent, output);
    }

    if (solutionTree->height != -1)
    {
        printPosition(solutionTree->position, output);
    }
}

void printPosition(Position& position, std::ostream& output)
{
    output << ALPHABET[position.y] << position.x + 1 << ' ';
}