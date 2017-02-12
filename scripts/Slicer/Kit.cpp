#include "Act.hpp"
#include "Kit.hpp"
#include "Transporter/Kit.hpp"
#include "Objects/Figure.hpp"
#include "Views/Figure.hpp"
#include "Application/Metric.hpp"

namespace Slicer
{

Kit::Kit(Act * act)
	: _anvil(cocos2d::DrawNode::create()),
	_hammer(cocos2d::DrawNode::create()),
	_touchSensor(cocos2d::EventListenerTouchOneByOne::create()),
	_physicSensor(cocos2d::EventListenerPhysicsContact::create()),
	_act(act)
{
	/*			Anvil			*/
	std::pair<cocos2d::Vec2, cocos2d::Vec2>
		anvil = Application::Metric::instance().anvil();
	_anvil->drawLine(
		anvil.first,
		anvil.second,
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody
		* anvilBody = cocos2d::PhysicsBody::createEdgeSegment(
			anvil.first,
			anvil.second
		);
	anvilBody->setDynamic(false);
	anvilBody->setContactTestBitmask(0xFFFFFFFF);
	_anvil->setPhysicsBody(anvilBody);
	_act->addChild(_anvil);

	/*			Hammmer			*/
	std::pair<cocos2d::Vec2, cocos2d::Vec2>
		hammer = Application::Metric::instance().hammer();
	_hammer->drawLine(
		hammer.first + cocos2d::Vec2(0.0f, Application::Metric::instance().lenght()),
		hammer.second + cocos2d::Vec2(0.0f, Application::Metric::instance().lenght()),
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody
		* hammerBody = cocos2d::PhysicsBody::createEdgeSegment(
			hammer.first + cocos2d::Vec2(0.0f, Application::Metric::instance().lenght()),
			hammer.second + cocos2d::Vec2(0.0f, Application::Metric::instance().lenght())
		);
	hammerBody->setDynamic(false);
	hammerBody->setContactTestBitmask(0xFFFFFFFF);
	_hammer->setPhysicsBody(hammerBody);
	_act->addChild(_hammer);

	/*			TouchSensor			*/
	_touchSensor->onTouchBegan = [this](cocos2d::Touch * touch, cocos2d::Event * event)
	{
		_hammer->runAction(
			cocos2d::Sequence::create(
				cocos2d::CallFunc::create(std::bind(&Kit::slice, this)),
				cocos2d::MoveBy::create(
					0.1f,
					cocos2d::Vec2(0.0f, -Application::Metric::instance().lenght())
				),
				nullptr
			)
		); 
		return true;
	};
	_touchSensor->onTouchEnded = [this](cocos2d::Touch * touch, cocos2d::Event * event)
	{
		_hammer->runAction(
			cocos2d::Sequence::create(
				cocos2d::MoveBy::create(
					0.1f,
					cocos2d::Vec2(0.0f, Application::Metric::instance().lenght())
				),
				nullptr
			)
		); 
	};
	_act->getEventDispatcher()->addEventListenerWithFixedPriority(_touchSensor, 1);

	/*			PhysicsSensor			*/
	_physicSensor->onContactBegin = [this](cocos2d::PhysicsContact & contact)
	{
		return this->contact(contact);
	};
	_act->getEventDispatcher()->addEventListenerWithFixedPriority(_physicSensor, 1);
}

Kit::~Kit()
{
	_anvil->removeFromParentAndCleanup(true);
	_hammer->removeFromParentAndCleanup(true);
	_act->getEventDispatcher()->removeEventListener(_touchSensor);
	_act->getEventDispatcher()->removeEventListener(_physicSensor);
}

void
Kit::update(float dt)
{
	return;
}

void
Kit::slice()
{
	std::vector<Objects::Figure *>
		figures = _act->transpoter()->find(Application::Metric::instance().hammer());
	for (Objects::Figure * figure : figures)
	{
		std::pair<
			std::unique_ptr<Objects::Figure>,
			std::unique_ptr<Objects::Figure>
		> slice = figure->slice(Application::Metric::instance().hammer());

		float firstArea = slice.first->area(), secondArea = slice.second->area(),
			  deltaArea = Application::Metric::instance().absolute(Application::Metric::instance().absolute(DELTA_AREA)),
			  limitArea = Application::Metric::instance().absolute(Application::Metric::instance().absolute(LIMIT_AREA));
		if (firstArea < limitArea || secondArea < limitArea)
			continue;

		if (abs(firstArea - secondArea) < deltaArea)
			_act->cleaner()->increase();
		else
			_act->cleaner()->reset();

		cocos2d::Vec2 firstImpuls = cocos2d::Vec2(Application::Metric::instance().reliative(-X_IMPULS), Application::Metric::instance().reliative(-Y_IMPULS));
		slice.first->view()->attach(_act);
		slice.first->view()->setPosition(figure->view()->getPosition());
		slice.first->view()->body()->applyImpulse(firstImpuls);
		_act->cleaner()->attach(std::move(slice.first));
		slice.first.release();

		cocos2d::Vec2 secondImpuls = cocos2d::Vec2(Application::Metric::instance().reliative(X_IMPULS), Application::Metric::instance().reliative(-Y_IMPULS));
		slice.second->view()->attach(_act);
		slice.second->view()->setPosition(figure->view()->getPosition());
		slice.second->view()->body()->applyImpulse(secondImpuls);
		_act->cleaner()->attach(std::move(slice.second));
		slice.second.release();

		_act->transpoter()->release(figure);
	}
}

bool
Kit::contact(cocos2d::PhysicsContact & contact)
{
	cocos2d::PhysicsBody
		* first = contact.getShapeA()->getBody(),
		* second = contact.getShapeB()->getBody();
	std::unique_ptr<Objects::Figure>
		firstFigure = _act->transpoter()->release(first),
		secondFigure = _act->transpoter()->release(second);
	if (firstFigure && (second == _hammer->getPhysicsBody() || second == _anvil->getPhysicsBody()))
	{
		firstFigure->fill();
		_act->cleaner()->attach(std::move(firstFigure));
		return true;
	}

	if (secondFigure && (first == _hammer->getPhysicsBody() || first == _anvil->getPhysicsBody()))
	{
		secondFigure->fill();
		_act->cleaner()->attach(std::move(secondFigure));
		return true;
	}

	Objects::Figure
		* firstShard = _act->cleaner()->find(first),
		* secondShard = _act->cleaner()->find(second);
	if (firstShard && (second == _hammer->getPhysicsBody() || second == _anvil->getPhysicsBody()))
		return true;

	if (secondShard && (first == _hammer->getPhysicsBody() || first == _anvil->getPhysicsBody()))
		return true;

	return false;
}

}