/*
 * Программа была написана Дудиным Андреем, студентом группы ПС-21
 * Задание 4.5
 * ===============================================================
 * Дана матрица N × N, заполненная целыми положительными числами.
 * Путь по матрице начинается в левом верхнем углу. За один ход
 * можно пройти в соседнюю по вертикали или горизонтали клетку
 * (если она существует). Нельзя ходить по диагонали, нельзя
 * оставаться на месте. Требуется найти максимальную сумму
 * чисел, стоящих в клетках по пути длиной K клеток (клетку
 * можно посещать несколько раз).
 * ===============================================================
 * Версия c++: 20
 * Компиляторы: gcc(9.3.0), g++(9.3.0)
 * ОС: Linux, Ubuntu 20.04
 * Доподнительно: сборка происходила через gnu make(4.2.1)
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using Matrix = std::vector<std::pair<std::vector<int>, int>>;
using Point = std::pair<int, int>;
using LoggedRecord = std::vector<Matrix>;

void initFiles(std::ifstream& input, std::ofstream& output);
void initMatrix(Matrix& matrix, int width);
void fillMatrix(Matrix& matrix, std::istream& input);
void countMaxRoute(Matrix&matrix, int stepsToTarget, std::ostream& output);
void processPoint(Matrix& matrix, Matrix& current, Matrix& previous, std::queue<Point>& queue, Point& originalPoint, Point& point);
void clearQueue(std::queue<Point>& queue);
std::vector<Point> getRoutes(const LoggedRecord& records, const Point& startPoint);
void writeRoutes(std::ostream& output, const std::vector<Point>& records);

int main()
{
    std::ifstream input;
    std::ofstream output;
    Matrix matrix;

    try
    {
        int size = 0;
        int stepsToTarget = 0;
        initFiles(input, output);

        input >> size >> stepsToTarget;
        if (size < 2 || size > 20)
        {
            throw std::invalid_argument("Error, size should be in range 2 .. 20");
        }

        if (stepsToTarget < 0 || stepsToTarget > 20)
        {
            throw std::invalid_argument("Error, steps to target should be in range 1 .. 20");
        }

        initMatrix(matrix, size);
        fillMatrix(matrix, input);
        countMaxRoute(matrix, stepsToTarget, output);
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

void initFiles(std::ifstream& input, std::ofstream& output)
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

void initMatrix(Matrix& matrix, int width)
{
    for (auto indexHeight = 0; indexHeight < width; indexHeight++)
    {
        matrix.push_back(std::pair<std::vector<int>, int>({}, indexHeight));

        for (auto indexWidth = 0; indexWidth < width; indexWidth++)
        {
            matrix.at(indexHeight).first.push_back(0);
        }
    }
}

void fillMatrix(Matrix& matrix, std::istream& input)
{
    for (auto indexHeight = 0; indexHeight < matrix.size(); indexHeight++)
    {
        for (auto indexWidth = 0; indexWidth < matrix.size(); indexWidth++)
        {
            input >> matrix.at(indexHeight).first.at(indexWidth);
        }
    }
}

void countMaxRoute(Matrix& matrix, int stepsToTarget, std::ostream& output)
{
    LoggedRecord records;
    Matrix firstStep;
    initMatrix(firstStep, matrix.size());
    firstStep.at(0).first.at(0) = 1;
    records.push_back(firstStep);

    std::queue<Point> queue;
    std::queue<Point> nextQueue;
    Matrix current;
    initMatrix(current, matrix.size());
    Matrix previous;
    initMatrix(previous, matrix.size());

    queue.push(Point(0, 0));

    for (auto index = 0; index < stepsToTarget - 1; index++)
    {
        while (!queue.empty())
        {
            Point startPoint = queue.front();
            queue.pop();

            if (startPoint.first - 1 > 0)
            {
                Point topPoint = Point(startPoint.first - 1, startPoint.second);
                processPoint(matrix, current, previous, nextQueue, startPoint, topPoint);
            }

            if (startPoint.first + 1 < matrix.size())
            {
                Point bottomPoint = Point(startPoint.first + 1, startPoint.second);
                processPoint(matrix, current, previous, nextQueue, startPoint, bottomPoint);
            }

            if (startPoint.second + 1 < matrix.size())
            {
                Point rightPoint = Point(startPoint.first, startPoint.second + 1);
                processPoint(matrix, current, previous, nextQueue, startPoint, rightPoint);
            }

            if (startPoint.second - 1 > 0)
            {
                Point leftPoint = Point(startPoint.first, startPoint.second - 1);
                processPoint(matrix, current, previous, nextQueue, startPoint, leftPoint);
            }
        }

        records.push_back(current);
        queue = nextQueue;
        clearQueue(nextQueue);
        previous = std::move(current);

        initMatrix(current, matrix.size());
    }

    int result = previous.at(0).first.at(0);
    Point maxValue;

    for (auto indexI = 0; indexI < matrix.size(); indexI++)
    {
        for (auto indexJ = 0; indexJ < matrix.size(); indexJ++)
        {
            if (result < previous.at(indexI).first.at(indexJ))
            {
                result = previous.at(indexI).first.at(indexJ);
                maxValue = {indexI, indexJ};
            }
        }
    }

    output << result + matrix.at(0).first.at(0) << std::endl;

    auto routes = getRoutes(records, maxValue);
    writeRoutes(output, routes);
}

void processPoint(Matrix& matrix, Matrix& current, Matrix& previous, std::queue<Point>& queue, Point& originalPoint, Point& point)
{
    if (current.at(point.first).first.at(point.second) == 0)
    {
        queue.push(std::pair<int, int>(point.first, point.second));
    }

    current.at(point.first).first.at(point.second) =
            std::max(
                    current.at(point.first).first.at(point.second),
                    previous.at(originalPoint.first).first.at(originalPoint.second)
                    + matrix.at(point.first).first.at(point.second)
            );
}

void clearQueue(std::queue<Point>& queue)
{
    while (!queue.empty())
    {
        queue.pop();
    }
}

std::vector<Point> getRoutes(const LoggedRecord& records, const Point& startPoint)
{
    Point point = startPoint;
    std::vector<Point> points;
    points.push_back(point);

    for (int index = records.size() - 2; index >= 0; index--)
    {
        std::vector<Point> pointForFurtherMovement;

        if (point.first - 1 >= 0)
        {
            pointForFurtherMovement.emplace_back(point.first - 1, point.second);
        }

        if (point.first + 1 < records[index].size() - 1)
        {
            pointForFurtherMovement.emplace_back(point.first + 1, point.second);
        }

        if (point.second + 1 < records[index].size() - 1)
        {
            pointForFurtherMovement.emplace_back(point.first, point.second + 1);
        }

        if (point.second - 1 >= 0)
        {
            pointForFurtherMovement.emplace_back(point.first, point.second - 1);
        }

        auto maxPointForMovement = std::max_element(pointForFurtherMovement.begin(), pointForFurtherMovement.end(),
                         [&records, index](const Point& first, const Point& second)
                         { return records[index].at(first.first).first.at(first.second) <= records[index].at(second.first).first.at(second.second); });

        point = *maxPointForMovement;
        points.push_back(point);
    }

    return points;
}

void writeRoutes(std::ostream& output, const std::vector<Point>& records)
{
    for (int index = records.size() - 1; index >= 0; index--)
    {
        output << records[index].first + 1 << ' ' << records[index].second + 1 << std::endl;
    }
}
