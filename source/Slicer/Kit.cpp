#include "Kit.hpp"
#include "Scenes/Act.hpp"
#include "Objects/Figure.hpp"

namespace Slicer
{

Kit::Kit(Scenes::Act * act)
	: _anvil(cocos2d::DrawNode::create()),
	_hammer(cocos2d::DrawNode::create()),
	_touchSensor(cocos2d::EventListenerTouchOneByOne::create()),
	_physicSensor(cocos2d::EventListenerPhysicsContact::create()),
	_act(act)
{
	/*
		Initialize anvil.
	*/
	std::pair<cocos2d::Vec2, cocos2d::Vec2>
		anvil = Application::Main::instance().metric().anvil();
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
	anvilBody->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_anvil->setPhysicsBody(anvilBody);
	_act->addChild(_anvil);

	/*
		Initialize hammmer.
	*/
	std::pair<cocos2d::Vec2, cocos2d::Vec2>
		hammer = Application::Main::instance().metric().hammer();
	cocos2d::Vec2
		hammerDeltaLength(0.0f, Application::Main::instance().metric().hammerLength());
	_hammer->drawLine(
		hammer.first + hammerDeltaLength,
		hammer.second + hammerDeltaLength,
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody
		* hammerBody = cocos2d::PhysicsBody::createEdgeSegment(
			hammer.first + hammerDeltaLength,
			hammer.second + hammerDeltaLength
		);
	hammerBody->setDynamic(false);
	hammerBody->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_hammer->setPhysicsBody(hammerBody);
	_act->addChild(_hammer);

	/*
		Initialize touch sensor.
	*/
	_touchSensor->onTouchBegan = [this](cocos2d::Touch * touch, cocos2d::Event * event)
	{
		return putDown();
	};
	_touchSensor->onTouchEnded = [this](cocos2d::Touch * touch, cocos2d::Event * event)
	{
		putUp();
	};
	_act->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchSensor, _act);

	/*
		Initialize physic sensor.
	*/
	_physicSensor->onContactBegin = [this](cocos2d::PhysicsContact & contact)
	{
		return this->contact(contact);
	};
	_act->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_physicSensor, _act);
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

bool
Kit::putDown()
{
	_hammer->runAction(
		cocos2d::Sequence::create(
			cocos2d::CallFunc::create(std::bind(&Kit::slice, this)),
			cocos2d::MoveBy::create(
				HIT_TIME,
				cocos2d::Vec2(0.0f, -Application::Main::instance().metric().hammerLength())
			),
			nullptr
		)
	);
	return true;
}

void
Kit::putUp()
{
	_hammer->runAction(
		cocos2d::Sequence::create(
			cocos2d::MoveBy::create(
				HIT_TIME,
				cocos2d::Vec2(0.0f, Application::Main::instance().metric().hammerLength())
			),
			nullptr
		)
	);
}

void
Kit::slice() const
{
	std::vector<Objects::Figure *>
		figures = _act->transpoter()->find(Application::Main::instance().metric().hammer());
	for (Objects::Figure * figure : figures)
	{
		std::pair<
			std::unique_ptr<Objects::Figure>,
			std::unique_ptr<Objects::Figure>
		> slice = figure->slice(Application::Main::instance().metric().hammer());

		float firstArea = slice.first->area(), secondArea = slice.second->area(),
			  deltaArea = Application::Main::instance().metric().absolute(Application::Main::instance().metric().absolute(DELTA_AREA)),
			  limitArea = Application::Main::instance().metric().absolute(Application::Main::instance().metric().absolute(LIMIT_AREA));
		if (firstArea < limitArea || secondArea < limitArea)
			continue;

		if (abs(firstArea - secondArea) < deltaArea)
			_act->cleaner()->increase();
		else
			_act->cleaner()->reset();

		cocos2d::Vec2 firstImpuls =
			cocos2d::Vec2(Application::Main::instance().metric().reliative(-X_IMPULS), Application::Main::instance().metric().reliative(-Y_IMPULS));
		slice.first->view()->attach(_act);
		slice.first->view()->setPosition(figure->view()->getPosition());
		slice.first->view()->body()->applyImpulse(firstImpuls);
		_act->cleaner()->attach(std::move(slice.first));
		slice.first.release();

		cocos2d::Vec2 secondImpuls =
			cocos2d::Vec2(Application::Main::instance().metric().reliative(X_IMPULS), Application::Main::instance().metric().reliative(-Y_IMPULS));
		slice.second->view()->attach(_act);
		slice.second->view()->setPosition(figure->view()->getPosition());
		slice.second->view()->body()->applyImpulse(secondImpuls);
		_act->cleaner()->attach(std::move(slice.second));
		slice.second.release();

		_act->transpoter()->release(figure);
	}
}

bool
Kit::contact(cocos2d::PhysicsContact & contact) const
{
	cocos2d::PhysicsBody
		* first = contact.getShapeA()->getBody(),
		* second = contact.getShapeB()->getBody();
	Objects::Figure * figure;
	/*
		Fill figures from permanent pool of Transporter::Kit and move to Cleaner::Kit on contact with anvel or hammer.
		Set contact result to true.
	*/
	if ((figure = _act->transpoter()->find(first)) && (second == _hammer->getPhysicsBody() || second == _anvil->getPhysicsBody()))
	{
		_act->cleaner()->reset();
		figure->fill();
		_act->cleaner()->attach(
			std::move(
				_act->transpoter()->release(figure)
			)
		);
		return true;
	}

	if ((figure = _act->transpoter()->find(second)) && (first == _hammer->getPhysicsBody() || first == _anvil->getPhysicsBody()))
	{
		_act->cleaner()->reset();
		figure->fill();
		_act->cleaner()->attach(
			std::move(
				_act->transpoter()->release(figure)
			)
		);
		return true;
	}

	/*
		Figures from Cleaner::Kit pool on contact with anvel or hammer.
		Set contact result to true.
	*/
	if (_act->cleaner()->find(first) && (second == _hammer->getPhysicsBody() || second == _anvil->getPhysicsBody()))
		return true;

	if (_act->cleaner()->find(second) && (first == _hammer->getPhysicsBody() || first == _anvil->getPhysicsBody()))
		return true;

	return contact.getResult();
}

}