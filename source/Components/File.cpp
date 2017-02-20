#include "File.hpp"
#include <cocos2d.h>

namespace Components
{

std::string
File::hash(const std::string & file) const
{
	std::stringstream stream;
	std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(file);
	std::size_t size = data.size();
	for (std::size_t i = 0; i < size; i += STEP)
		stream << std::hex << (size ^ data[i]);

	std::string hash = stream.str();
	if (hash.length() > LIMIT)
		return trim(hash);
	if (hash.length() < LIMIT)
		return pad(hash);
	return hash;
}

std::string
File::pad(const std::string & hash) const
{
	std::stringstream stream;
	stream << hash;
	std::size_t size = hash.size();
	for (std::size_t i = 0; i < size / 2; ++i)
	{
		stream << std::hex << (hash[i] ^ hash[size - 1 - i]);
		if (size + i == LIMIT)
			break;
	}

	std::string phash = stream.str();
	if (phash.length() < LIMIT)
		return pad(phash);

	return phash;
}

std::string
File::trim(const std::string & hash) const
{
	std::stringstream stream;
	std::size_t size = hash.size();
	for (std::size_t i = 0; i < size / 2; ++i)
		stream << std::hex << (hash[i] ^ hash[size - 1 - i]);

	std::string thash = stream.str();
	if (thash.length() > LIMIT)
		return trim(thash);
	if (thash.length() < LIMIT)
		return pad(thash);

	return thash;
}

}