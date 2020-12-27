#include "Records.h"

#include <utility>

bool Top::operator==(const Top &rhs) const {
    return (name == rhs.name && points == rhs.points && time == rhs.time);
}

Records::Records(std::string Path, const int& SizeTop){
    path = std::move(Path);
    sizeTop = SizeTop;
    defaultResult = {"", 0, 0};
}

void Records::makeView(int charSize, sf::Font& font, sf::Color color) {
    text.setFont(font);
    text.setFillColor(color);
    text.setCharacterSize(charSize);
    int lName = 0, lPoint = 0, lTime = 0;
    const int countSpace = 4;
    std::string title, name, points, time;
    title = "RECORDS"; name = "NAME"; points = "POINTS"; time = "TIME";
    int minName = name.length();
    int minPoint = points.length();
    int minTime = time.length();
    int titleLength = title.length();
    int minLength = minName + minPoint + minTime + countSpace;
    for (const auto & i : top) {
        if (i.name.length() > lName)
            lName = i.name.length();

        if (std::to_string(i.points).length() > lPoint)
            lPoint = std::to_string(i.points).length();

        if (std::to_string(i.time).length() > lTime)
            lTime = std::to_string(i.time).length();
    }

    int totalLength = lName + lPoint + lTime + countSpace;
    if (totalLength <= minLength)
        totalLength = minLength;

    if (lName <= minName)
        lName = minName;

    if (lPoint <= minPoint)
        lPoint = minPoint;

    std::string str;
    std::stringstream stream;
    stream << makeSpace(totalLength / 2 - titleLength / 2) << title << "\n";

    stream << makeSpace(2) << name << makeSpace(1 + lName - minName) <<
    points << makeSpace(1 + lPoint - minPoint) << time << "\n";

    if(top[0] != defaultResult)
        for (ptrdiff_t i = 0; i < top.size(); i++) {
            stream << std::to_string(i + 1) << makeSpace(1) << top[i].name <<
            makeSpace(lName - int(top[i].name.length() + 1)) << std::to_string(top[i].points) <<
            makeSpace(lPoint - int(std::to_string(top[i].points).length() + 1)) << std::to_string(top[i].time);
            if (i != top.size() - 1)
                stream << "\n";
        }
    str = stream.str();
    text.setString(str);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
}

bool Records::read() {
    std::string line, name;
    std::ifstream reader(path);
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
        return lhs.points > rhs.points;
    });
    if(top.size() > sizeTop)
        top.pop_back();
    return write();
}

bool Records::write() {
    std::ofstream writer(path);
    std::stringstream stream;
    if (writer.is_open()) {
        writer.clear();
        for (const Top& i : top) {
            stream << i.name << " " << i.points << " " << i.time << '\n';
        }
        writer << stream.str();
        writer.close();
        return true;
    }
    return false;
}


bool Records::isRecord(const int& point) {
    for (const Top& i : top) {
        if (i.points < point)
            return true;
    }
    return false;
}

std::string Records::makeSpace(const int& count) {
    std::string str;
    for (ptrdiff_t i = 0; i < count; i++) {
        str += " ";
    }
    return str;
}
