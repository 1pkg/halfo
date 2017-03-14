#include "include.hpp"

std::string hash(const cocos2d::Data & data)
{
	if (data.isNull())
		return "";

	std::stringstream stream;
	std::size_t size = data.getSize();
	unsigned char * buffer = data.getBytes();
	for (std::size_t i = 0; i < size; i += 0x8)
		stream << std::hex << ((size ^ buffer[i]) % 0xF);

	std::function<std::string(const std::string &)> hashpad =
	[&](const std::string & hash)
	{
		std::stringstream stream;
		std::size_t size = hash.size();
		stream << hash;
		for (std::size_t i = 0; i < size / 2; ++i)
		{
			stream << std::hex << ((hash[i] ^ hash[size - 1 - i]) % 0xF);
			if (size + i == HASH_SIZE)
 				break;
		}

		std::string phash = stream.str();
		if (phash.length() < HASH_SIZE)
 			return hashpad(phash);
		return phash;
	};

	std::function<std::string(const std::string &)> hashtrim =
	[&](const std::string & hash)
	{
		std::stringstream stream;
		std::size_t size = hash.size();
		for (std::size_t i = 0; i < size / 2; ++i)
		{
			if (size - i == HASH_SIZE)
			{
				std::string thash = stream.str();
				stream << hash.substr(i, 0x10 - i);
				std::string thash1 = stream.str();
				break;
			}
			stream << std::hex << ((hash[i] ^ hash[size - 1 - i]) % 0xF);
		}

		std::string thash = stream.str();
		if (thash.length() > HASH_SIZE)
 			return hashtrim(thash);
		return thash;
	};

	std::string hash = stream.str();
	if (hash.length() > HASH_SIZE)
		return hashtrim(hash);
	if (hash.length() < HASH_SIZE)
		return hashpad(hash);
	return hash;
}