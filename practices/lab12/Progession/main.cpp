#include <iostream>
#include <vector>

void checkArithmeticProgressionOnBlocks(std::istream& input, std::ostream& output);

bool isArithmeticProgression(const std::vector<int>& numbers);

int main()
{
    int blockCount = 0;
    std::cin >> blockCount;

    for (auto index = 0; index < blockCount; index++)
    {
        checkArithmeticProgressionOnBlocks(std::cin, std::cout);
    }

    return 0;
}

void checkArithmeticProgressionOnBlocks(std::istream& input, std::ostream& output)
{
    int numbersCount = 0;
    input >> numbersCount;

    std::vector<int> numbers(numbersCount, 0);

    for (auto &element : numbers)
    {
        input >> element;
    }

    output << (isArithmeticProgression(numbers) ? "YES" : "NO");
    output << std::endl;
}

bool isArithmeticProgression(const std::vector<int>& numbers)
{
    std::vector<int> sortedNumbers = numbers;

    std::sort(sortedNumbers.begin(), sortedNumbers.end());

    if (sortedNumbers.size() <= 1)
    {
        return true;
    }

    int difference = sortedNumbers[1] - sortedNumbers[0];
    for (auto index = 0; index < sortedNumbers.size() - 1; index++)
    {
        int newDifference = sortedNumbers[index + 1] - sortedNumbers[index];

        if (difference != newDifference)
        {
            return false;
        }
    }

    return true;
}
