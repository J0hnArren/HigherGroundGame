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
	void AddTexture(const std::string& fileType, const std::string& fileName) noexcept(false);
    void AddMusic(const std::string& fileName) noexcept(false);
	std::map<std::string, std::vector<sf::Texture>> singletonTextures;
    static std::vector<sf::Music> soundTracks;
private:
	FilesBank() = default;
	FilesBank(const FilesBank&) = delete;
	~FilesBank() = default;
	FilesBank& operator=(FilesBank const&) = delete;

	static void FileFormatCheck(const std::string& fileName);
	static void FileTypeCheck(const std::string &ST_FileType);
    static void FileLoadCheck(const std::string& fileName);

	sf::Texture texture;
    sf::Music music;
};

#endif // !FILESBANK