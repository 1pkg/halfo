#include "Act.hpp"
#include "Kit.hpp"
#include "Objects/Figure.hpp"
#include "Application/Metric.hpp"

namespace Cleaner
{

Kit::Kit(Act * act)
	: _act(act),
	_node(cocos2d::Node::create())
{
	_act->addChild(_node);
	cocos2d::Vec2 vector[2] = 
		{
			Application::Metric::instance().origin(),
			cocos2d::Vec2(Application::Metric::instance().size().width, Application::Metric::instance().origin().y)
		};
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeChain(vector, 2);
	body->setCategoryBitmask(0x4);
	body->setCollisionBitmask(0x3);
	body->setContactTestBitmask(0x3);
	_node->setPhysicsBody(body);
}

Kit::~Kit()
{
}

void
Kit::update(float dt)
{
	return;
}

void
Kit::attach(std::unique_ptr<Objects::Figure> figure)
{
	_pool.push_back(std::move(figure));
}

void
Kit::grow()
{
	++_combo;
	_node->runAction(
		cocos2d::MoveBy::create(
			0.5f,
			cocos2d::Vec2(0.0f, -STEP)
		)
	);
}

void
Kit::drop()
{
	_node->runAction(
		cocos2d::MoveTo::create(
			0.5f,
			cocos2d::Vec2::ZERO
		)
	);
	_combo = 0;
}

}