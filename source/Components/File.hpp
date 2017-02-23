#ifndef COMPONENTS_FILE
#define COMPONENTS_FILE

#include "Application\Wrapper.hpp"
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

	static const std::size_t HASH_SIZE = 32;
	static const std::size_t CRYPTO_CHUNK_SIZE = 256;
	static const unsigned char CRYPTO_KEY[HASH_SIZE + 1], CRYPTO_IV[HASH_SIZE + 1];

	static std::string pad(const std::string & hash);
	static std::string trim(const std::string & hash);

	static cocos2d::Data encrypt(const cocos2d::Data & data);
	static cocos2d::Data decrypt(const cocos2d::Data & data);

	bool _encrypted;
};

}

#endif