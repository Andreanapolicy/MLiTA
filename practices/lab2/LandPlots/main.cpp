#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <climits>

using Store = std::map<int, std::pair<int, std::string>>;

void calculateMinNumberOfArea(int landArea);
int getCountOfAreas(int landArea, Store& store);

int main()
{
    int landArea = 0;
    std::cout << "Land area: ";
    std::cin >> landArea;

    if (landArea >= 100000)
    {
        std::cout << "Wrong number" << std::endl;

        return 0;
    }
    calculateMinNumberOfArea(landArea);
    return 0;
}

void calculateMinNumberOfArea(int landArea)
{
    Store landStore;

    int countOfAreas = getCountOfAreas(landArea, landStore);
    std::cout << countOfAreas << std::endl;
//    std:: cout << landStore.at(landArea).second << std::endl;
}

int getCountOfAreas(int landArea, Store& store)
{
    auto storedCountOfAreasForLand = store.find(landArea);
    if (storedCountOfAreasForLand != store.end())
    {
        return storedCountOfAreasForLand->first;
    }

    if (landArea < 2)
    {
        store.emplace(landArea, std::pair<int, std::string>(1, std::to_string(landArea)));

        return landArea;
    }

    if ((int) (std::sqrt(landArea)) * (int) (std::sqrt(landArea)) == landArea)
    {
        store.emplace(landArea, std::pair<int, std::string>(1, std::to_string(landArea)));

        return 1;
    }

    int minCountOfAreas = INT_MAX;
    int nearestRoot = (int) (std::sqrt(landArea)) * (int) (std::sqrt(landArea));
    for (auto index = landArea - nearestRoot; index < landArea; index++)
    {
        int newCountOfAreas = 0;

        auto storedCountOfAreas = store.find(landArea - index);
        if (storedCountOfAreas == store.end())
        {
            newCountOfAreas += getCountOfAreas(landArea - index, store);
        }
        else
        {
            newCountOfAreas += storedCountOfAreas->second.first;
        }

        auto storedCountOfIndex = store.find(index);
        if (storedCountOfIndex == store.end())
        {
            newCountOfAreas += getCountOfAreas(index, store);
        }
        else
        {
            newCountOfAreas += storedCountOfIndex->second.first;
        }

        if (newCountOfAreas < minCountOfAreas && newCountOfAreas != 0)
        {
            minCountOfAreas = newCountOfAreas;
            store[landArea] = std::pair<int, std::string>{minCountOfAreas, ""};
        }
    }

    return minCountOfAreas;
}
