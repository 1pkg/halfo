#ifndef COMPONENTS_CRYPTO
#define COMPONENTS_CRYPTO

#include "Application/Component.hpp"
#include <cocos2d.h>
#include <array>

namespace Components
{

class Crypto : public Application::Component
{
public:

	cocos2d::Data encrypt(const cocos2d::Data & data, unsigned int blockSize);
	cocos2d::Data decrypt(const cocos2d::Data & data, unsigned int blockSize);
};

}

#endif