#include "Integrity.hpp"
#include <cocos2d.h>
#include <json/document.h>
#include <json/writer.h>
#include <json/memorybuffer.h>

namespace Components
{

Integrity::Integrity()
	: File(false)
{
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

std::string
Integrity::path() const
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + "gt.hf";
}

cocos2d::Data
Integrity::serialize() const
{
	using namespace rapidjson;
    Document document(kObjectType);
	Document::AllocatorType & allocator = document.GetAllocator();
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
	document.AddMember(
		"gth",
		Value(File::hash(path()).data(), allocator),
		allocator
	);

	MemoryBuffer bufffer;
	Writer<MemoryBuffer> writer(bufffer);
	document.Accept(writer);
	cocos2d::Data data;
	data.copy((unsigned char *)bufffer.GetBuffer(), bufffer.GetSize());
	return std::move(data);
}

bool
Integrity::unserialize(const cocos2d::Data & buffer)
{
	using namespace rapidjson;
	Document document;
	document.Parse<kParseNoFlags>(
		(char *)buffer.getBytes(),
		buffer.getSize()
	);
	if (document.HasParseError())
		return false;

	_storage = document["sth"].GetString();
	_resource = document["rch"].GetString();
	_self = document["gth"].GetString();

	return true;
}

}