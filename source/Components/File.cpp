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
	if (buffer.isNull())
		return "";

	std::stringstream stream;
	std::size_t size = buffer.getSize();
	unsigned char * data = buffer.getBytes();
	for (std::size_t i = 0; i < size; i += 0x8)
		stream << std::hex << ((size ^ data[i]) % 15);

	std::string hash = stream.str();
	if (hash.length() > CRYPTO_SIZE)
		return trim(hash);
	if (hash.length() < CRYPTO_SIZE)
		return pad(hash);
	return hash;
}

std::string
File::pad(const std::string & hash)
{
	std::stringstream stream;
	std::size_t size = hash.size();
	stream << hash;
	if (size % 2 != 0)
		stream << std::hex << 0;
	for (std::size_t i = 0; i < size / 2; ++i)
	{
		stream << std::hex << ((hash[i] ^ hash[size - 1 - i]) % 15);
		if (size + i == CRYPTO_SIZE)
			break;
	}

	std::string phash = stream.str();
	if (phash.length() < CRYPTO_SIZE)
		return pad(phash);
	return phash;
}

std::string
File::trim(const std::string & hash)
{
	std::stringstream stream;
	std::size_t size = hash.size();
	if (size % 2 != 0)
		stream << std::hex << 15;
	for (std::size_t i = 0; i < size / 2; ++i)
	{
		stream << std::hex << ((hash[i] ^ hash[size - 1 - i]) % 15);
		if (size - i == CRYPTO_SIZE)
		{
			stream << hash.substr(i, size - 1 - i);
			break;
		}
	}
	std::string thash = stream.str();
	if (thash.length() > CRYPTO_SIZE)
		return trim(thash);
	return thash;
}

cocos2d::Data
File::encrypt(const cocos2d::Data & data)
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
File::decrypt(const cocos2d::Data & data)
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

const std::array<unsigned char, File::CRYPTO_SIZE>
File::CRYPTO_KEY = {'2','4','8','9','5','1','7','5','6','2','4','6','7','9','1','5'};

const std::array<unsigned char, File::CRYPTO_SIZE>
File::CRYPTO_IV = {'9','4','8','9','9','1','7','5','6','3','4','6','7','9','1','3'};

}