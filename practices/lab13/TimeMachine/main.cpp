#include <iostream>
#include <vector>
#include <limits>

void checkSequence(std::ostream& output, unsigned long long number);
std::string getBinaryString(unsigned long long number);

int main()
{
    unsigned long long number;
    std::cin >> number;

    checkSequence(std::cout, number);
    return 0;
}

void checkSequence(std::ostream& output, unsigned long long number)
{
    if (number % 2 == 0)
    {
        output << "NO";
        return;
    }

    std::string binaryString = getBinaryString(number);
    output << (binaryString.size() - 1) << std::endl;
    for (int index = 0; index < binaryString.size() - 1; ++index)
    {
        if (binaryString[index] == '1')
        {
            output << 2 << " ";
        }
        if (binaryString[index] == '0')
        {
            output << 1 << " ";
        }
    }
}

std::string getBinaryString(unsigned long long int number)
{
    std::string binaryCode;

    binaryCode.reserve(std::numeric_limits<unsigned int>::digits);

    do
    {
        binaryCode += char('0' + number % 2);
        number = number / 2;
    } while (number > 0);

    std::reverse(binaryCode.begin(), binaryCode.end());
    return binaryCode;
}