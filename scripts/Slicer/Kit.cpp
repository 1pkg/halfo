#include "Act.hpp"
#include "Kit.hpp"
#include "Transporter/Kit.hpp"
#include "Objects/Figure.hpp"
#include "Views/Figure.hpp"

namespace Slicer
{

Kit::Kit(Act * act)
	: _act(act),
	_sensor(cocos2d::EventListenerTouchOneByOne::create()),
	_anvil(cocos2d::DrawNode::create()),
	_hammer(cocos2d::DrawNode::create())
{
	_act->addChild(_anvil), _act->addChild(_hammer);
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
	std::pair<cocos2d::Vec2, cocos2d::Vec2> anvil(
		cocos2d::Vec2(size.width / 2.0f, 0.0f),
		cocos2d::Vec2(size.width / 2.0f,  size.height / 3.0f * 2.0f)
	);
	std::pair<cocos2d::Vec2, cocos2d::Vec2> hammer(
		cocos2d::Vec2(size.width / 2.0f, size.height / 3.0f * 2.0f),
		cocos2d::Vec2(size.width / 2.0f, size.height)
	);
	_anvil->drawLine(
		anvil.first,
		anvil.second,
		cocos2d::Color4F::BLACK
	);
	_hammer->drawLine(
		hammer.first,
		hammer.second,
		cocos2d::Color4F::GREEN
	);
	cocos2d::PhysicsBody
		* anvilBody = cocos2d::PhysicsBody::createEdgeSegment(anvil.first, anvil.second),
		* hammerBody = cocos2d::PhysicsBody::createEdgeSegment(hammer.first, hammer.second);
	anvilBody->setDynamic(false);
	anvilBody->setCategoryBitmask(0x4);
	anvilBody->setCollisionBitmask(0x3);
	anvilBody->setContactTestBitmask(0x3);
	hammerBody->setDynamic(false);
	hammerBody->setCategoryBitmask(0x4);
	hammerBody->setCollisionBitmask(0x3);
	hammerBody->setContactTestBitmask(0x3);
	//_anvil->setPhysicsBody(anvilBody), _hammer->setPhysicsBody(hammerBody);

	_sensor->onTouchBegan = [this, hammer](cocos2d::Touch * touch, cocos2d::Event * event)
	{
		return this->slice(hammer);
	};
	_act->getEventDispatcher()->addEventListenerWithFixedPriority(_sensor, 1);
}

Kit::~Kit()
{
	_act->getEventDispatcher()->removeEventListener(_sensor);

	_anvil->removeFromParentAndCleanup(true);
	_hammer->removeFromParentAndCleanup(true);
}

void
Kit::update(float dt)
{
	return;
}

bool
Kit::slice(std::pair<cocos2d::Vec2, cocos2d::Vec2> line)
{
	std::vector<
		std::unique_ptr<Objects::Figure>
	> figures = _act->transpoter()->release(line);
	for (std::unique_ptr<Objects::Figure> & figure : figures)
	{
		std::pair<
			std::unique_ptr<Objects::Figure>,
			std::unique_ptr<Objects::Figure>
		> slice = figure->slice(line);

		slice.first->render()->attach(_act);
		slice.first->view()->setPosition(figure->view()->getPosition());
		slice.first->view()->body()->applyImpulse((cocos2d::Vec2(-30000.0f, -10000.0f)));

		slice.second->render()->attach(_act);
		slice.second->view()->setPosition(figure->view()->getPosition());
		slice.second->view()->body()->applyImpulse((cocos2d::Vec2(30000.0f, -10000.0f)));

		_pool.insert(
			std::pair<
				cocos2d::PhysicsBody *,
				std::unique_ptr<Objects::Figure>
			>(
				slice.first->view()->body(),
				std::move(slice.first)
			)
		);
		_pool.insert(
			std::pair<
				cocos2d::PhysicsBody *,
				std::unique_ptr<Objects::Figure>
			>(
				slice.second->view()->body(),
				std::move(slice.second)
			 )
		);

		slice.first.release();
		slice.second.release();
	}
	return false;
}

}