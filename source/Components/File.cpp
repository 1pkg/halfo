#include "include.hpp"
#include "File.hpp"

namespace Components
{

void
File::initialize()
{
	cocos2d::FileUtils::getInstance()->removeDirectory(cache());
	directory(cache());
}

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
	std::string path = "";
    for (unsigned i = 0; i < CACHE_FILENAME_SIZE; ++i)
       path += CACHE_FILENAME_CHARSET[cocos2d::RandomHelper::random_int<unsigned int>(0, (sizeof(CACHE_FILENAME_CHARSET) - 1))];
	path = cache() + path + TRUE_FILE_EXTENSION;
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

}