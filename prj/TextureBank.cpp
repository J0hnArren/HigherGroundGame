#include "TextureBank.h"

TextureBank& TextureBank::getInstance() {
	static TextureBank instance;
	return instance;
}

TextureBank::TextureBank(const std::string& FileName) {
	this->FileName = FileName;

	try {
		CheckFileFormat(FileName);
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << "/n" << FileName << "/n";
	}
	isChecked = true;
	AddTexture(FileType, FileName);
}

TextureBank::TextureBank(const std::string& FileType, const std::string& FileName){
	this->FileType = FileType;
	this->FileName = FileName;

	try {
		CheckFileFormat(FileName);
	}catch (std::invalid_argument e) {
		std::cout << e.what() << "/n" << this->FileName << "/n";
	}
	isChecked = true;
	AddTexture(this->FileType, this->FileName);
}

void TextureBank::AddTexture(const std::string& fileType, const std::string& fileName) noexcept(false){

	if (!isChecked) {
		CheckFileFormat(fileName);
	}

	if (!texture.loadFromFile("C:/Users/Rauf/CLionProjects/HigherGround/src/images/" + fileName)){
        throw std::runtime_error("Could not load " + fileName);
	}
	TextureBank::getInstance().singletonTextures[fileType];
	TextureBank::getInstance().singletonTextures[fileType].push_back(texture);
}

void TextureBank::CheckFileFormat(const std::string& fileName) {
	int size = fileName.size();
	std::string fileFormat = fileName;
	fileFormat.erase(0, size - 3);

	if (fileFormat != "png" && fileFormat != "jpg") {
		throw std::invalid_argument("Wrong file format!");
	}
}