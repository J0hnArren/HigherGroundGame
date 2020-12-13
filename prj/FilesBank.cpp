#include "FilesBank.h"

void FilesBank::AddFiles(const std::string& fileType, const std::string& fileName) noexcept(false){
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
        std::cout << "Something went wrong in FilesBank.cpp FilesBank::AddFiles()" << "\n";
    }

    FilesBank::getInstance().singletonTextures[fileType];
    FilesBank::getInstance().singletonTextures[fileType].push_back(texture);
}

sf::Texture* FilesBank::GetFile(const std::string& fileType, const int &fileNumber){
    return &singletonTextures[fileType][fileNumber];
}

void FilesBank::AddSounds(const std::string& fileType, const std::string& fileName) noexcept(false){
    try {
        SoundTypeCheck(fileType);
        FileFormatCheck(fileName);
        if (!sound.loadFromFile("src/audio/" + fileName)) {
            FileLoadCheck(fileName);
        }
    } catch (std::runtime_error &e) {
        std::cout << e.what() << "\n";
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << "\n";
    } catch (...) {
        std::cout << "Something went wrong in FilesBank.cpp FilesBank::AddSounds()" << "\n";
    }

    FilesBank::getInstance().sounds[fileType];
    FilesBank::getInstance().sounds[fileType].push_back(sound);
}

sf::SoundBuffer* FilesBank::getSounds(const std::string &fileType, const int &musicNumber){
    return &sounds[fileType][musicNumber];
}

FilesBank& FilesBank::getInstance() {
	static FilesBank instance;
	return instance;
}

void FilesBank::FileFormatCheck(const std::string& fileName) {
	int size = fileName.size();
	std::string fileFormat = fileName;
	fileFormat.erase(0, size - 3);

	if (fileFormat != "png" && fileFormat != "jpg" && fileFormat != "ogg") {
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

void FilesBank::SoundTypeCheck(const std::string &ST_FileType){
    if (ST_FileType != "jump" && ST_FileType != "trampoline"){
        throw std::invalid_argument(
                "Wrong type for singletonTextures!"
                "\nIt can contain only 'jump' or 'trampoline'."
                "\nYou added: " + ST_FileType + ". Check for the typo."
        );
    }
}

void FilesBank::FileLoadCheck(const std::string& fileName){
    throw std::runtime_error("Could not load from file: " + fileName);
}