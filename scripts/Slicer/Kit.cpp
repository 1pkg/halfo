#include "Act.hpp"
#include "Kit.hpp"
#include "Transporter/Kit.hpp"
#include "Objects/Figure.hpp"
#include "Views/Figure.hpp"
#include "Application/Metric.hpp"

namespace Slicer
{

Kit::Kit(Act * act)
	: _act(act),
	_sensor(cocos2d::EventListenerTouchOneByOne::create()),
	_anvil(cocos2d::DrawNode::create()),
	_hammer(cocos2d::DrawNode::create())
{
	_act->addChild(_anvil), _act->addChild(_hammer);
	_anvil->drawLine(
		Application::Metric::instance().anvil().first,
		Application::Metric::instance().anvil().second,
		cocos2d::Color4F::BLACK
	);
	_hammer->drawLine(
		Application::Metric::instance().hammer().first,
		Application::Metric::instance().hammer().second,
		cocos2d::Color4F::GREEN
	);
	cocos2d::PhysicsBody
		* anvilBody = cocos2d::PhysicsBody::createEdgeSegment(
			Application::Metric::instance().anvil().first,
			Application::Metric::instance().anvil().second
		),
		* hammerBody = cocos2d::PhysicsBody::createEdgeSegment(
			Application::Metric::instance().hammer().first,
			Application::Metric::instance().hammer().second
		);
	anvilBody->setDynamic(false);
	anvilBody->setCategoryBitmask(0x4);
	anvilBody->setCollisionBitmask(0x3);
	anvilBody->setContactTestBitmask(0x3);
	hammerBody->setDynamic(false);
	hammerBody->setCategoryBitmask(0x4);
	hammerBody->setCollisionBitmask(0x3);
	hammerBody->setContactTestBitmask(0x3);
	//_anvil->setPhysicsBody(anvilBody), _hammer->setPhysicsBody(hammerBody);

	_sensor->onTouchBegan = [this](cocos2d::Touch * touch, cocos2d::Event * event)
	{
		return this->slice();
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
Kit::slice()
{
	std::vector<
		std::unique_ptr<Objects::Figure>
	> figures = _act->transpoter()->release(Application::Metric::instance().hammer());
	for (std::unique_ptr<Objects::Figure> & figure : figures)
	{
		std::pair<
			std::unique_ptr<Objects::Figure>,
			std::unique_ptr<Objects::Figure>
		> slice = figure->slice(Application::Metric::instance().hammer());

		slice.first->view()->attach(_act);
		slice.first->view()->setPosition(figure->view()->getPosition());
		slice.first->view()->body()->applyImpulse((cocos2d::Vec2(-30000.0f, -10000.0f)));

		slice.second->view()->attach(_act);
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