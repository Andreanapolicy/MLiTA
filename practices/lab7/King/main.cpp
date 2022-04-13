#include <iostream>
#include <vector>

void runKingPassing(std::istream& input, std::ostream& output, int variationCount);

int main()
{
    int variationCount = 0;
    std::cin >> variationCount;

    runKingPassing(std::cin, std::cout, variationCount);
    return 0;
}

void runKingPassing(std::istream& input, std::ostream& output, int variationCount)
{
    for (auto index = 0; index < variationCount; index++)
    {
        int x = 0;
        int y = 0;

        input >> x;
        input >> y;

        if (x % 2 != 0 && y % 2 != 0)
        {
            output << 2 << std::endl;
            continue;
        }

        output << 1 << std::endl;
    }
}