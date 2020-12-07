#include "TextureBank.h"

TextureBank& TextureBank::getInstance() {
	static TextureBank instance;
	return instance;
}

void TextureBank::FileFormatCheck(const std::string& fileName) {
	int size = fileName.size();
	std::string fileFormat = fileName;
	fileFormat.erase(0, size - 3);

	if (fileFormat != "png" && fileFormat != "jpg") {
		throw std::invalid_argument("Wrong file format! Added file format: " + fileFormat);
	}
}

void TextureBank::FileTypeCheck(const std::string &ST_FileType){
    if (ST_FileType != "player" && ST_FileType != "bg" && ST_FileType != "platform"){
        throw std::invalid_argument(
                "Wrong type for singletonTextures!"
                "\nIt can contain only 'player', 'bg' and 'platform'."
                "\nYou added: " + ST_FileType + ". Check for the typo."
                );
    }
}

void TextureBank::FileLoadCheck(const std::string& fileName){
    throw std::runtime_error("Could not load from file: " + fileName);
}

void TextureBank::AddTexture(const std::string& fileType, const std::string& fileName) noexcept(false){

    try {
        FileTypeCheck(fileType);
        FileFormatCheck(fileName);
        if (!texture.loadFromFile("../../src/images/" + fileName)) {
            FileLoadCheck(fileName);
        }
    }
    catch (std::invalid_argument &e) {
        std::cout << e.what() << "\n";
    }
    catch (std::runtime_error &e) {
        std::cout << e.what() << "\n";
    }
    catch (...) {
        std::cout << "Something went wrong with in TextureBank::AddTexture()" << "\n";
    }

    TextureBank::getInstance().singletonTextures[fileType];
    TextureBank::getInstance().singletonTextures[fileType].push_back(texture);
}