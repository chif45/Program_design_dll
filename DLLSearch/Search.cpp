#include <iostream>
#include <string>
#include <regex>
#include <list>
#include "Search.h"

class EmptyException
{
public:
    EmptyException(std::string message) : message{ message } {}
private:
    std::string message;
};

// ������� ��� ������ ���������
void printElements(const std::list<std::string>& elements, const std::string& type) {

    if (elements.empty()) {
        throw EmptyException("������ ������");
    }

    std::cout << type << ":\n";
    for (const std::string& element : elements) {
        std::cout << element << "\n";
    }
    std::cout << std::endl;
}

// ���������� ����������
std::list<std::string> ExtractTitles(const std::string& content) {
    std::list<std::string> titles;
    std::regex headerRegex("<h([1-6])>(.*?)</h\\2>");

    if (content.empty()) {
        throw std::invalid_argument("���������� ������.");
    }

    std::sregex_iterator headerBegin = std::sregex_iterator(content.begin(), content.end(), headerRegex);
    std::sregex_iterator headerEnd = std::sregex_iterator();
    for (std::sregex_iterator i = headerBegin; i != headerEnd; ++i) {
        titles.push_back((*i)[2].str());
    }

    return titles;
}

// ���������� ����������
std::list<std::string> ExtractParagraphs(const std::string& content) {
    std::list<std::string> paragraphs;
    std::regex paragraphRegex("<p>(.*?)</p>");

    if (content.empty()) {
        throw std::invalid_argument("���������� ������.");
    }

    std::sregex_iterator headerBegin = std::sregex_iterator(content.begin(), content.end(), paragraphRegex);
    std::sregex_iterator headerEnd = std::sregex_iterator();
    for (std::sregex_iterator i = headerBegin; i != headerEnd; ++i) {
        paragraphs.push_back((*i)[1].str());
    }

    return paragraphs;
}

// ���������� ������� ������
std::list<std::string> ExtractBoldTexts(const std::string& content) {
    std::list<std::string> boldTexts;
    std::regex boldTextRegex("<b>(.*?)</b>");

    if (content.empty()) {
        throw std::invalid_argument("���������� ������.");
    }

    std::sregex_iterator headerBegin = std::sregex_iterator(content.begin(), content.end(), boldTextRegex);
    std::sregex_iterator headerEnd = std::sregex_iterator();
    for (std::sregex_iterator i = headerBegin; i != headerEnd; ++i) {
        boldTexts.push_back((*i)[1].str());
    }

    return boldTexts;
}
