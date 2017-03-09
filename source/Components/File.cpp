#include "File.hpp"

namespace Components
{

void
File::initialize()
{
	cocos2d::FileUtils::getInstance()->setSearchPaths(std::vector<std::string>{
		cocos2d::FileUtils::getInstance()->getWritablePath(),
		"assets"
	});
}

void
File::finitialize()
{
	for (const std::string & file : _files)
		remove(file);
}

cocos2d::Data
File::read(const std::string & from) const
{
	return cocos2d::FileUtils::getInstance()->getDataFromFile(from);
}

std::string
File::write(const cocos2d::Data & data, const std::string & to)
{
	std::string directory = cocos2d::FileUtils::getInstance()->getWritablePath();
	if (to.length() == 0)
	{
		std::string path = directory + "/" + unique(0x10) + ".ev";
		cocos2d::FileUtils::getInstance()->writeDataToFile(data, path);
		_files.push_back(path);
		return path;
	}
	std::string path = directory + "/" + to;
	cocos2d::FileUtils::getInstance()->writeDataToFile(data, path);
	return path;
}

bool
File::exist(const std::string & from) const
{
	return cocos2d::FileUtils::getInstance()->isFileExist(from);
}

void
File::remove(const std::string & from)
{
	cocos2d::FileUtils::getInstance()->removeFile(from);
}

void
File::move(const std::string & from, const std::string & to)
{
	cocos2d::Data data = read(from);
	write(data, to);
}

std::string
File::unique(std::size_t size) const
{
	static const char CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string unique = "";
    for (unsigned i = 0; i < size; ++i)
       unique += CHARS[cocos2d::RandomHelper::random_int<unsigned int>(0, (sizeof(CHARS) - 1))];
	return unique;
}

}