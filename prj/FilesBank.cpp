#include "FilesBank.h"

void FilesBank::AddTexture(const std::string& fileType, const std::string& fileName) noexcept(false){
    try {
        FileTypeCheck(fileType);
        FileFormatCheck(fileName);
        if (!texture.loadFromFile("src/images/" + fileName)) {
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
        std::cout << "Something went wrong with in FilesBank::AddTexture()" << "\n";
    }

    FilesBank::getInstance().singletonTextures[fileType];
    FilesBank::getInstance().singletonTextures[fileType].push_back(texture);
}

FilesBank& FilesBank::getInstance() {
	static FilesBank instance;
	return instance;
}

void FilesBank::FileFormatCheck(const std::string& fileName) {
	int size = fileName.size();
	std::string fileFormat = fileName;
	fileFormat.erase(0, size - 3);

	if (fileFormat != "png" && fileFormat != "jpg") {
		throw std::invalid_argument("Wrong file format! Added file format: " + fileFormat);
	}
}

void FilesBank::FileTypeCheck(const std::string &ST_FileType){
    if (ST_FileType != "player" && ST_FileType != "bg" && ST_FileType != "platform"){
        throw std::invalid_argument(
                "Wrong type for singletonTextures!"
                "\nIt can contain only 'player', 'bg' and 'platform'."
                "\nYou added: " + ST_FileType + ". Check for the typo."
                );
    }
}

void FilesBank::FileLoadCheck(const std::string& fileName){
    throw std::runtime_error("Could not load from file: " + fileName);
}