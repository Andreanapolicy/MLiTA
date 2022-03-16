#include <iostream>
#include <vector>

void fillVector(std::istream& input, std::vector<int>& vector);
void reestablishVector(const std::vector<int>& inverseVector, std::vector<int>& originalVector);
void writeVector(std::ostream& output, const std::vector<int>& vector);
void fillVectorBySubsequence(std::vector<int>& vector);

int main()
{
    std::cout << "Pass count of elements: ";
    int countOfNumbers;
    std::cout << "Pass elements: ";
    std::cin >> countOfNumbers;

    std::vector<int> inverseVector(countOfNumbers);
    std::vector<int> originalVector;

    fillVector(std::cin, inverseVector);
    reestablishVector(inverseVector, originalVector);
    writeVector(std::cout, originalVector);

    return 0;
}

void fillVector(std::istream& input, std::vector<int>& vector)
{
    for (auto index = 0; index < vector.size(); index++)
    {
        input >> vector[index];
    }
}

void reestablishVector(const std::vector<int>& inverseVector, std::vector<int>& originalVector)
{
    int vectorSize = (int) inverseVector.size();
    std::vector<int> supportVector(vectorSize);
    fillVectorBySubsequence(supportVector);

    for (auto index = 0; index <= vectorSize - 1; index++)
    {
        int lastIndex = inverseVector.at(vectorSize - index - 1);

        originalVector.push_back(supportVector[supportVector.size() - lastIndex - 1]);
        supportVector.erase(supportVector.begin() + supportVector.size() - lastIndex - 1);
    }
}

void writeVector(std::ostream& output, const std::vector<int>& vector)
{
    for (int index = vector.size() - 1; index >= 0; index--)
    {
        output << vector[index] << ' ';
    }
    output << std::endl;
}

void fillVectorBySubsequence(std::vector<int>& vector)
{
    for (int index = 0; index < vector.size(); ++index)
    {
        vector[index] = index + 1;
    }
}
