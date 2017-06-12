#include "components.hpp"
#include "Splitter.hpp"
#include "Objects/Figure.hpp"
#include <splitter/polysplitter.hpp>

namespace Components
{

std::vector<std::unique_ptr<Objects::Figure>>
Splitter::split(const Objects::Figure * figure, const cocos2d::Line & line)
{
	PolySplitter splitter;
	cocos2d::Polygon pattern = rotate(figure->pattern(), figure->view()->getRotation());
	for (cocos2d::Vec2 & point : pattern)
		point += figure->view()->getPosition();
	std::vector<cocos2d::Polygon> patterns = splitter.Split(pattern, line);
	for (cocos2d::Polygon & pattern : patterns)
		for (cocos2d::Vec2 & point : pattern)
			point -= figure->view()->getPosition();

	cocos2d::log(
		"Split figure: %s\nBy line: %s\n\nSplitted into %d figures:\n",
		to_string(pattern).data(),
		to_string(line).data(),
		patterns.size()
	);
	std::vector<std::unique_ptr<Objects::Figure>> figures;
	for (const cocos2d::Polygon & pattern : patterns)
	{
		cocos2d::log("%s\n", to_string(pattern).data());
		if (area(pattern) > 0.0f)
		{
			figures.push_back(std::unique_ptr<Objects::Figure>(
				new Objects::Figure(pattern, figure->view()->getRotation(), false)
			));
			figures.back()->view()->setPosition(figure->view()->getPosition());
			figures.back()->view()->body()->applyImpulse(cocos2d::Vec2(-100.0f, 0.0f));
		}
	}
	return figures;
}

cocos2d::Polygon
Splitter::rotate(const cocos2d::Polygon& vector, float angle)
{
	cocos2d::Polygon result(vector.size());
	float rotation = CC_DEGREES_TO_RADIANS(angle);
	for (std::size_t i = 0; i < vector.size(); ++i)
		result[i] = cocos2d::Vec2(
			cos(rotation) * (vector[i].x) + sin(rotation) * (vector[i].y),
			-sin(rotation) * (vector[i].x) + cos(rotation) * (vector[i].y)
		);
	return result;
}

}