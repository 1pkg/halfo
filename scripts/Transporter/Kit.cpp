#include "Act.hpp"
#include "Kit.hpp"
#include "Objects/Figure.hpp"
#include "Views/Figure.hpp"
#include "Application/Metric.hpp"

namespace Transporter
{

Kit::Kit(Act * act)
	: _act(act),
	_sensor(cocos2d::EventListenerPhysicsContact::create()),
	_node(cocos2d::Node::create())
{
	_act->addChild(_node);
	cocos2d::Vec2 vector[4] = 
		{
			Application::Metric::instance().origin() - cocos2d::Vec2(Application::Metric::instance().origin().x, Application::Metric::instance().size().height),
			cocos2d::Vec2(Application::Metric::instance().origin().x, Application::Metric::instance().size().height),
			cocos2d::Vec2(Application::Metric::instance().size().width, Application::Metric::instance().size().height),
			cocos2d::Vec2(Application::Metric::instance().size().width, Application::Metric::instance().origin().y) - cocos2d::Vec2(Application::Metric::instance().origin().x, Application::Metric::instance().size().height)
		};
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeChain(vector, 4);
	body->setCategoryBitmask(0x4);
	body->setCollisionBitmask(0x3);
	body->setContactTestBitmask(0x3);
	_node->setPhysicsBody(body);

	_sensor->onContactBegin = [this](cocos2d::PhysicsContact & contact)
	{
		return this->contact(contact);
	};
	_act->getEventDispatcher()->addEventListenerWithFixedPriority(_sensor, 1);
}

Kit::~Kit()
{
	_act->getEventDispatcher()->removeEventListener(_sensor);

	_node->removeFromParentAndCleanup(true);
}

void
Kit::update(float dt)
{
	static float spawn = 0.0f, refresh = 0.0f;
	spawn += dt;
	refresh += dt;

	if (spawn >= 5.0f)
	{
		std::unique_ptr<Objects::Figure> figure = _architector.provide();
		figure->view()->attach(_act);
		_pool.insert(
			std::pair<
				cocos2d::PhysicsBody *,
				std::unique_ptr<Objects::Figure>
			>(
				figure->view()->body(),
				std::move(figure)
			)
		);
		spawn = 0.0f;
	}

	if (refresh >= 50.0f)
	{
		_architector.refresh();
		refresh = 0.0f;
	}
}

std::vector<Objects::Figure *>
Kit::find(std::pair<cocos2d::Vec2, cocos2d::Vec2> line)
{
	std::vector<Objects::Figure *> result;
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it = _pool.begin();
	while (it != _pool.end())
	{
		if ((*it).second->intersect(line))
			result.push_back(it->second.get());
		++it;
	}
	return result;
}

void
Kit::release(Objects::Figure * figure)
{
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it = _pool.begin();
	while (it != _pool.end())
	{
		if ((*it).second.get() == figure)
		{
			_pool.erase(it);
			return;
		}
		++it;
	}
}

bool
Kit::contact(cocos2d::PhysicsContact & contact)
{
	cocos2d::PhysicsBody * first = contact.getShapeA()->getBody();
	cocos2d::PhysicsBody * second = contact.getShapeB()->getBody();
	if (_pool.find(first) != _pool.end() && _pool.find(second) != _pool.end())
		return false;

	if (_pool.find(first) != _pool.end() && second == _node->getPhysicsBody())
	{
		_pool.find(first)->second->fill();
		_pool.find(first)->second.release();
		_pool.erase(_pool.find(first));
	}

	if (_pool.find(second) != _pool.end() && first == _node->getPhysicsBody())
	{
		_pool.find(second)->second->fill();
		_pool.find(second)->second.release();
		_pool.erase(_pool.find(second));
	}
	return true;
}

}