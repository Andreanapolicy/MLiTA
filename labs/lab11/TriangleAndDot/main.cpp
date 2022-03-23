/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 11.1
 * ===============================================================
 * В декартовой системе координат на плоскости заданы координаты
 * вершин треугольника и еще одной точки. Определить, принадлежит
 * ли эта точка треугольнику.
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Linux, Ubuntu 20.04
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <fstream>
#include <iostream>
#include <cmath>

struct Point
{
    int x = 0;
    int y = 0;
};

void InitFiles(std::ifstream& input, std::ofstream& output);
std::string WhereIsDotRelativeTriangle(const Point& dot, const Point& firstVertex, const Point& secondVertex, const Point& thirdVertex);
double GetTriangleArea(const Point& firstVertex, const Point& secondVertex, const Point& thirdVertex);

int main()
{
    std::ifstream input;
    std::ofstream output;

    try
    {
        Point dot;
        Point firstVertex;
        Point secondVertex;
        Point thirdVertex;

        InitFiles(input, output);
        input >> firstVertex.x >> firstVertex.y;
        input >> secondVertex.x >> secondVertex.y;
        input >> thirdVertex.x >> thirdVertex.y;
        input >> dot.x >> dot.y;

        output << WhereIsDotRelativeTriangle(dot, firstVertex, secondVertex, thirdVertex) << std::endl;
        if (!output.flush())
        {
            throw std::runtime_error("Error, can't flush output");
        }

        output.close();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return 1;
    }

    return 0;
}

void InitFiles(std::ifstream& input, std::ofstream& output)
{
    const std::string INPUT_FILE_NAME = "INPUT.TXT";
    const std::string OUTPUT_FILE_NAME = "OUTPUT.txt";

    input.open(INPUT_FILE_NAME, std::ios_base::in);
    output.open(OUTPUT_FILE_NAME, std::ios_base::out);
    if (!input.is_open())
    {
        throw std::invalid_argument("Error, can't open INPUT.TXT");
    }

    if (!output.is_open())
    {
        throw std::invalid_argument("Error, can't open OUTPUT.TXT");
    }
}

std::string WhereIsDotRelativeTriangle(const Point& dot, const Point& firstVertex, const Point& secondVertex, const Point& thirdVertex)
{
    double triangleArea = GetTriangleArea(firstVertex, secondVertex, thirdVertex);
    double tempFirstTriangleArea = GetTriangleArea(dot, secondVertex, thirdVertex);
    double tempSecondTriangleArea = GetTriangleArea(firstVertex, dot, thirdVertex);
    double tempThirdTriangleArea = GetTriangleArea(firstVertex, secondVertex, dot);

    if (tempFirstTriangleArea + tempSecondTriangleArea + tempThirdTriangleArea <= triangleArea)
    {
        return "In";
    }

    return "Out";
}

double GetTriangleArea(const Point& firstVertex, const Point& secondVertex, const Point& thirdVertex)
{
    auto firstSide = sqrt(pow((secondVertex.x - firstVertex.x), 2) + pow((secondVertex.y - firstVertex.y), 2));
    auto secondSide = sqrt(pow((thirdVertex.x - secondVertex.x), 2) + pow((thirdVertex.y - secondVertex.y), 2));
    auto thirdSide = sqrt(pow((firstVertex.x - thirdVertex.x), 2) + pow((firstVertex.y - thirdVertex.y), 2));

    auto p = (thirdSide + secondSide + firstSide) / 2;

    return sqrt(p * (p - firstSide) * (p - secondSide) * (p - thirdSide));
}
