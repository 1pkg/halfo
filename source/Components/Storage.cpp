#include "include.hpp"
#include "Storage.hpp"
#include "Helpers/Result.hpp"
#include <json/document.h>
#include <json/writer.h>
#include <json/memorybuffer.h>
#include <crypto/aes.h>

namespace Components
{

void
Storage::initialize()
{
	_path = cocos2d::FileUtils::getInstance()->getWritablePath() + "st.hf";
	pull();
}

void
Storage::flush() const
{
	if (cocos2d::FileUtils::getInstance()->isFileExist(_path))
		cocos2d::FileUtils::getInstance()->removeFile(_path);

	cocos2d::Data buffer = serialize();
	if (!buffer.isNull())
	{
		buffer = Storage::encrypt(buffer);
		cocos2d::FileUtils::getInstance()->writeDataToFile(buffer, _path);
	}
}

void
Storage::pull()
{
	if (!cocos2d::FileUtils::getInstance()->isFileExist(_path))
		return;

	cocos2d::Data buffer = cocos2d::FileUtils::getInstance()->getDataFromFile(_path);
	buffer = Storage::decrypt(buffer);
	if (!unserialize(buffer))
		return;
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
	for (const std::pair<std::string, std::string> & setting : Master::instance().setting()._settings)
		settings.AddMember(Value(setting.first.data(), allocator), Value(setting.second.data(), allocator), allocator);
	document.AddMember("settings", settings, allocator);

	/*
		Serialize statistic.
	*/
	Value statistic(kObjectType);
	Value table(kArrayType), totals(kObjectType);
	for (const Helpers::Result & result : Master::instance().statistic()._table)
	{
		if (result.empty())
			continue;

		Value temp(kObjectType);
		temp.AddMember("slice", result.slice(),allocator);
		temp.AddMember("time", result.time(),allocator);
		table.PushBack(temp, allocator);
	}
	for (const std::pair<std::string, unsigned int> & total : Master::instance().statistic()._totals)
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
Storage::unserialize(const cocos2d::Data & buffer)
{
	using namespace rapidjson;
	Document document;
	document.Parse<kParseNoFlags>((char *)buffer.getBytes(), buffer.getSize());
	if (document.HasParseError())
		return false;
	if (cocos2d::getDeviceIdentifier() != document["identifier"].GetString())
		return false;

	/*
		Unserialize settings.
	*/
	for (Value::ConstMemberIterator it = document["settings"].MemberBegin(); it != document["settings"].MemberEnd(); ++it)
		Master::instance().setting()._settings.at(it->name.GetString()) = it->value.GetString();

	/*
		Unserialize statistic.
	*/
	std::size_t position = 0;
	for (Value::ConstValueIterator it = document["statistic"]["table"].Begin(); it != document["statistic"]["table"].End(); ++it)
		Master::instance().statistic()._table[position++] = Helpers::Result((*it)["slice"].GetUint(), (*it)["time"].GetUint());
	for (Value::ConstMemberIterator it = document["statistic"]["totals"].MemberBegin(); it != document["statistic"]["totals"].MemberEnd(); ++it)
		Master::instance().statistic()._totals.at(it->name.GetString()) = it->value.GetUint();

	return true;
}

cocos2d::Data
Storage::encrypt(const cocos2d::Data & data)
{
	aes_encrypt_ctx cx[1];
	aes_encrypt_key128(CRYPTO_KEY, cx);
	cocos2d::Data iv;
	iv.copy(CRYPTO_IV, CRYPTO_SIZE);
	std::size_t dataSize = data.getSize(), bufferSize = (std::size_t)(ceil((float)dataSize / (float)CRYPTO_SIZE) * CRYPTO_SIZE), currentSize = 0;
	unsigned char eof = std::char_traits<unsigned char>::eof();
	cocos2d::Data buffer;
	buffer.fastSet(new unsigned char[bufferSize], bufferSize);
	do
	{
		cocos2d::Data in, out;
		in.fastSet(new unsigned char[CRYPTO_SIZE], CRYPTO_SIZE);
		out.fastSet(new unsigned char[CRYPTO_SIZE], CRYPTO_SIZE);
		if (dataSize - currentSize < CRYPTO_SIZE)
		{
			memcpy(in.getBytes(), data.getBytes() + currentSize, dataSize - currentSize);
			memset(in.getBytes() + dataSize - currentSize, (unsigned char)std::char_traits<unsigned char>::eof(), CRYPTO_SIZE - (dataSize - currentSize));
		}
		else
			memcpy(in.getBytes(), data.getBytes() + currentSize, CRYPTO_SIZE);

		aes_cbc_encrypt(in.getBytes(), out.getBytes(), CRYPTO_SIZE, iv.getBytes(), cx);
		memcpy(buffer.getBytes() + currentSize, out.getBytes(), CRYPTO_SIZE);
		currentSize += CRYPTO_SIZE;
	} while (currentSize != bufferSize);
	return std::move(buffer);
}

cocos2d::Data
Storage::decrypt(const cocos2d::Data & data)
{
	aes_decrypt_ctx cx[1];
	aes_decrypt_key128(CRYPTO_KEY, cx);
	cocos2d::Data iv;
	iv.copy(CRYPTO_IV, CRYPTO_SIZE);
	std::size_t dataSize = data.getSize(), currentSize = 0;
	cocos2d::Data buffer;
	buffer.fastSet(new unsigned char[dataSize], dataSize);
	do
	{
		cocos2d::Data in, out;
		in.fastSet(new unsigned char[CRYPTO_SIZE], CRYPTO_SIZE);
		out.fastSet(new unsigned char[CRYPTO_SIZE], CRYPTO_SIZE);
		memcpy(in.getBytes(), data.getBytes() + currentSize, CRYPTO_SIZE);

		aes_cbc_decrypt(in.getBytes(), out.getBytes(), CRYPTO_SIZE, iv.getBytes(), cx);
		memcpy(buffer.getBytes() + currentSize, out.getBytes(), CRYPTO_SIZE);
		currentSize += CRYPTO_SIZE;
	} while (currentSize != dataSize);
	while (buffer.getBytes()[currentSize - 1] == (unsigned char)std::char_traits<unsigned char>::eof())
		--currentSize;
	cocos2d::Data tbuffer;
	tbuffer.copy(buffer.getBytes(), currentSize);
	return std::move(tbuffer);
}

const unsigned char Storage::CRYPTO_KEY[CRYPTO_SIZE + 1] = "1564949426338204";

const unsigned char Storage::CRYPTO_IV[CRYPTO_SIZE + 1] = "2832340405100085";

}