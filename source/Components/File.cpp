#include "File.hpp"

namespace Components
{

void
File::finitialize()
{
	for (const std::string & file : _files)
		remove(file);
}

std::string
File::application() const
{
	return cocos2d::FileUtils::getInstance()->getSearchPaths()[0];
}

std::string
File::root() const
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + "halfo/";
}

std::string
File::assets() const
{
	return root() + "sts/";
}

std::string
File::storage() const
{
	return root() + "str/";
}

std::string
File::cache() const
{
	return root() + "cch/";
}

cocos2d::Data
File::read(const std::string & path) const
{
	return cocos2d::FileUtils::getInstance()->getDataFromFile(path);
}

void
File::write(const cocos2d::Data & data, const std::string & path) const
{
	cocos2d::FileUtils::getInstance()->writeDataToFile(data, path);
}

std::string
File::cache(const cocos2d::Data & data)
{
	std::string path = cache() + unique(0x10) + ".ev";
	cocos2d::FileUtils::getInstance()->writeDataToFile(data, path);
	_files.push_back(path);
	return path;
}

void
File::directory(const std::string & path) const
{
	cocos2d::FileUtils::getInstance()->createDirectory(path);
}

bool
File::exist(const std::string & path) const
{
	return cocos2d::FileUtils::getInstance()->isFileExist(path);
}

void
File::remove(const std::string & path) const
{
	cocos2d::FileUtils::getInstance()->removeFile(path);
}

void
File::copy(const std::string & from, const std::string & to) const
{
	cocos2d::Data data = read(from);
	write(data, to);
}

void
File::move(const std::string & from, const std::string & to) const
{
	copy(from, to);
	remove(from);
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