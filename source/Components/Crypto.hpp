#ifndef COMPONENTS_CRYPTO
#define COMPONENTS_CRYPTO

#include "Application/Component.hpp"
#include <cocos2d.h>

namespace Components
{

class Crypto : public Application::Component
{
public:

	cocos2d::Data encrypt(const cocos2d::Data & data, unsigned int blockSize);
	cocos2d::Data decrypt(const cocos2d::Data & data, unsigned int blockSize);

private:

	static const std::size_t CRYPTO_SIZE = 16;
	static const unsigned char CRYPTO_KEY[CRYPTO_SIZE + 1], CRYPTO_IV[CRYPTO_SIZE + 1];
};

}

#endif