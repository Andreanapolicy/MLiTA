#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void fillVector(std::vector<int>& tree, std::istream& input);
void fillTree(std::vector<int>& tree, std::vector<int>& helpVector);
void showTree(std::vector<int>& tree, std::ostream& output);
int rsq(std::vector<int>& tree, int begin, int end);
void add(std::vector<int>& tree, int index, int number);
void update(std::vector<int>& tree, int index, int number);

int main()
{
    std::string command;

    std::vector<int> helpVector;

    fillVector(helpVector, std::cin);
    showTree(helpVector, std::cout);
    std::vector<int> fenwickTree(helpVector.size(), 0);
    fillTree(fenwickTree, helpVector);
    showTree(fenwickTree, std::cout);

    while (std::cin >> command && command != "exit")
    {
        int firstParam;
        int secondParam;

        std::cin >> firstParam >> secondParam;

        if (command == "rsq")
        {
            std::cout << rsq(fenwickTree, firstParam, secondParam) << std::endl;
            showTree(fenwickTree, std::cout);
        }
        else if (command == "add")
        {
            add(fenwickTree, firstParam, secondParam);
            showTree(fenwickTree, std::cout);
        }
        else if (command == "update")
        {
            update(fenwickTree, firstParam, secondParam);
            showTree(fenwickTree, std::cout);
        }
    }
    return 0;
}

void fillVector(std::vector<int>& tree, std::istream& input)
{
    int number;
    std::string readableString;
    std::getline(input, readableString);
    std::istringstream iss(readableString);

    while (iss >> number)
    {
        tree.push_back(number);
    }
}

void showTree(std::vector<int>& tree, std::ostream& output)
{
    for (auto element : tree)
    {
        output << element << ' ';
    }

    output << std::endl;
}

int rsq(std::vector<int> &tree, int begin, int end)
{
    int result = 0;

    for (int index = begin; index < tree.size() && index <= end; ++index)
    {
        result += tree[index];
    }

    return result;
}

void fillTree(std::vector<int> &tree, std::vector<int> &helpVector)
{
    for (int index = 0; index < helpVector.size() - 1; index++)
    {
        add(tree, index, helpVector[index]);
    }
}

void add(std::vector<int> &tree, int index, int number)
{
    tree[index] += number;
}

void update(std::vector<int> &tree, int index, int number)
{
    add(tree, index, number - tree[index]);
}
