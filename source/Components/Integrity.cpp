#include "Integrity.hpp"
#include <cocos2d.h>
#include <json/document.h>
#include <json/writer.h>

namespace Components
{

std::string
Integrity::path() const
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + "inr.hf";
}

void
Integrity::flush() const
{
	write();
}

void
Integrity::fetch()
{
	read();
}

Integrity::Integrity()
{
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "inr.hf";
	if (!cocos2d::FileUtils::getInstance()->isFileExist(path))
		return;

	read();

}

Integrity::~Integrity()
{
	write();
}


const std::string &
Integrity::storage() const
{
	return _storage;
}

const std::string &
Integrity::resource() const
{
	return _resource;
}

void
Integrity::storage(const std::string & storage)
{
	_storage = storage;
}

void
Integrity::resource(const std::string & resource)
{
	_resource = resource;
}

void
Integrity::write() const
{
	using namespace rapidjson;
    Document document(kObjectType);
	Document::AllocatorType & allocator =
		document.GetAllocator();
	document.AddMember(
		"sth",
		Value(_storage.data(), allocator),
		allocator
	);
	document.AddMember(
		"rch",
		Value(_resource.data(), allocator),
		allocator
	);
	
	/*
		Write to file.
	*/
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "inr.hf";
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	cocos2d::FileUtils::getInstance()->writeStringToFile(
		buffer.GetString(),
		path
	);
}

void
Integrity::read()
{
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "inr.hf";
	using namespace rapidjson;
	std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(path);
	Document document;
	document.Parse<0>(data.data());
	_storage = document["sth"].GetString();
	_resource = document["rch"].GetString();
}

}