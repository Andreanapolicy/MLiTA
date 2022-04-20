#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

void fillDictionary(std::vector<std::string>& dictionary, std::istream& input);
void runWordSearching(const std::string& originalString, const std::vector<std::string>& dictionary, std::ostream& output);
bool isWordAvailable(const std::unordered_map<char, int>& originalParsedWord, const std::string &processedWord);
std::unordered_map<char, int> getParsedWord(const std::string& originalWord);

int main()
{
    std::string originalString;
    std::vector<std::string> dictionary;
    std::cin >> originalString;

    fillDictionary(dictionary, std::cin);
    runWordSearching(originalString, dictionary, std::cout);

    return 0;
}

void fillDictionary(std::vector<std::string>& dictionary, std::istream& input)
{
    std::string word;

    while (input >> word)
    {
        dictionary.push_back(word);
    }
}

void runWordSearching(const std::string &originalString, const std::vector<std::string> &dictionary, std::ostream &output)
{
    std::unordered_map<char, int> parsedOriginalWord = getParsedWord(originalString);
    std::vector<std::string> availableWords;
    long score = 0;

    for (const auto& element : dictionary)
    {
        if (isWordAvailable(parsedOriginalWord, element))
        {
            availableWords.push_back(element);
            score += element.length();
        }
    }

    output << score << std::endl;

    std::sort(availableWords.begin(), availableWords.end(), [](const std::string& left, const std::string& right){
        if (left.length() != right.length())
        {
            return left.length() > right.length();
        }

        return left < right;
    });

    for (const auto& element : availableWords)
    {
        output << element << std::endl;
    }
}

bool isWordAvailable(const std::unordered_map<char, int>& originalParsedWord, const std::string &processedWord)
{
    std::unordered_map<char, int> parsedWord = getParsedWord(processedWord);

    for (auto const& element : parsedWord)
    {
        auto it = originalParsedWord.find(element.first);

        if (it == originalParsedWord.end() || element.second > it->second)
        {
            return false;
        }
    }

    return true;
}

std::unordered_map<char, int> getParsedWord(const std::string &originalWord)
{
    std::unordered_map<char, int> parsedString;

    for (const auto& element : originalWord)
    {
        auto it = parsedString.find(element);
        if (it == parsedString.end())
        {
            parsedString.emplace(element, 1);
        }
        else
        {
            it->second++;
        }
    }

    return parsedString;
}
