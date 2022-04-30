#include <iostream>
#include <vector>
#include <string>

using SuitableStrings = std::vector<std::string>;

void fillSuitableStrings(SuitableStrings& suitableStrings, int letterCount);
void printMostSuitableSubstring(SuitableStrings& suitableStrings, std::ostream& output);

int main()
{
    int letterCount = 0;

    SuitableStrings suitableStrings;
    std::cin >> letterCount;
    fillSuitableStrings(suitableStrings, letterCount);
    printMostSuitableSubstring(suitableStrings, std::cout);
    return 0;
}

void fillSuitableStrings(SuitableStrings& suitableStrings, int letterCount)
{
    std::string substring;
    char symbol;

    for (auto index = 0; index < letterCount; index++)
    {
        std::cin >> symbol;
        auto symbolPos = substring.find(symbol);

        if (substring.find(symbol) != std::string::npos)
        {
            suitableStrings.push_back(substring);
            if (symbolPos + 1 == substring.length())
            {
                substring = "";
            }
            else
            {
                substring = substring.substr(symbolPos + 1);
            }
        }

        substring.push_back(symbol);
    }

    suitableStrings.push_back(substring);
}

void printMostSuitableSubstring(SuitableStrings& suitableStrings, std::ostream& output)
{

    std::sort(suitableStrings.begin(), suitableStrings.end(), [](const std::string& left, const std::string& right){
        if (left.length() != right.length())
        {
            return left.length() > right.length();
        }

        return left < right;
    });

    output << suitableStrings[0];
}