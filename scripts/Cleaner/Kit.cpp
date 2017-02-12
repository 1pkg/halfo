#include "Act.hpp"
#include "Kit.hpp"
#include "Objects/Figure.hpp"
#include "Application/Metric.hpp"

namespace Cleaner
{

Kit::Kit(Act * act)
	: _scale(1), _combo(0), _result(0),
	_edge(cocos2d::Node::create()),
	_score(cocos2d::Label::createWithTTF(std::to_string(_result), "sexy.ttf", 32)),
	_multiply(cocos2d::Label::createWithTTF(std::to_string(_scale), "sexy.ttf", 32)),
	_sensor(cocos2d::EventListenerPhysicsContact::create()),
	_act(act)
{
	/*			Edge			*/
	cocos2d::Vec2 vector[2] = 
		{
			Application::Metric::instance().origin(),
			cocos2d::Vec2(Application::Metric::instance().size().width, Application::Metric::instance().origin().y)
		};
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeChain(vector, 2);
	body->setDynamic(false);
	body->setContactTestBitmask(0xFFFFFFFF);
	_edge->setPhysicsBody(body);
	_act->addChild(_edge);

	/*			Score			*/
	_score->setPosition(Application::Metric::instance().score());
	_act->addChild(_score);

	/*			Multiply			*/
	_multiply->setPosition(Application::Metric::instance().combo());
	_act->addChild(_multiply);

	/*			Sensor			*/
	_sensor->onContactBegin = [this](cocos2d::PhysicsContact & contact)
	{
		return this->contact(contact);
	};
	_act->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_sensor, _act);
}

Kit::~Kit()
{
	_edge->removeFromParentAndCleanup(true);
	_score->removeFromParentAndCleanup(true);
	_multiply->removeFromParentAndCleanup(true);
	_act->getEventDispatcher()->removeEventListener(_sensor);
}

void
Kit::update(float dt)
{
	return;
}

void
Kit::attach(std::unique_ptr<Objects::Figure> figure)
{
	if (figure->view()->getPosition().x < Application::Metric::instance().center().x)
		_lpool.insert(
			std::pair<
				cocos2d::PhysicsBody *,
				std::unique_ptr<Objects::Figure>
			>(
				figure->view()->body(),
				std::move(figure)
			)
		);
	else
		_rpool.insert(
			std::pair<
				cocos2d::PhysicsBody *,
				std::unique_ptr<Objects::Figure>
			>(
				figure->view()->body(),
				std::move(figure)
			)
		);

	_result += _scale;
	_score->setString(std::to_string(_result));
}

Objects::Figure *
Kit::find(cocos2d::PhysicsBody * body)
{
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it = _lpool.find(body);
	if (it != _lpool.end())
		return (*it).second.get();

	it = _rpool.begin();
	if (it != _rpool.end())
		return (*it).second.get();

	return nullptr;
}

void
Kit::increase()
{
	++_combo;
	if (_combo >= COMBO_PROOF)
	{
		clean();
		_edge->setPosition(Application::Metric::instance().origin());
		_combo = 0;
		_scale += _scale <= SCALE_LIMIT;
		_multiply->setString(std::to_string(_scale));
	}
	_edge->runAction(
		cocos2d::MoveBy::create(
			0.5f,
			cocos2d::Vec2(0.0f, -CLEAN_STEP)
		)
	);
}

void
Kit::reset()
{
	_edge->runAction(
		cocos2d::MoveTo::create(
			0.5f,
			Application::Metric::instance().origin()
		)
	);
	_combo = 0;
	_scale = 1;
	_multiply->setString(std::to_string(_scale));
}

void
Kit::clean()
{
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it = _lpool.begin();
	while (it != _lpool.end())
	{
		if ((*it).second->view()->getPosition().y < Application::Metric::instance().origin().x)
			it = _lpool.erase(it);
		else
			++it;
	}
	it = _rpool.begin();
	while (it != _rpool.end())
	{
		if ((*it).second->view()->getPosition().y < Application::Metric::instance().origin().x)
			it = _rpool.erase(it);
		else
			++it;
	}
}

bool
Kit::contact(cocos2d::PhysicsContact & contact)
{
	cocos2d::PhysicsBody
		* first = contact.getShapeA()->getBody(),
		* second = contact.getShapeB()->getBody();
	return contact.getResult() ||
		_lpool.find(first) != _lpool.end() && _lpool.find(second) != _lpool.end() ||
		_rpool.find(first) != _rpool.end() && _rpool.find(second) != _rpool.end() ||
		_lpool.find(first) != _lpool.end() && _edge->getPhysicsBody() == second ||
		_lpool.find(second) != _lpool.end() && _edge->getPhysicsBody() == first ||
		_rpool.find(first) != _rpool.end() && _edge->getPhysicsBody() == second ||
		_rpool.find(second) != _rpool.end() && _edge->getPhysicsBody() == first;


}

}