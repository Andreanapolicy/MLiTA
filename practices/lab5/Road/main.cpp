#include <iostream>
#include <vector>

struct Point
{
    int x;
    int y;
};

void fillPositions(std::istream& input, std::vector<Point>& positions);
int getCountOfLeftTurns(const std::vector<Point>& positions);

int main()
{
    int roadsCount = 0;
    std::cout << "Get count of roads: ";
    std::cin >> roadsCount;
    std::vector<Point> positions(roadsCount);
    fillPositions(std::cin, positions);
    std::cout << "Count of left turns: " << getCountOfLeftTurns(positions) << std::endl;
    return 0;
}

void fillPositions(std::istream& input, std::vector<Point>& positions)
{
    for (auto index = 0; index < positions.size(); index++)
    {
        input >> positions[index].x;
        input >> positions[index].y;
    }
}

int getCountOfLeftTurns(const std::vector<Point>& positions)
{
    int count = 0;
    for (auto index = 0; index < positions.size() - 2; index++)
    {
        const Point firstPoint = positions[index];
        const Point secondPoint = positions[index + 1];
        const Point thirdPoint = positions[index + 2];

        if ((secondPoint.x - firstPoint.x) * (thirdPoint.y - firstPoint.y) - (thirdPoint.x - firstPoint.x) * (secondPoint.y - firstPoint.y) > 0)
        {
            count++;
        }
    }

    return count;
}
