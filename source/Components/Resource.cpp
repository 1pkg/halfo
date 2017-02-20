#include "Resource.hpp"
#include "Application/Main.hpp"
#include <cocos2d.h>
#include <json/document.h>
#include <json/writer.h>

namespace Components
{

std::string
Resource::path() const
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + "rc.hf";
}

void
Resource::flush() const
{
	write();
}

void
Resource::fetch()
{
	read();
}

Resource::Resource()
{
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "rc.hf";
	if (
		!cocos2d::FileUtils::getInstance()->isFileExist(path) ||
		Application::Main::instance().integrity().resource() != hash(path)
	)
	{
		default();
		return;
	}

	read();
	for (const std::pair<std::string, Rsc> & pair : _resources)
		if (hash(pair.second.path) != pair.second.hash)
			default();

}

Resource::~Resource()
{
	write();
}

Buffer
Resource::resource(const std::string & alias) const
{
	ssize_t size;
	Buffer::byte * data =
		cocos2d::FileUtils::getInstance()->getFileData(
			_resources.find(alias)->second.path,
			nullptr,
			&size
		);

	return Buffer(data, size);
}

void
Resource::write() const
{
	using namespace rapidjson;
    Document document(kObjectType);
	Document::AllocatorType & allocator =
		document.GetAllocator();

	/*
		Serialize resources.
	*/
	Value resources(kObjectType);
	for (const std::pair<std::string, Rsc> & pair : _resources)
	{
		Value rsc(kObjectType);
		rsc.AddMember(
			"path",
			Value(pair.second.path.data(), allocator),
			allocator
		);
		rsc.AddMember(
			"hash",
			Value(pair.second.hash.data(), allocator),
			allocator
		);

		resources.AddMember(
			Value(pair.first.data(), allocator),
			rsc,
			allocator
		);
	}
	document.AddMember(
		"resources",
		resources,
		allocator
	);
	
	/*
		Write to file.
	*/
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "rc.hf";
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	cocos2d::FileUtils::getInstance()->writeStringToFile(
		buffer.GetString(),
		path
	);
	Application::Main::instance().integrity().resource(hash(path));
}

void
Resource::read()
{
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "rc.hf";
	using namespace rapidjson;
	std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(path);
	Document document;
	document.Parse<0>(data.data());

	/*
		Unserialize resources.
	*/
	for (
		Value::ConstMemberIterator it = document["resources"].MemberBegin();
		it != document["resources"].MemberEnd();
		++it
	)
	{
		Rsc rsc;
		for (
			Value::ConstMemberIterator nestedIt = it->value.MemberBegin();
			nestedIt != it->value.MemberEnd();
			++nestedIt
		)
		{
			if (nestedIt->name == "path")
				rsc.path = nestedIt->value.GetString();
			if (nestedIt->name == "hash")
				rsc.hash = nestedIt->value.GetUint();
		}
		_resources.insert(
			std::pair<
				std::string,
				Rsc
			>(it->name.GetString(), rsc)
		);
	}
}

void
Resource::default()
{
	_resources.clear();
}

}