#ifndef COMPONENTS_FILE
#define COMPONENTS_FILE

#include "Application\Wrapper.hpp"
#include <array>
#include <cocos2d.h>

namespace Components
{

class File : public Application::Wrapper
{
public:

	File(bool encrypted);
	virtual void flush() const;
	virtual void pull();


protected:

	virtual std::string path() const = 0;
	virtual cocos2d::Data serialize() const = 0;
	virtual bool unserialize(const cocos2d::Data & buffer) = 0;
	virtual void default();

	static std::string hash(const std::string & path);

private:

	static const std::size_t CRYPTO_SIZE = 16;
	static const std::array<unsigned char, CRYPTO_SIZE> CRYPTO_KEY, CRYPTO_IV;

	static std::string pad(const std::string & hash);
	static std::string trim(const std::string & hash);

	static cocos2d::Data encrypt(const cocos2d::Data & data);
	static cocos2d::Data decrypt(const cocos2d::Data & data);

	bool _encrypted;
};

}

#endif