#include "Over.hpp"

namespace Views
{

Over::Over()
	: _node(cocos2d::DrawNode::create())
{
	const std::array<
		cocos2d::Vec2, 2
	> & over = Application::Main::instance().metric().over();
	_node->drawLine(
		over[0],
		over[1],
		cocos2d::Color4F::RED
	);
}

Over::~Over()
{
	_node->removeFromParentAndCleanup(true);
}

void
Over::attach(cocos2d::Layer * layer)
{
	if (_node->getParent() != nullptr)
		return;

	layer->addChild(_node);
}

}