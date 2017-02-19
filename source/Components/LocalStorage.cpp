#include "LocalStorage.hpp"
#include <cocos2d.h>
#include <json/document.h>
#include <json/writer.h>
#include <algorithm>

namespace Components
{

LocalStorage::LocalStorage()
{
	std::string has1h = hash(path());
	if (
		!cocos2d::FileUtils::getInstance()->isFileExist(path()) ||
		hash(path()) != cocos2d::UserDefault::getInstance()->getStringForKey("hash")
	)
	{
		default();
		return;
	}

	using namespace rapidjson;
	std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(path());
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
		Unserialize scores.
	*/
	_total = document["total"].GetUint();
	for (
		Value::ConstValueIterator it = document["scores"].Begin();
		it != document["scores"].End();
		++it
	)
		_scores.push_back(it->GetUint());

}

LocalStorage::~LocalStorage()
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
			StringRef(pair.second.data()),
			document.GetAllocator()
		);
	document.AddMember(
		"settings",
		settings,
		allocator
	);

	/*
		Serialize scores.
	*/
	document.AddMember(
		"total",
		Value(_total),
		allocator
	);
	Value scores(kArrayType);
	for (unsigned int value : _scores)
		scores.PushBack(Value(value), document.GetAllocator());
	document.AddMember(
		"scores",
		scores,
		allocator
	);
	
	/*
		Write to file.
	*/
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	cocos2d::FileUtils::getInstance()->writeStringToFile(
		buffer.GetString(),
		path()
	);
	cocos2d::UserDefault::getInstance()->setStringForKey(
		"hash",
		hash(path())
	);
}

bool
LocalStorage::feature(const std::string & feature) const
{
	return _features.find(feature)->second;
}

std::string
LocalStorage::setting(const std::string & setting) const
{
	return _settings.find(setting)->second;
}

unsigned int
LocalStorage::score(unsigned int index) const
{
	return _scores.at(index);
}

unsigned int
LocalStorage::total() const
{
	return _total;
}

void
LocalStorage::unblock(const std::string & feature)
{
	_features.find(feature)->second = true;
}

void
LocalStorage::change(
	const std::string & setting,
	const std::string & value
)
{
	_settings.find(setting)->second = value;
}

void
LocalStorage::update(unsigned int score, unsigned int seconds)
{
	++_total;
	_scores.push_back(score);
	std::sort(_scores.begin(), _scores.end());
	if (_scores.size() > 100)
		_scores.pop_back();
}

void
LocalStorage::default()
{
	_total = 0;

	_features.insert(
		std::pair<
			std::string,
			bool
		>(DISABLE_ADDS_FEATURE, false)
	);
}

std::string
LocalStorage::path() const
{
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "ls.hf";
	return cocos2d::FileUtils::getInstance()->getWritablePath() + "ls.hf";
}

std::string
LocalStorage::hash(const std::string & file) const
{
	const std::size_t LIMIT = 128;
	std::stringstream stream;
	std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(file);
	std::size_t size = data.size();
	for (std::size_t i = 0; i < size; ++i)
		if (i % 8 == 0)
			 stream << std::hex << (size ^ data[i]);

	std::string hash = stream.str();
	if (hash.length() > LIMIT)
		hash.erase(LIMIT, std::string::npos);
	if (hash.length() < LIMIT)
		hash.append(std::string(LIMIT - hash.length(), '0'));
	return hash;
}

}