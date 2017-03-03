#ifndef COMPONENTS_STORAGE
#define COMPONENTS_STORAGE

#include "Application/Component.hpp"
#include <cocos2d.h>
#include <array>

namespace Components
{

class Storage : public Application::Component
{
public:

	void initialize() override;
	void flush() const;
	void pull();

private:

	std::string path() const;
	cocos2d::Data serialize() const;
	bool unserialize(const cocos2d::Data & buffer);

	static const std::size_t CRYPTO_SIZE = 16;
	static const std::array<unsigned char, CRYPTO_SIZE> CRYPTO_KEY, CRYPTO_IV;

	static cocos2d::Data encrypt(const cocos2d::Data & data);
	static cocos2d::Data decrypt(const cocos2d::Data & data);
};

}

#endif