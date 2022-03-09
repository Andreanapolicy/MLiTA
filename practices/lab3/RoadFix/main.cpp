#include <iostream>
#include <vector>

void fillRoad(std::istream& input, std::vector<long>& road, int countOfRoads);
void extendRoad(std::vector<long>& road, long start, long end);
void printCountOfRange(std::ostream& output, std::vector<long>& road, int countOfRepeats);

int main()
{
    int countOfRoads = 0;
    int countOfRepeats = 0;
    std::cout << "Get count of roads and count of repeats: ";
    std::cin >> countOfRoads >> countOfRepeats;

    std::vector<long> road;

    fillRoad(std::cin, road, countOfRoads);
    printCountOfRange(std::cout, road, countOfRepeats);
    return 0;
}

void fillRoad(std::istream& input, std::vector<long>& road, int countOfRoads)
{
    for (auto index = 0; index < countOfRoads; index++)
    {
        long startRange = 0;
        long endRange = 0;

        input >> startRange >> endRange;
        if (road.size() < endRange + 1)
        {
            if (road.size() < startRange + 1)
            {
                road.resize(startRange, 0);
            }
            else
            {
                extendRoad(road, startRange, (long)road.size());
            }

            road[startRange - 1]++;
            road.resize(endRange, 1);
        }
        else
        {
            extendRoad(road, startRange, endRange);
        }
    }
}

void extendRoad(std::vector<long>& road, long start, long end)
{
    for (auto index = start - 1; index < end; index++)
    {
        road[index]++;
    }
}

void printCountOfRange(std::ostream& output, std::vector<long>& road, int countOfRepeats)
{
    long count = 0;
    bool needPair = false;
    bool needSum = false;

    for (auto element : road )
    {
        if (element >= countOfRepeats && needPair)
        {
            if (needSum)
            {
                count++;
                needSum = false;
            }

            continue;
        }

        if (element >= countOfRepeats && !needPair)
        {
            needPair = true;
            needSum = true;

            continue;
        }

        if (element < countOfRepeats)
        {
            needPair = false;
            needSum = false;
        }
    }

    output << count << std::endl;
}