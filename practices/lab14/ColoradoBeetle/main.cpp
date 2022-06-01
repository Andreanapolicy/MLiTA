#include <iostream>
#include <vector>

using Garden = std::vector<std::vector<std::pair<int, bool>>>;

void initGarden(Garden& garden, int width, int height)
{
    for (auto indexWidth = 0; indexWidth < width; indexWidth++)
    {
        garden.push_back(std::vector<std::pair<int, bool>>(height, {0, false}));
    }
}

void getGardenFromStream(Garden& garden, std::istream& input)
{
    char symbol;
    for (auto indexWidth = 0; indexWidth < garden.size(); indexWidth++)
    {
        for (auto indexHeight = 0; indexHeight < garden.at(indexWidth).size(); indexHeight++)
        {
            std::cin >> symbol;
            if (symbol == '#')
            {
                garden.at(indexWidth).at(indexHeight).first = 1;
            }
        }
    }
}

void writeGarden(Garden& garden)
{
    for (auto indexWidth = 0; indexWidth < garden.size(); indexWidth++)
    {
        for (auto indexHeight = 0; indexHeight < garden.at(0).size(); indexHeight++)
        {
            std::cout << garden.at(indexWidth).at(indexHeight).first;
        }

        std::cout << std::endl;
    }
}

void checkBushes(Garden& garden, int indexWidth, int indexHeight, int& maxCount, int& currentCount)
{
    if (indexWidth >= 0 && indexWidth < garden.size() && indexHeight >= 0 && indexHeight < garden.at(0).size() && garden.at(indexWidth).at(indexHeight).first == 1 && !garden[indexWidth][indexHeight].second)
    {
        garden[indexWidth][indexHeight].second = true;
        currentCount++;
        maxCount = std::max(maxCount, currentCount);
    }

    if (indexWidth - 1 >= 0 && indexWidth - 1 < garden.size() && indexHeight >= 0 && indexHeight < garden.at(0).size() && garden.at(indexWidth - 1).at(indexHeight).first == 1 && !garden[indexWidth - 1][indexHeight].second)
    {
        checkBushes(garden, indexWidth - 1, indexHeight, maxCount, currentCount);
        maxCount = std::max(maxCount, currentCount);
        garden[indexWidth - 1][indexHeight].second = false;
        currentCount--;
    }

    if (indexWidth >= 0 && indexWidth < garden.size() && indexHeight - 1 >= 0 && indexHeight - 1 < garden.at(0).size() && garden.at(indexWidth).at(indexHeight - 1).first == 1 && !garden[indexWidth][indexHeight - 1].second)
    {
        checkBushes(garden, indexWidth, indexHeight - 1, maxCount, currentCount);
        maxCount = std::max(maxCount, currentCount);
        garden[indexWidth][indexHeight - 1].second = false;
        currentCount--;
    }

    if (indexWidth + 1 >= 0 && indexWidth + 1 < garden.size() && indexHeight >= 0 && indexHeight < garden.at(0).size() && garden.at(indexWidth + 1).at(indexHeight).first == 1 && !garden[indexWidth + 1][indexHeight].second)
    {
        checkBushes(garden, indexWidth + 1, indexHeight, maxCount, currentCount);
        maxCount = std::max(maxCount, currentCount);
        garden[indexWidth + 1][indexHeight].second = false;
        currentCount--;
    }

    if (indexWidth >= 0 && indexWidth < garden.size() && indexHeight + 1 >= 0 && indexHeight + 1 < garden.at(0).size() && garden.at(indexWidth).at(indexHeight + 1).first == 1 && !garden[indexWidth][indexHeight + 1].second)
    {
        checkBushes(garden, indexWidth, indexHeight + 1, maxCount, currentCount);
        maxCount = std::max(maxCount, currentCount);
        garden[indexWidth][indexHeight + 1].second = false;
        currentCount--;
    }
}

int getCountOfEatenBushes(Garden& garden)
{
    int count = 0;

    for (auto indexWidth = 0; indexWidth < garden.size(); indexWidth++)
    {
        for (auto indexHeight = 0; indexHeight < garden.at(0).size(); indexHeight++)
        {
            int currentCount = 0;
            if (garden.at(indexWidth).at(indexHeight).first == 1)
            {
                checkBushes(garden, indexWidth, indexHeight, count, currentCount);
                garden[indexWidth][indexHeight].second = false;
            }
        }
    }

    return count;
}

int main()
{
    int width = 0;
    int length = 0;
    std::cin >> width >> length;
    Garden garden(width, std::vector<std::pair<int, bool>>(length, {0, false}));

    std::cout << std::endl;
    getGardenFromStream(garden, std::cin);
    writeGarden(garden);
    int count = getCountOfEatenBushes(garden);

    std::cout << count;
    return 0;
}
