#include "File.hpp"
#include <crypto/aes.h>

namespace Components
{

File::File(bool encrypted)
	: _encrypted(encrypted)
{
}

void
File::flush() const
{
	if (cocos2d::FileUtils::getInstance()->isFileExist(path()))
		cocos2d::FileUtils::getInstance()->removeFile(path());

	cocos2d::Data buffer = serialize();
	if (!buffer.isNull())
	{
		if (_encrypted)
			buffer = File::encrypt(buffer);

		cocos2d::FileUtils::getInstance()->writeDataToFile(
			buffer,
			path()
		);
	}
}

void
File::pull()
{
	if (!cocos2d::FileUtils::getInstance()->isFileExist(path()))
	{
		default();
		return;
	}
	cocos2d::Data buffer =
		cocos2d::FileUtils::getInstance()->getDataFromFile(path());
	if (_encrypted)
		buffer = File::decrypt(buffer);
	if (!unserialize(buffer))
	{
		default();
		return;
	}
}

void
File::default()
{
}

std::string
File::hash(const std::string & path)
{
	cocos2d::Data buffer =
		cocos2d::FileUtils::getInstance()->getDataFromFile(path);
	if (buffer.isNull() || buffer.getSize() == 0)
		return "";

	const std::size_t STEP = 4;
	std::stringstream stream;
	std::size_t size = buffer.getSize();
	unsigned char * data = buffer.getBytes();
	for (std::size_t i = 0; i < size; i += STEP)
		stream << std::hex << (size ^ data[i]);

	std::string hash = stream.str();
	if (hash.length() > HASH_SIZE)
		return trim(hash);
	if (hash.length() < HASH_SIZE)
		return pad(hash);
	return hash;
}

std::string
File::pad(const std::string & hash)
{
	std::stringstream stream;
	stream << hash;
	std::size_t size = hash.size();
	for (std::size_t i = 0; i < size / 2; ++i)
	{
		stream << std::hex << (hash[i] ^ hash[size - 1 - i]);
		if (size + i == HASH_SIZE)
			break;
	}

	std::string phash = stream.str();
	if (phash.length() < HASH_SIZE)
		return pad(phash);

	return phash;
}

std::string
File::trim(const std::string & hash)
{
	std::stringstream stream;
	std::size_t size = hash.size();
	for (std::size_t i = 0; i < size / 2; ++i)
		stream << std::hex << (hash[i] ^ hash[size - 1 - i]);

	std::string thash = stream.str();
	if (thash.length() > HASH_SIZE)
		return trim(thash);
	if (thash.length() < HASH_SIZE)
		return pad(thash);

	return thash;
}

cocos2d::Data
File::encrypt(const cocos2d::Data & data)
{
	aes_encrypt_ctx cx[1];
	aes_encrypt_key256(CRYPTO_KEY, cx);
	cocos2d::Data iv;
	iv.copy(CRYPTO_IV, HASH_SIZE + 1);

	cocos2d::Data buffer;
	buffer.fastSet(new unsigned char[data.getSize()]{0}, data.getSize());
	std::size_t size = 0, block = 0;
	do
	{
		if (data.getSize() - size < CRYPTO_CHUNK_SIZE)
			block = data.getSize() - size;
		else
			block = CRYPTO_CHUNK_SIZE;

		cocos2d::Data in, out;
		in.fastSet(new unsigned char[CRYPTO_CHUNK_SIZE]{0}, CRYPTO_CHUNK_SIZE);
		out.fastSet(new unsigned char[CRYPTO_CHUNK_SIZE]{0}, CRYPTO_CHUNK_SIZE);
		memcpy(in.getBytes(), data.getBytes() + size, block);

		aes_cbc_encrypt(
			in.getBytes(),
			out.getBytes(),
			CRYPTO_CHUNK_SIZE,
			iv.getBytes(),
			cx
		);
		memcpy(buffer.getBytes() + size, out.getBytes(), block);
		size += block;
	} while (block == CRYPTO_CHUNK_SIZE);
	return std::move(buffer);
}

cocos2d::Data
File::decrypt(const cocos2d::Data & data)
{
	aes_decrypt_ctx cx[1];
	aes_decrypt_key256(CRYPTO_KEY, cx);
	cocos2d::Data iv;
	iv.copy(CRYPTO_IV, HASH_SIZE + 1);

	cocos2d::Data buffer;
	buffer.fastSet(new unsigned char[data.getSize()]{0}, data.getSize());
	std::size_t size = 0, block = 0;
	do
	{
		if (data.getSize() - size < CRYPTO_CHUNK_SIZE)
			block = data.getSize() - size;
		else
			block = CRYPTO_CHUNK_SIZE;

		cocos2d::Data in, out;
		in.fastSet(new unsigned char[CRYPTO_CHUNK_SIZE]{0}, CRYPTO_CHUNK_SIZE);
		out.fastSet(new unsigned char[CRYPTO_CHUNK_SIZE]{0}, CRYPTO_CHUNK_SIZE);
		memcpy(in.getBytes(), data.getBytes() + size, block);

		aes_cbc_decrypt(
			in.getBytes(),
			out.getBytes(),
			CRYPTO_CHUNK_SIZE,
			iv.getBytes(),
			cx
		);
		memcpy(buffer.getBytes() + size, out.getBytes(), block);
		size += block;
	} while (block == CRYPTO_CHUNK_SIZE);
	return std::move(buffer);
}

const unsigned char
File::CRYPTO_KEY[HASH_SIZE + 1] = "49984386545308851686356475384311";

const unsigned char
File::CRYPTO_IV[HASH_SIZE + 1] = "14584768657157232041968904477990";

}