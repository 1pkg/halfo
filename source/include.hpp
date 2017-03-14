#ifndef INCLUDE
#define INCLUDE

#include "Application/Wrapper.hpp"
#include "Application/Kit.hpp"
#include "Application/Object.hpp"
#include "Application/View.hpp"
#include "Application/Component.hpp"

#include "Components/Metric.hpp"
#include "Components/File.hpp"
#include "Components/Setting.hpp"
#include "Components/Statistic.hpp"
#include "Components/Storage.hpp"
#include "Components/Deploy.hpp"
#include "Components/Resource.hpp"
#include "Components/Crypto.hpp"
#include "Components/Texture.hpp"
#include "Components/Body.hpp"
#include "Components/Font.hpp"

#include "Master.hpp"
#include <cocos2d.h>

#include <memory>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#define CRYPTO_KEY "1564949426338204"
#define CRYPTO_IV "2832340405100085"
#define CRYPTO_RESOURCE_BLOCK 0x10
#define CRYPTO_STORAGE_BLOCK 0x1
#define HASH_SIZE 0x10

#define CACHE_FILENAME_SIZE 0x10
#define CACHE_FILENAME_CHARSET "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define TRUE_FILE_EXTENSION ".ev"

#define STATISTIC_TABLE_SIZE 0xA
#define FLAG_NON "non"
#define FLAG_DONE "done"

#define COMMON_SCENE_SIZE cocos2d::Size(1920.0f, 1080.0f)
#define DEFAULT_PHYSICS_MASK 0xFFFFFFFF

template <typename T>
std::string to_string(T value)
{
	std::ostringstream stream;
	stream << value ;
	return stream.str() ;
}
std::string hash(const cocos2d::Data & data);

#endif