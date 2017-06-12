#include "include.hpp"

template <>
std::string to_string(cocos2d::Vec2 value)
{
	return "(" + to_string(value.x) + ";" + to_string(value.y) + ")";
}

template <>
std::string to_string(cocos2d::Line value)
{
	return "Line:\n" + to_string(value.first) + "\n" + to_string(value.second);
}

template <>
std::string to_string(cocos2d::Polygon value)
{
	std::ostringstream stream;
	stream << "Polygon:\n";
	for (cocos2d::Vec2 point : value)
		stream << to_string(point) << "\n";
	stream << "Area: " << area(value);
	return stream.str();
}

std::string replace(const std::string & string, const std::string & search, const std::string & replace)
{
	std::string result = string;
    while(1)
	{
        std::size_t position = result.find(search);
        if(position == std::string::npos)
			break;
        result.erase(position, search.length());
        result.insert(position, replace);
    }
	return result;
}

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

float area(const cocos2d::Polygon & polygon)
{
	float result = 0.0f;
	for (std::size_t i = 0; i < polygon.size(); ++i)
	{
		cocos2d::Vec2 first = polygon.at(i);
		cocos2d::Vec2 second = polygon.at((i == polygon.size() - 1 ? 0 : i + 1));
		result += first.x * second.y - first.y * second.x;
	}
	return abs(result / 2.0f);
}

Result::Result()
{
	this->slices = this->time = this->mass = 0;
}

Result::Result(unsigned int slices, unsigned int time, unsigned int mass)
{
	this->slices = slices, this->time = time, this->mass = mass;
}

bool
Result::operator<(const Result & result) const
{
	return slices < result.slices;
}

bool
Result::empty() const
{
	return slices == 0 && time == 0 && mass == 0;
}