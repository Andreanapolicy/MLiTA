#include <iostream>
#include <vector>
#include <string>
#include <sstream>

void fillSupportVector(std::vector<int>& supportVector, std::istream& input);
void buildSegmentTree(const std::vector<int>& supportVector, std::vector<int>& segmentTree, int startIndex, int lowerBound, int upperBound);
int rmq(const std::vector<int>& segmentTree, int lowerBound, int upperBound, int index, int startIndex, int endIndex);
void write(const std::vector<int>& segmentTree, std::ostream& output);

int main()
{
    std::vector<int> supportVector;
    fillSupportVector(supportVector, std::cin);
    std::vector<int> segmentTree(supportVector.size() * 2 + 1, 0);
    buildSegmentTree(supportVector, segmentTree, 1, 0, supportVector.size() - 1);

    std::string command;
    while (std::cin >> command)
    {
        int firstParam;
        int secondParam;
        int thirdParam;

        std::cin >> firstParam >> secondParam;

        if (command == "rmq")
        {
            std::cout << rmq(segmentTree, 0, segmentTree.size() - 1, 1, firstParam, secondParam) << std::endl;
        }
        else if (command == "add1")
        {

        }
        else if (command == "add2")
        {

        }
    }

    return 0;
}

void fillSupportVector(std::vector<int> &supportVector, std::istream &input)
{
    std::string line;
    std::getline(input, line);
    std::istringstream iss(line);
    int number;

    while (iss >> number)
    {
        supportVector.push_back(number);
    }
}

void buildSegmentTree(const std::vector<int> &supportVector, std::vector<int> &segmentTree, int startIndex, int lowerBound, int upperBound)
{
    int middle = (lowerBound + upperBound) / 2;

    if (lowerBound == upperBound)
    {
        segmentTree[startIndex] = supportVector[lowerBound];
        return;
    }

    buildSegmentTree(supportVector, segmentTree, 2 * startIndex, lowerBound, middle);
    buildSegmentTree(supportVector, segmentTree, 2 * startIndex + 1, middle + 1, upperBound);

    segmentTree[startIndex] = segmentTree[2 * startIndex] + segmentTree[2 * startIndex + 1];
}

void write(const std::vector<int> &segmentTree, std::ostream &output)
{
    for (auto element : segmentTree)
    {
        output << element << ' ';
    }

    output << std::endl;
}

int rmq(const std::vector<int> &segmentTree, int lowerBound, int upperBound, int index, int startIndex, int endIndex)
{
    if (startIndex <= lowerBound && upperBound <= endIndex)
    {
        return segmentTree[index];
    }

    if (upperBound < startIndex || endIndex < lowerBound)
    {
        return 0;
    }

    int middle = (lowerBound + upperBound) / 2;
    return std::max(
            rmq(segmentTree, lowerBound, middle, index * 2, startIndex, endIndex),
            rmq(segmentTree, middle + 1, upperBound, index * 2 + 1, startIndex, endIndex)
    );
}
