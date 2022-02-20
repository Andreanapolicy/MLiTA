#include <iostream>
#include <sstream>
#include <vector>

using Garden = std::vector<std::pair<std::vector<int>, int>>;

void initGarden(Garden& garden, int width, int height)
{
    for (auto indexWidth = 0; indexWidth < width + 2; indexWidth++)
    {
        garden.push_back(std::pair<std::vector<int>, int>({}, indexWidth));

        for (auto indexHeight = 0; indexHeight < height + 2; indexHeight++)
        {
            if (indexHeight == 0 || indexHeight == height + 1 || indexWidth == 0 || indexWidth == width + 1)
            {
                garden.at(indexWidth).first.push_back(-1);
            }
            else
            {
                garden.at(indexWidth).first.push_back(0);
            }
        }
    }
}

void getGardenFromStream(Garden& garden, std::istream& input)
{
    char symbol;
    for (auto indexWidth = 1; indexWidth < garden.size() - 1; indexWidth++)
    {
        for (auto indexHeight = 1; indexHeight < garden.at(1).first.size() - 1; indexHeight++)
        {
            std::cin >> symbol;
            if (symbol == '#')
            {
                garden.at(indexWidth).first.at(indexHeight) = 1;
            }
        }
    }
}

void checkBeds(Garden& garden, int indexWidth, int indexHeight)
{
    if (garden.at(indexWidth).first.at(indexHeight) == 1)
    {
        garden.at(indexWidth).first.at(indexHeight) = -1;
    }

    if (garden.at(indexWidth - 1).first.at(indexHeight) == 1)
    {
        checkBeds(garden, indexWidth - 1, indexHeight);
    }

    if (garden.at(indexWidth).first.at(indexHeight - 1) == 1)
    {
        checkBeds(garden, indexWidth, indexHeight - 1);
    }

    if (garden.at(indexWidth + 1).first.at(indexHeight) == 1)
    {
        checkBeds(garden, indexWidth + 1, indexHeight);
    }

    if (garden.at(indexWidth).first.at(indexHeight + 1) == 1)
    {
        checkBeds(garden, indexWidth, indexHeight + 1);
    }
}

void getCountOfBeds(Garden& garden, int& count)
{
    char symbol;
    for (auto indexWidth = 1; indexWidth < garden.size() - 1; indexWidth++)
    {
        for (auto indexHeight = 1; indexHeight < garden.at(1).first.size() - 1; indexHeight++)
        {
            if (garden.at(indexWidth).first.at(indexHeight) == 1)
            {
                checkBeds(garden, indexWidth, indexHeight);
                count++;
            }
        }
    }
}

void writeGarden(Garden& garden)
{
    for (auto indexWidth = 0; indexWidth < garden.size(); indexWidth++)
    {
        for (auto indexHeight = 0; indexHeight < garden.at(0).first.size(); indexHeight++)
        {
            std::cout << garden.at(indexWidth).first.at(indexHeight);
        }

        std::cout << std::endl;
    }
}

int main()
{
    int width = 0;
    int length = 0;
    int bedsCount = 0;
    Garden garden;

    std::cout << "Put width and length of garden: ";
    std::cin >> width >> length;

    initGarden(garden, width, length);

    std::cout << std::endl;
    getGardenFromStream(garden, std::cin);

    getCountOfBeds(garden, bedsCount);
    std::cout << "Count of beds: " << bedsCount << std::endl;
    return 0;
}
