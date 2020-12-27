#ifndef HIGHERGROUND_CPP_RECORDS_H
#define HIGHERGROUND_CPP_RECORDS_H
#include <SFML/Graphics.hpp>
#include <iosfwd>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

struct Top
{
    bool operator==(const Top &rhs) const;
    bool operator!=(const Top &rhs) const { return !operator==(rhs); }
    std::string name;
    int points = 0;
    int time = 0;
};

class Records {
public:
    Records(std::string Path, const int& SizeTop);
    Records() = default;
    Records(const Records&) = default;

    static std::vector<Top> top;
    static sf::Text text;
    static bool read(); // считываниеке, сразу после экземпляра
    static bool write(const std::string &name, const int &point, const int &time); // запись в файл
    static bool isRecord(const int& point); // после него write
    static void makeView(int charSize, sf::Font& font, sf::Color color); // выводит
private:
    static bool write(); // вспомогательная
    static std::string makeSpace(const int& count);
    static std::string path;
    static Top defaultResult;
    static int sizeTop;
};


#endif //HIGHERGROUND_CPP_RECORDS_H
