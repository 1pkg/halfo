#include "Crypto.hpp"
#include <crypto/aes.h>

namespace Components
{

cocos2d::Data
Crypto::encrypt(const cocos2d::Data & data, unsigned int blockSize)
{
	aes_encrypt_ctx cx[1];
	aes_encrypt_key128(CRYPTO_KEY, cx);
	cocos2d::Data iv;
	iv.copy(CRYPTO_IV, CRYPTO_SIZE);
	std::size_t dataSize = data.getSize(), block = CRYPTO_SIZE * blockSize, bufferSize = (std::size_t)(ceil((float)dataSize / (float)block) * block), currentSize = 0;
	unsigned char eof = std::char_traits<unsigned char>::eof();
	cocos2d::Data buffer;
	buffer.fastSet(new unsigned char[bufferSize], bufferSize);
	do
	{
		cocos2d::Data in, out;
		in.fastSet(new unsigned char[block], block);
		out.fastSet(new unsigned char[block], block);
		if (dataSize - currentSize < block)
		{
			memcpy(in.getBytes(), data.getBytes() + currentSize, dataSize - currentSize);
			memset(in.getBytes() + dataSize - currentSize, (unsigned char)std::char_traits<unsigned char>::eof(), block - (dataSize - currentSize));
		}
		else
			memcpy(in.getBytes(), data.getBytes() + currentSize, block);

		aes_cbc_encrypt(in.getBytes(), out.getBytes(), block, iv.getBytes(), cx);
		memcpy(buffer.getBytes() + currentSize, out.getBytes(), block);
		currentSize += block;
	} while (currentSize != bufferSize);
	return std::move(buffer);
}

cocos2d::Data
Crypto::decrypt(const cocos2d::Data & data, unsigned int blockSize)
{
	aes_decrypt_ctx cx[1];
	aes_decrypt_key128(CRYPTO_KEY, cx);
	cocos2d::Data iv;
	iv.copy(CRYPTO_IV, CRYPTO_SIZE);
	std::size_t dataSize = data.getSize(), block = CRYPTO_SIZE * blockSize, currentSize = 0;
	cocos2d::Data buffer;
	buffer.fastSet(new unsigned char[dataSize], dataSize);
	do
	{
		cocos2d::Data in, out;
		in.fastSet(new unsigned char[block], block);
		out.fastSet(new unsigned char[block], block);
		memcpy(in.getBytes(), data.getBytes() + currentSize, block);

		aes_cbc_decrypt(in.getBytes(), out.getBytes(), block, iv.getBytes(), cx);
		memcpy(buffer.getBytes() + currentSize, out.getBytes(), block);
		currentSize += block;
	} while (currentSize != dataSize);
	while (buffer.getBytes()[currentSize - 1] == (unsigned char)std::char_traits<unsigned char>::eof())
		--currentSize;
	cocos2d::Data tbuffer;
	tbuffer.copy(buffer.getBytes(), currentSize);
	return std::move(tbuffer);
}

const unsigned char Crypto::CRYPTO_KEY[CRYPTO_SIZE + 1] = "1564949426338204";

const unsigned char Crypto::CRYPTO_IV[CRYPTO_SIZE + 1] = "2832340405100085";

}