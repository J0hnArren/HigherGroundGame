#ifndef FILESBANK_H
#define FILESBANK_H
#include <iosfwd>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

class FilesBank
{
public:
	static FilesBank& getInstance();
	void AddFiles(const std::string& fileType, const std::string& fileName) noexcept(false);
    void AddSounds(const std::string& fileType, const std::string& fileName) noexcept(false);
    sf::Texture* GetFile(const std::string& fileType, const int &fileNumber);
    sf::SoundBuffer* getSounds(const std::string& fileType, const int &musicNumber);
private:
	FilesBank() = default;
	FilesBank(const FilesBank&) = delete;
	~FilesBank() = default;
	FilesBank& operator=(FilesBank const&) = delete;

    std::map<std::string, std::vector<sf::Texture>> singletonTextures;
    std::map<std::string, std::vector<sf::SoundBuffer>> sounds;

	static void FileFormatCheck(const std::string& fileName);
	static void FileTypeCheck(const std::string &ST_FileType);
    static void SoundTypeCheck(const std::string &ST_FileType);
    static void FileLoadCheck(const std::string& fileName);

	sf::Texture texture;
    sf::SoundBuffer sound;
};

#endif // !FILESBANK