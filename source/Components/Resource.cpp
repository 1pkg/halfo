#include "include.hpp"
#include "Resource.hpp"
#include <json/document.h>

namespace Components
{

void
Resource::initialize()
{
#ifdef RESOURCE_DEBUG
	cocos2d::Data data = Master::instance().get<File>().read(Master::instance().get<File>().storage() + "/rc.ev");
	data = Master::instance().get<Crypto>().decrypt(data, 1);
	std::vector<std::tuple<std::string, Resource::Type, std::string, std::string>> resources = unserialize(data);
	for (const std::tuple<std::string, Resource::Type, std::string, std::string> & resource : resources)
	{
		std::pair<std::string, Type> alias(std::get<0>(resource), std::get<1>(resource));
		cocos2d::Data data = fetch(Master::instance().get<File>().assets() + "/" + std::get<2>(resource), std::get<1>(resource));
		if (hash(data) == std::get<3>(resource))
			_resources.insert(std::pair<std::pair<std::string, Type>, cocos2d::Data>(alias, data));
	}
#else
	std::vector<std::pair<std::string, Type>> resources{
		std::pair<std::string, Type>("figure-deault", Type::TEXTURE),
		std::pair<std::string, Type>("hammer-deault", Type::TEXTURE),
		std::pair<std::string, Type>("hammer-deault", Type::BODY),
		std::pair<std::string, Type>("hammer-deault", Type::AUDIO),
		std::pair<std::string, Type>("hammer-deault1", Type::AUDIO),
		std::pair<std::string, Type>("font", Type::FONT)
	};
	for (const std::pair<std::string, Type> & alias : resources)
		_resources.insert(std::pair<std::pair<std::string, Type>, cocos2d::Data>(alias, fetch(Master::instance().get<File>().assets() + "/" + alias.first, alias.second)));
#endif
}

const cocos2d::Data &
Resource::get(const std::string & resource, Type type)
{
	return _resources.at(std::pair<std::string, Type>(resource, type));
}

cocos2d::Data
Resource::fetch(const std::string & resource, Type type)
{
#ifdef RESOURCE_DEBUG
	cocos2d::Data data = Master::instance().get<File>().read(resource);
	return Master::instance().get<Components::Crypto>().decrypt(data, 0x10);
#else
	std::string file = resource;
	switch (type)
	{
		case Components::Resource::Type::TEXTURE:
			file += ".png";
			break;

		case Components::Resource::Type::BODY:
			file += ".json";
			break;

		case Components::Resource::Type::AUDIO:
			file += ".wav";
			break;

		case Components::Resource::Type::FONT:
			file += ".ttf";
			break;

		default:
			break;
	}
	return Master::instance().get<File>().read(file);
#endif
}

std::vector<std::tuple<std::string, Resource::Type, std::string, std::string>>
Resource::unserialize(const cocos2d::Data & data)
{
	std::vector<std::tuple<std::string, Type, std::string, std::string>> resources;
	using namespace rapidjson;
	Document document;
	document.Parse<kParseNoFlags>((char *)data.getBytes(), data.getSize());
	if (document.HasParseError())
		return resources;

	for (Value::ConstValueIterator it = document["resources"].Begin(); it != document["resources"].End(); ++it)
	{
		std::tuple<std::string, Type, std::string, std::string> resource((*it)["origin"].GetString(), (Type)(*it)["type"].GetUint(), (*it)["resource"].GetString(), (*it)["hash"].GetString());
		resources.push_back(resource);
	}
	return resources;
}

std::string
Resource::hash(const cocos2d::Data & data)
{
	if (data.isNull())
		return "";

	std::stringstream stream;
	std::size_t size = data.getSize();
	unsigned char * buffer = data.getBytes();
	for (std::size_t i = 0; i < size; i += 0x8)
		stream << std::hex << ((size ^ buffer[i]) % 15);

	std::string hash = stream.str();
	if (hash.length() > 0x10)
		return hashtrim(hash);
	if (hash.length() < 0x10)
		return hashpad(hash);
	return hash;
}

std::string
Resource::hashpad(const std::string & hash)
{
	std::stringstream stream;
	std::size_t size = hash.size();
	stream << hash;
	for (std::size_t i = 0; i < size / 2; ++i)
	{
		stream << std::hex << ((hash[i] ^ hash[size - 1 - i]) % 0xF);
		if (size + i == 0x10)
 			break;
	}

	std::string phash = stream.str();
	if (phash.length() < 0x10)
 		return hashpad(phash);
	return phash;
}

std::string
Resource::hashtrim(const std::string & hash)
{
	std::stringstream stream;
	std::size_t size = hash.size();
	for (std::size_t i = 0; i < size / 2; ++i)
	{
		if (size - i == 0x10)
		{
			std::string thash = stream.str();
			stream << hash.substr(i, 0x10 - i);
			std::string thash1 = stream.str();
			break;
		}
		stream << std::hex << ((hash[i] ^ hash[size - 1 - i]) % 0xF);
	}

	std::string thash = stream.str();
	if (thash.length() > 0x10)
 		return hashtrim(thash);
	return thash;
}

}