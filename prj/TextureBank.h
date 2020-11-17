#ifndef TEXTUREBANK_H
#define TEXTUREBANK_H
#include <iosfwd>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

// __declspec(selectany) - the linker must select one definition for use by all external links and discard the others
//__declspec(selectany) std::map<std::string, std::vector<sf::Texture>> textureList;

class TextureBank
{
public:
	static TextureBank& getInstance();
	void AddTexture(const std::string& fileType, const std::string& fileName) noexcept(false);
	std::map<std::string, std::vector<sf::Texture>> singletonTextures;
private:
	TextureBank() = default;
	TextureBank(const TextureBank&) = delete;
	TextureBank(const std::string & FileName);
	TextureBank(const std::string & FileType, const std::string & FileName);
	~TextureBank() = default;
	TextureBank& operator=(TextureBank const&) = delete;

	void CheckFileFormat(const std::string& fileName);
	bool isChecked = false;

	std::string FileName;
	std::string FileType;

	sf::Texture texture;
};

#endif // !TEXTUREBANK