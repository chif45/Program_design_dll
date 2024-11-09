#include <iostream>
#include <Windows.h>
#include <list>
#include <fstream>
#include <locale.h>
#include "..\DLL_OpenCloseFiles\OpenCloseF.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RUS");

    /*
    if (argc < 2) {
        return 1;
    }
    */

    std::list<std::string> titles, paragraphs, boldTexts;

    HINSTANCE loadSearch;

    loadSearch = LoadLibrary("DLLSearch.dll");

    if (!loadSearch) {
        std::cerr << "Ошибка при загрузке DLL" << std::endl;
        return 1;
    }

    typedef std::list<std::string> (*extract) (const std::string&);
    typedef void (*printe) (const std::list<std::string>&, const std::string&);

    extract extractTitles = (extract)GetProcAddress(loadSearch, "ExtractTitles");
    extract extractParagraphs = (extract)GetProcAddress(loadSearch, "ExtractParagraphs");
    extract extractBoldText = (extract)GetProcAddress(loadSearch, "ExtractBoldTexts");
    printe printelem = (printe)GetProcAddress(loadSearch, "printElements");

    //std::string path = argv[1];
    std::string path = "D:\\3курс\\ПТППОВС\\2лаба\\Laba2\\x64\\Debug\\laba1.html";
    try {
        std::ifstream* file = OpenFiles(path);
        if (file == nullptr) {
            std::cerr << "Ошибка при открытии файла: " << path << std::endl;
            return 1;
        }
    }
    catch (std::runtime_error) {
        printf("Данного файла не существует");
        return 1;
    }

    std::ifstream* file = OpenFiles(path);

    std::string content((std::istreambuf_iterator<char>(*file)), std::istreambuf_iterator<char>());

    CloseFiles(file);

    std::list<std::string>Titles = extractTitles(content);
    std::list<std::string>Paragraphs = extractParagraphs(content);
    std::list<std::string>BoldTexts = extractBoldText(content);

    try {
        printelem(Titles, "Заголовки");
    }
    catch (...) {
        std::cout << "Неудалось вывести заголовки"<<std::endl;
    }

    printelem(Paragraphs, "Абзацы");
    printelem(BoldTexts, "Жирный текст");;

    FreeLibrary(loadSearch);
}