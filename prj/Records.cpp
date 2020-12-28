#include "Records.h"

#include <utility>

bool Top::operator==(const Top &rhs) const {
    return (name == rhs.name && scores == rhs.scores && time == rhs.time);
}

Records::Records(std::string Path, const int& SizeTop)
    : path(std::move(Path)), sizeTop(SizeTop), defaultTop({"", 0, 0}){
}

sf::Text Records::ShowTable(int charSize, sf::Color color) {
    text.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    text.setFillColor(color);
    text.setCharacterSize(charSize);
    int lName = 0, lPoint = 0, lTime = 0;
    std::string name = " NAME ", points = " POINTS ", time = " TIME";
    int maxName = name.length();
    int maxPoint = points.length();
    for (const auto & i : top) {
        if (i.name.length() > lName)
            lName = i.name.length();

        if (std::to_string(i.scores).length() > lPoint)
            lPoint = std::to_string(i.scores).length();

        if (std::to_string(i.time).length() > lTime)
            lTime = std::to_string(i.time).length();
    }
    if (lName <= maxName)
        lName = maxName;

    if (lPoint <= maxPoint)
        lPoint = maxPoint;

    std::string str;
    std::stringstream stream;
    stream << AddSpace(2) << name << AddSpace(1 + lName + maxName) <<
           points << AddSpace(1 + lPoint + maxPoint) << time << "\n";

    if(top[0] != defaultTop)
        for (ptrdiff_t i = 0; i < top.size(); i++) {
            int difference = maxName - int(top[i].name.length());
            stream << std::to_string(i + 1) << AddSpace(2) << top[i].name <<
                   AddSpace(difference + int(name.size()) + 1 + lName + maxName - int(top[i].name.length() + 1)) <<
                   std::to_string(top[i].scores) <<
                   AddSpace(difference + int(points.size()) + 1 + lPoint + maxPoint - int(std::to_string(top[i].scores).length() + 1)) <<
                   std::to_string(top[i].time);

            if (i != top.size() - 1)
                stream << "\n";
        }
    str = stream.str();
    text.setString(str);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);

    return text;
}

bool Records::read() {
    top.clear();
    std::string line, name;
    std::ifstream reader(path + "data.txt");
    std::stringstream lines;
    int point = 0, time = 0;
    if (reader.is_open()) {
        // Checking for end of the file
        if (reader.peek() != EOF) {
            while (getline(reader, line)) {
                lines << line;
                lines >> name >> point >> time;
                top.push_back({ name, point, time });
                lines.clear();
            }
            reader.close();
        }
        else {
            top.push_back({"", 0, 0});
        }
        return true;
    }
    return false;
}

bool Records::write(const std::string &name, const int &point, const int &time) {
    top.push_back({ name, point, time });
    std::sort(top.begin(), top.end(), [](const Top& lhs, const Top& rhs) {
        return lhs.scores > rhs.scores;
    });
    if(top.size() > sizeTop)
        top.pop_back();
    return write();
}

bool Records::write() {
    std::ofstream writer(path + "data.txt");
    std::stringstream stream;
    if (writer.is_open()) {
        writer.clear();
        for (const Top& i : top) {
            stream << i.name << " " << i.scores << " " << i.time << '\n';
        }
        writer << stream.str();
        writer.close();
        return true;
    }
    return false;
}


bool Records::isNewRecord(const int& point, const std::string &name) {
    for (const Top& i : top) {
        if (i.scores < point && i.name != name) {
            return true; // will add new record
        }
        else if (i.scores < point && i.name == name) {
            top.erase(std::remove(top.begin(), top.end(), i), top.end());
            return true; // will add new record and erase old one
        }
        else {
            return false; // will not be added
        }
    }
    return true; // default
}

std::string Records::AddSpace(const int& count) {
    std::string str;
    for (ptrdiff_t i = 0; i < count; i++) {
        str += " ";
    }
    return str;
}