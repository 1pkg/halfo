#include "include.hpp"
#include "Storage.hpp"
#include <json/document.h>
#include <json/writer.h>
#include <json/memorybuffer.h>

namespace Components
{

void
Storage::initialize()
{
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "st.ev";
	if (!cocos2d::FileUtils::getInstance()->isFileExist(path))
		return;

	cocos2d::Data data = cocos2d::FileUtils::getInstance()->getDataFromFile(path);
	data = Master::instance().get<Crypto>("crypto").decrypt(data, 1);
	unserialize(data);
}

void
Storage::finitialize()
{
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "st.ev";
	if (cocos2d::FileUtils::getInstance()->isFileExist(path))
		cocos2d::FileUtils::getInstance()->removeFile(path);

	cocos2d::Data data = serialize();
	if (!data.isNull())
	{
		data = Master::instance().get<Crypto>("crypto").encrypt(data, 1);
		cocos2d::FileUtils::getInstance()->writeDataToFile(data, path);
	}
}

cocos2d::Data
Storage::serialize() const
{
	using namespace rapidjson;
    Document document(kObjectType);
	Document::AllocatorType & allocator = document.GetAllocator();
	document.AddMember("identifier", Value(cocos2d::getDeviceIdentifier().data(), allocator), allocator);

	/*
		Serialize settings.
	*/
	Value settings(kObjectType);
	for (const std::pair<std::string, std::string> & setting : Master::instance().get<Setting>("setting")._settings)
		settings.AddMember(Value(setting.first.data(), allocator), Value(setting.second.data(), allocator), allocator);
	document.AddMember("settings", settings, allocator);

	/*
		Serialize statistic.
	*/
	Value statistic(kObjectType);
	Value table(kArrayType), totals(kObjectType);
	for (const std::tuple<unsigned int, unsigned int, unsigned int> & result : Master::instance().get<Statistic>("statistic")._table)
	{
		if (!std::get<2>(result))
			continue;

		Value temp(kObjectType);
		temp.AddMember("slice", std::get<0>(result), allocator);
		temp.AddMember("time", std::get<1>(result), allocator);
		temp.AddMember("total", std::get<2>(result), allocator);
		table.PushBack(temp, allocator);
	}
	for (const std::pair<std::string, unsigned int> & total :  Master::instance().get<Statistic>("statistic")._totals)
		totals.AddMember(Value(total.first.data(), allocator), Value(total.second), allocator);
	statistic.AddMember("table", table,allocator);
	statistic.AddMember("totals", totals, allocator);
	document.AddMember("statistic",	statistic, allocator);

	MemoryBuffer bufffer;
	Writer<MemoryBuffer> writer(bufffer);
	document.Accept(writer);
	cocos2d::Data data;
	data.copy((unsigned char *)bufffer.GetBuffer(), bufffer.GetSize());
	return std::move(data);
}

bool
Storage::unserialize(const cocos2d::Data & data)
{
	using namespace rapidjson;
	Document document;
	document.Parse<kParseNoFlags>((char *)data.getBytes(), data.getSize());
	if (document.HasParseError())
		return false;
	if (cocos2d::getDeviceIdentifier() != document["identifier"].GetString())
		return false;

	/*
		Unserialize settings.
	*/
	for (Value::ConstMemberIterator it = document["settings"].MemberBegin(); it != document["settings"].MemberEnd(); ++it)
		Master::instance().get<Setting>("setting")._settings.at(it->name.GetString()) = it->value.GetString();

	/*
		Unserialize statistic.
	*/
	std::size_t position = 0;
	for (Value::ConstValueIterator it = document["statistic"]["table"].Begin(); it != document["statistic"]["table"].End(); ++it)
		Master::instance().get<Statistic>("statistic")._table[position++] = std::tuple<unsigned int, unsigned int, unsigned int>((*it)["slice"].GetUint(), (*it)["time"].GetUint(), (*it)["total"].GetUint());
	for (Value::ConstMemberIterator it = document["statistic"]["totals"].MemberBegin(); it != document["statistic"]["totals"].MemberEnd(); ++it)
		Master::instance().get<Statistic>("statistic")._totals.at(it->name.GetString()) = it->value.GetUint();

	return true;
}

}