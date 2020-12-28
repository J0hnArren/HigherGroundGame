#ifndef HIGHERGROUND_CPP_RECORDS_H
#define HIGHERGROUND_CPP_RECORDS_H
#include <SFML/Graphics.hpp>
#include "FilesBank.h"
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
    int scores = 0;
    int time = 0;
};

class Records {
public:
    Records(std::string Path, const int& SizeTop);
    Records() = default;
    Records(const Records&) = default;

    bool read(); // reading from data.txt file
    bool isNewRecord(const int& score, const std::string &name, const int& gameTime); // if its true, we can write in file
    bool write(const std::string &name, const int &score, const int& gameTime); // write new line in file
    sf::Text ShowTable(int charSize, sf::Color color); // show table
private:
    std::vector<Top> top;
    sf::Text text;
    bool write(); // help method for bool write(const std::string &name, const int &point, const int &time)
    static std::string AddSpace(const int& count);
    std::string path;
    Top defaultTop;
    int sizeTop = 0;
};


#endif //HIGHERGROUND_CPP_RECORDS_H
