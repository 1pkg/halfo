#include "File.hpp"
#include "Resource.hpp"
#include "Body.hpp"
#include <json/document.h>

namespace Components
{

void
Body::initialize()
{
	std::function<bool(const std::string &, const cocos2d::Data &)> callback =
	[this](const std::string & origin, const cocos2d::Data & data)
	{
		std::string body = Master::instance().get<File>().cache(data);
		_bodies.insert(std::pair<std::string, std::string>(replace(origin, Resource::Extension[(unsigned int)Resource::Type::BODY], ""), body));
		return true;
	};
	Master::instance().get<Components::Resource>().walk(Resource::Type::BODY, callback);
}

cocos2d::PhysicsBody *
Body::get(const std::string & body, cocos2d::Node * node)
{
	std::unordered_map<std::string, std::string>::const_iterator it = _bodies.find(body);
	if (it == _bodies.end())
		return nullptr;

	cocos2d::Data data = Master::instance().get<File>().read(it->second);
	using namespace rapidjson;
	Document document;
	document.Parse<kParseNoFlags>((char*)data.getBytes(), data.getSize());
	if (document.HasParseError())
		return nullptr;

	cocos2d::PhysicsBody * physicsBody = cocos2d::PhysicsBody::create();
	cocos2d::Size content = node->getContentSize();
	float offsetX = node->getAnchorPoint().x * content.width;
    float offsetY = node->getAnchorPoint().y * content.height;
	Value & shapes = document["rigidBodies"];
	for (Value::ConstValueIterator it = document["rigidBodies"].Begin(); it != document["rigidBodies"].End(); ++it)
	{
		cocos2d::Vec2 origin((*it)["origin"]["x"].GetDouble(), (*it)["origin"]["y"].GetDouble());
		for (Value::ConstValueIterator itNested = (*it)["polygons"].Begin(); itNested != (*it)["polygons"].End(); ++itNested)
		{
			std::size_t size = itNested->Size();
			std::vector<cocos2d::Vec2> points(size);
            for (std::size_t i = 0; i < size; ++i)
            {
                points[i].x = content.width * (*itNested)[i]["x"].GetDouble() - offsetX;
                points[i].y = content.height * (*itNested)[i]["y"].GetDouble() - offsetY;
            }
			physicsBody->addShape(cocos2d::PhysicsShapePolygon::create(points.data(), size));
		}
	}
	return physicsBody;
}

}