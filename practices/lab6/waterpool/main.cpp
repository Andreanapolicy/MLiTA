#include <iostream>
#include <vector>
#include <exception>

using Matrix = std::vector<std::vector<int>>;

void initMatrix(Matrix& matrix, int doctorsCount);
void fillMatrix(std::istream& input, Matrix& matrix);
void topologicalSortEntryPoint(const Matrix& matrix, std::ostream& output);
void topologicalSort(const Matrix& matrix, std::vector<int>& visitedNodes, std::vector<int>& nodesStack, int node);

int main()
{
    std::cout << "Pass count of doctors: ";
    int doctorsCount;
    std::cin >> doctorsCount;

    Matrix matrix;
    initMatrix(matrix, doctorsCount);
    std::cout << "Now, pass dependencies: " << std::endl;
    fillMatrix(std::cin, matrix);
    try
    {
        topologicalSortEntryPoint(matrix, std::cout);
    }
    catch (const std::exception& exception)
    {
        std::cout << "No" << std::endl;
        return 0;
    }

    return 0;
}

void initMatrix(Matrix& matrix, int doctorsCount)
{
    for (auto indexI = 0; indexI < doctorsCount; indexI++)
    {
        matrix.push_back(std::vector<int>(doctorsCount, 0));
    }
}

void fillMatrix(std::istream& input, Matrix& matrix)
{
    int countOfDependencies = 0;
    int value = 0;

    for (auto index = 0; index < matrix.size(); index++)
    {
        input >> countOfDependencies;
        for (auto dependencyIndex = 0; dependencyIndex < countOfDependencies; dependencyIndex++)
        {
            input >> value;
            matrix[index][value - 1] = 1;
        }
    }
}

void topologicalSortEntryPoint(const Matrix& matrix, std::ostream& output)
{
    std::vector<int> nodesStack;
    std::vector<int> visitedNodes(matrix.size(), 0);

    for (auto index = 0; index < matrix.size(); index++)
    {
        if (visitedNodes[index] == 0)
        {
            topologicalSort(matrix, visitedNodes, nodesStack, index);
        }
    }

    std::cout << "Yes" << std::endl;
    for (auto element : nodesStack)
    {
        std::cout << element + 1 << std::endl;
    }
}

void topologicalSort(const Matrix& matrix, std::vector<int>& visitedNodes, std::vector<int>& nodesStack, int node)
{
    visitedNodes[node] = 1;
    for (auto index = 0; index < matrix.size(); index++)
    {
        if (matrix[node][index] == 0)
        {
            continue;
        }
        if (matrix[node][index] != 0 && visitedNodes[index] == 0)
        {
            topologicalSort(matrix, visitedNodes, nodesStack, index);
        }
        if (visitedNodes[index] == 1)
        {
            throw std::invalid_argument("cycle");
        }
    }
    visitedNodes[node] = 2;

    nodesStack.push_back(node);
}