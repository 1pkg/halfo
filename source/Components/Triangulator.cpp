#include "Triangulator.hpp"
#include <triangulator/src/polypartition.h>

namespace Components
{

std::vector<cocos2d::Triangle>
Triangulator::triangulate(const cocos2d::Polygon & polygon) const
{
	TPPLPartition triangulator;
	std::list<TPPLPoly> ptriangles;
	TPPLPoly tpolygon;
	tpolygon.Init(polygon.size());
	for (std::size_t i = 0; i < polygon.size(); ++i)
		tpolygon.GetPoint(i) = TPPLPoint{polygon[i].x, polygon[i].y};
	triangulator.Triangulate_OPT(&tpolygon, &ptriangles);

	std::vector<cocos2d::Triangle> triangles;
	for (std::list<TPPLPoly>::iterator it = ptriangles.begin(); it != ptriangles.end(); ++it)
	{
		cocos2d::Triangle triangle = {
			cocos2d::Vec2(it->GetPoint(0).x, it->GetPoint(0).y),
			cocos2d::Vec2(it->GetPoint(1).x, it->GetPoint(1).y),
			cocos2d::Vec2(it->GetPoint(2).x, it->GetPoint(2).y)
		};
		triangles.push_back(triangle);
	}
	return triangles;
}

}