#ifndef TEXTUREBANK_H
#define TEXTUREBANK_H
#include <iosfwd>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

class TextureBank
{
public:
	static TextureBank& getInstance();
	void AddTexture(const std::string& fileType, const std::string& fileName) noexcept(false);
	std::map<std::string, std::vector<sf::Texture>> singletonTextures;
private:
	TextureBank() = default;
	TextureBank(const TextureBank&) = delete;
	~TextureBank() = default;
	TextureBank& operator=(TextureBank const&) = delete;

	static void FileFormatCheck(const std::string& fileName);
	static void FileTypeCheck(const std::string &ST_FileType);
    static void FileLoadCheck(const std::string& fileName);

	sf::Texture texture;
};

#endif // !TEXTUREBANK