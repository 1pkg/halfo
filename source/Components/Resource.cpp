#include "constants.hpp"
#include "File.hpp"
#include "Crypto.hpp"
#include "Resource.hpp"
#include <json/document.h>

namespace Components
{

void
Resource::initialize()
{
	cocos2d::Data data = Master::instance().get<File>().read(Master::instance().get<File>().storage() + "rc" + TRUE_FILE_EXTENSION);
	data = Master::instance().get<Crypto>().decrypt(data, CRYPTO_STORAGE_BLOCK);
	unserialize(data);
}

const cocos2d::Data &
Resource::get(const std::string & resource, Type type)
{
	static cocos2d::Data data;
	std::unordered_map<std::pair<std::string, Type>, cocos2d::Data, unorderedhash>::const_iterator it = _resources.find(std::pair<std::string, Type>(resource, type));
	if (it != _resources.end())
		return it->second;

	return data;
}

void
Resource::walk(Type type, std::function<bool(const std::string &, const cocos2d::Data &)> callback)
{
	for(std::unordered_map<std::pair<std::string, Type>, cocos2d::Data, unorderedhash>::const_iterator it = _resources.begin(); it != _resources.end(); ++it)
		if (it->first.second == type)
			if(!callback(it->first.first, it->second))
				return;
}

void
Resource::unserialize(const cocos2d::Data & data)
{
	using namespace rapidjson;
	Document document;
	document.Parse<kParseNoFlags>((char *)data.getBytes(), data.getSize());
	if (document.HasParseError())
		return;

	for (Value::ConstValueIterator it = document["resources"].Begin(); it != document["resources"].End(); ++it)
	{
		std::string origin = (*it)["origin"].GetString();
		Type type = (Type)(*it)["type"].GetUint();
		std::string resource = (*it)["resource"].GetString();
		std::string hsh = (*it)["hash"].GetString();
		cocos2d::Data data = Master::instance().get<File>().read(Master::instance().get<File>().assets() + resource + TRUE_FILE_EXTENSION);
		data = Master::instance().get<Crypto>().decrypt(data, CRYPTO_RESOURCE_BLOCK);
		if (hash(data) == hsh)
			_resources.insert(std::pair<std::pair<std::string, Type>, cocos2d::Data>(std::pair<std::string, Type>(origin,type), data));
	}
}

}