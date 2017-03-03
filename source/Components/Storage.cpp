#include "include.hpp"
#include "Storage.hpp"
#include <json/document.h>
#include <json/writer.h>
#include <json/memorybuffer.h>
#include <crypto/aes.h>

namespace Components
{

void
Storage::initialize()
{
}

void
Storage::flush() const
{
	if (cocos2d::FileUtils::getInstance()->isFileExist(path()))
		cocos2d::FileUtils::getInstance()->removeFile(path());

	cocos2d::Data buffer = serialize();
	if (!buffer.isNull())
	{
		buffer = Storage::encrypt(buffer);
		cocos2d::FileUtils::getInstance()->writeDataToFile(
			buffer,
			path()
		);
	}
}

void
Storage::pull()
{
	if (!cocos2d::FileUtils::getInstance()->isFileExist(path()))
		return;

	cocos2d::Data buffer =
		cocos2d::FileUtils::getInstance()->getDataFromFile(path());
	buffer = Storage::decrypt(buffer);
	if (!unserialize(buffer))
		return;
}

std::string
Storage::path() const
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + "st.hf";
}

cocos2d::Data
Storage::serialize() const
{
	using namespace rapidjson;
    Document document(kObjectType);
	Document::AllocatorType & allocator = document.GetAllocator();

	document.AddMember(
		"identifier",
		Value(/*cocos2d::identifier()*/ 0),
		allocator
	);

	/*
		Serialize features.
	*/
	Value features(kObjectType);
	for (const std::pair<std::string, bool> & feature : Master::instance().feature()._features)
		features.AddMember(
			Value(feature.first.data(), allocator),
			Value(feature.second),
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
	for (const std::pair<std::string, std::string> & setting : Master::instance().setting()._settings)
		settings.AddMember(
			Value(setting.first.data(), allocator),
			Value(setting.first.data(), allocator),
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
	Value results(kArrayType);
	for (const Application::Result & result : Master::instance().result()._results)
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
		Serialize stats.
	*/
	Value stats(kObjectType);
	stats.AddMember(
		"total",
		Value(Master::instance().stat()._total),
		allocator
	);
	document.AddMember(
		"stats",
		stats,
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
Storage::unserialize(const cocos2d::Data & buffer)
{
	using namespace rapidjson;
	Document document;
	document.Parse<kParseNoFlags>(
		(char *)buffer.getBytes(),
		buffer.getSize()
	);
	if (document.HasParseError())
		return false;

	if (/*cocos2d::identifier()*/ 0 != document["identifier"].GetInt())
		return false;

	/*
		Unserialize features.
	*/
	for (
		Value::ConstMemberIterator it = document["features"].MemberBegin();
		it != document["features"].MemberEnd();
		++it
	)
		Master::instance().feature().change(
			it->name.GetString(),
			it->value.GetBool()
		);

	/*
		Unserialize settings.
	*/
	for (
		Value::ConstMemberIterator it = document["settings"].MemberBegin();
		it != document["settings"].MemberEnd();
		++it
	)
		Master::instance().setting().change(
			it->name.GetString(),
			it->value.GetString()
		);

	/*
		Unserialize results.
	*/
	for (
		Value::ConstValueIterator it = document["results"].Begin();
		it != document["results"].End();
		++it
	)
	{
		Application::Result result(
			(*it)["score"].GetUint(),
			(*it)["seconds"].GetUint(),
			(*it)["integral"].GetUint()
		);
		Master::instance().result().update(result);
	}

	/*
		Unserialize stats.
	*/
	Master::instance().stat()._total = document["stats"]["total"].GetUint();

	return true;
}

cocos2d::Data
Storage::encrypt(const cocos2d::Data & data)
{
	aes_encrypt_ctx cx[1];
	aes_encrypt_key128(CRYPTO_KEY.data(), cx);
	cocos2d::Data iv;
	iv.copy(CRYPTO_IV.data(), CRYPTO_SIZE);
	std::size_t
		blockSize = CRYPTO_SIZE * CRYPTO_SIZE,
		dataSize = data.getSize(),
		bufferSize = (std::size_t)(ceil((float)dataSize / (float)blockSize) * blockSize),
		currentSize = 0;
	unsigned char eof = std::char_traits<unsigned char>::eof();
	cocos2d::Data buffer;
	buffer.fastSet(new unsigned char[bufferSize], bufferSize);
	do
	{
		cocos2d::Data in, out;
		in.fastSet(new unsigned char[blockSize], blockSize);
		out.fastSet(new unsigned char[blockSize], blockSize);
		if (dataSize - currentSize < blockSize)
		{
			memcpy(in.getBytes(), data.getBytes() + currentSize, dataSize - currentSize);
			memset(in.getBytes() + dataSize - currentSize, (unsigned char)std::char_traits<unsigned char>::eof(), blockSize - (dataSize - currentSize));
		}
		else
			memcpy(in.getBytes(), data.getBytes() + currentSize, blockSize);

		aes_cbc_encrypt(
			in.getBytes(),
			out.getBytes(),
			blockSize,
			iv.getBytes(),
			cx
		);
		memcpy(buffer.getBytes() + currentSize, out.getBytes(), blockSize);
		currentSize += blockSize;
	} while (currentSize != bufferSize);
	return std::move(buffer);
}

cocos2d::Data
Storage::decrypt(const cocos2d::Data & data)
{
	aes_decrypt_ctx cx[1];
	aes_decrypt_key128(CRYPTO_KEY.data(), cx);
	cocos2d::Data iv;
	iv.copy(CRYPTO_IV.data(), CRYPTO_SIZE);
	std::size_t
		blockSize = CRYPTO_SIZE * CRYPTO_SIZE,
		dataSize = data.getSize(),
		currentSize = 0;
	cocos2d::Data buffer;
	buffer.fastSet(new unsigned char[dataSize], dataSize);
	do
	{
		cocos2d::Data in, out;
		in.fastSet(new unsigned char[blockSize], blockSize);
		out.fastSet(new unsigned char[blockSize], blockSize);
		memcpy(in.getBytes(), data.getBytes() + currentSize, blockSize);

		aes_cbc_decrypt(
			in.getBytes(),
			out.getBytes(),
			blockSize,
			iv.getBytes(),
			cx
		);
		memcpy(buffer.getBytes() + currentSize, out.getBytes(), blockSize);
		currentSize += blockSize;
	} while (currentSize != dataSize);
	while (buffer.getBytes()[currentSize - 1] == (unsigned char)std::char_traits<unsigned char>::eof())
		--currentSize;
	cocos2d::Data tbuffer;
	tbuffer.copy(buffer.getBytes(), currentSize);
	return std::move(tbuffer);
}

const std::array<unsigned char, Storage::CRYPTO_SIZE>
Storage::CRYPTO_KEY = {'2','4','8','9','5','1','7','5','6','2','4','6','7','9','1','5'};

const std::array<unsigned char, Storage::CRYPTO_SIZE>
Storage::CRYPTO_IV = {'9','4','8','9','9','1','7','5','6','3','4','6','7','9','1','3'};

}