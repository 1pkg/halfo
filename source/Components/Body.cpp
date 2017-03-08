#include "Body.hpp"
#include <json/document.h>

namespace Components
{

cocos2d::PhysicsBody *
Body::get(const cocos2d::Data & data, cocos2d::Node * node)
{
	using namespace rapidjson;
	Document document;
	document.Parse<kParseNoFlags>((char *)data.getBytes(), data.getSize());
	if (document.HasParseError())
		return nullptr;

	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::create();
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
			body->addShape(cocos2d::PhysicsShapePolygon::create(points.data(), size));
		}
	}
	return body;
}

}