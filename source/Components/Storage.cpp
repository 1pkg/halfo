#include "Storage.hpp"
#include "Application/Main.hpp"
#include <cocos2d.h>
#include <json/document.h>
#include <json/writer.h>
#include <algorithm>

namespace Components
{

std::string
Storage::path() const
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + "st.hf";
}

void
Storage::flush() const
{
	write();
}

void
Storage::fetch()
{
	read();
}

Storage::Storage()
{
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "st.hf";
	if (
		!cocos2d::FileUtils::getInstance()->isFileExist(path) ||
		Application::Main::instance().integrity().storage() != hash(path)
	)
	{
		default();
		return;
	}

	read();
}

Storage::~Storage()
{
	write();
}

bool
Storage::feature(const std::string & feature) const
{
	return _features.find(feature)->second;
}

std::string
Storage::setting(const std::string & setting) const
{
	return _settings.find(setting)->second;
}

const Storage::Result &
Storage::result(unsigned int index) const
{
	return _results.at(index);
}

unsigned int
Storage::total() const
{
	return _total;
}

void
Storage::unblock(const std::string & feature)
{
	_features.find(feature)->second = true;
}

void
Storage::change(const std::string & setting, const std::string & value)
{
	_settings.find(setting)->second = value;
}

void
Storage::update(const Storage::Result & result)
{
	++_total;
	_results.push_back(result);
	std::sort(_results.begin(), _results.end());
	if (_results.size() > RESULT_LIMIT)
		_results.pop_back();
}

void
Storage::write() const
{
	using namespace rapidjson;
    Document document(kObjectType);
	Document::AllocatorType & allocator =
		document.GetAllocator();

	/*
		Serialize features.
	*/
	Value features(kObjectType);
	for (const std::pair<std::string, bool> & pair : _features)
		features.AddMember(
			Value(pair.first.data(), allocator),
			Value(pair.second),
			allocator
		);
	document.AddMember(
		"features",
		features,
		allocator
	);

	/*
		Serialize settings.
	*/
	Value settings(kObjectType);
	for (const std::pair<std::string, std::string> & pair : _settings)
		settings.AddMember(
			Value(pair.first.data(), allocator),
			Value(pair.second.data(), allocator),
			allocator
		);
	document.AddMember(
		"settings",
		settings,
		allocator
	);

	/*
		Serialize results.
	*/
	document.AddMember(
		"total",
		Value(_total),
		allocator
	);
	Value results(kArrayType);
	for (const Result & result : _results)
	{
		Value res(kObjectType);
		res.AddMember(
			"score",
			result.score,
			allocator
		);
		res.AddMember(
			"seconds",
			result.seconds,
			allocator
		);
		res.AddMember(
			"integral",
			result.integral,
			allocator
		);
		results.PushBack(res, allocator);
	}
	document.AddMember(
		"results",
		results,
		allocator
	);
	
	/*
		Write to file.
	*/
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "st.hf";
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	cocos2d::FileUtils::getInstance()->writeStringToFile(
		buffer.GetString(),
		path
	);
	Application::Main::instance().integrity().storage(hash(path));
}

void
Storage::read()
{
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "st.hf";
	using namespace rapidjson;
	std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(path);
	Document document;
	document.Parse<0>(data.data());

	/*
		Unserialize features.
	*/
	for (
		Value::ConstMemberIterator it = document["features"].MemberBegin();
		it != document["features"].MemberEnd();
		++it
	)
		_features.insert(
			std::pair<std::string, bool>(
				it->name.GetString(),
				it->value.GetBool()
			)
		);

	/*
		Unserialize settings.
	*/
	for (
		Value::ConstMemberIterator it = document["settings"].MemberBegin();
		it != document["settings"].MemberEnd();
		++it
	)
		_settings.insert(
			std::pair<std::string, std::string>(
				it->name.GetString(),
				it->value.GetString()
			)
		);

	/*
		Unserialize results.
	*/
	_total = document["total"].GetUint();
	for (
		Value::ConstValueIterator it = document["results"].Begin();
		it != document["results"].End();
		++it
	)
	{
		Result result;
		for (
			Value::ConstMemberIterator nestedIt = it->MemberBegin();
			nestedIt != it->MemberEnd();
			++nestedIt
		)
		{
			if (nestedIt->name == "score")
				result.score = nestedIt->value.GetUint();
			if (nestedIt->name == "seconds")
				result.seconds = nestedIt->value.GetUint();
			if (nestedIt->name == "integral")
				result.integral = nestedIt->value.GetUint();
		}
		_results.push_back(result);
	}
}

void
Storage::default()
{
	_features.clear();
	_features.insert(
		std::pair<
			std::string,
			bool
		>(DISABLE_ADDS_FEATURE, false)
	);

	_settings.clear();
	_settings.insert(
		std::pair<
			std::string,
			std::string
		>(FIGURE_SKIN_SETTING, "default")
	);
	_settings.insert(
		std::pair<
			std::string,
			std::string
		>(HAMMER_SKIN_SETTING, "default")
	);

	_total = 0;
	_results.clear();
}

}