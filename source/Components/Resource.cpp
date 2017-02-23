#include "Resource.hpp"
#include "Application/Main.hpp"
#include <cocos2d.h>
#include <json/document.h>
#include <json/writer.h>

namespace Components
{

Resource::Resource()
	: File(true)
{
}

void
Resource::flush() const
{
	File::flush();
	Application::Main::instance().integrity().resource(
		File::hash(path())
	);
}

void
Resource::pull()
{
	if (cocos2d::FileUtils::getInstance()->isFileExist(path())
		&& Application::Main::instance().integrity().resource() != File::hash(path())
	)
	{
		default();
		return;
	}
	File::pull();
	for (const std::pair<std::string, std::tuple<std::string, std::string>> & pair : _resources)
		if (File::hash(std::get<0>(pair.second)) != std::get<1>(pair.second))
			default();
}

cocos2d::Data
Resource::resource(const std::string & alias) const
{
	cocos2d::Data buffer =
		cocos2d::FileUtils::getInstance()->getDataFromFile(
			std::get<0>(_resources.find(alias)->second)
		);
	return std::move(buffer);
}

std::string
Resource::path() const
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + "rc.hf";
}

cocos2d::Data
Resource::serialize() const
{
	using namespace rapidjson;
    Document document(kObjectType);
	Document::AllocatorType & allocator = document.GetAllocator();

	/*
		Serialize resources.
	*/
	Value resources(kObjectType);
	for (const std::pair<std::string, std::tuple<std::string, std::string>> & pair : _resources)
	{
		Value rsc(kObjectType);
		rsc.AddMember(
			"path",
			Value(std::get<0>(pair.second).data(), allocator),
			allocator
		);
		rsc.AddMember(
			"hash",
			Value(std::get<1>(pair.second).data(), allocator),
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

	StringBuffer bufffer;
	Writer<StringBuffer> writer(bufffer);
	document.Accept(writer);
	cocos2d::Data data;
	data.copy((unsigned char *)bufffer.GetString(), bufffer.GetSize());
	return std::move(data);
}

bool
Resource::unserialize(const cocos2d::Data & buffer)
{
	using namespace rapidjson;
	Document document;
	document.Parse<kParseNoFlags>(
		(char *)buffer.getBytes(),
		buffer.getSize()
	);
	if (document.HasParseError())
		return false;

	/*
		Unserialize resources.
	*/
	for (
		Value::ConstMemberIterator it = document["resources"].MemberBegin();
		it != document["resources"].MemberEnd();
		++it
	)
	{
		std::tuple<std::string, std::string> tuple;
		for (
			Value::ConstMemberIterator nestedIt = it->value.MemberBegin();
			nestedIt != it->value.MemberEnd();
			++nestedIt
		)
		{
			if (nestedIt->name == "path")
				std::get<0>(tuple) = nestedIt->value.GetString();
			if (nestedIt->name == "hash")
				std::get<1>(tuple) = nestedIt->value.GetString();
		}
		_resources.insert(
			std::pair<
				std::string,
				std::tuple<
					std::string,
					std::string
				>
			>(it->name.GetString(), tuple)
		);
	}
	return true;
}

void
Resource::default()
{
	_resources.clear();
}

}