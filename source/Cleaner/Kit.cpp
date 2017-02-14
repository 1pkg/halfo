#include "Kit.hpp"
#include "Application/Act.hpp"
#include "Objects/Figure.hpp"
#include <algorithm>

namespace Cleaner
{

Kit::Kit(Application::Act * act)
	: _combo(0), _result(0),
	_edge(cocos2d::Node::create()),
	_score(cocos2d::Label::createWithTTF(std::to_string(_result), FONT_NAME, FONT_SIZE)),
	_scale(cocos2d::Label::createWithTTF(std::to_string(1), FONT_NAME, FONT_SIZE)),
	_sensor(cocos2d::EventListenerPhysicsContact::create()),
	_act(act)
{
	/*			Edge			*/
	const std::array<
		cocos2d::Vec2, 2
	> & vector = Application::Metric::instance().cleanerEdge();
	cocos2d::PhysicsBody * body =
		cocos2d::PhysicsBody::createEdgeChain(vector.data(), vector.size());
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_edge->setPhysicsBody(body);
	_act->addChild(_edge);

	/*			Score			*/
	_score->setPosition(Application::Metric::instance().score());
	_act->addChild(_score);

	/*			Scale			*/
	_scale->setPosition(Application::Metric::instance().combo());
	_act->addChild(_scale);

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
	_scale->removeFromParentAndCleanup(true);
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

	_result += scale();
	_score->setString(std::to_string(_result));
}

Objects::Figure *
Kit::find(cocos2d::PhysicsBody * body) const
{
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::const_iterator it = _lpool.find(body);
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
	if (_combo >= COMBO_LIMIT)
		return;

	++_combo;
	if (_combo >= COMBO_PROOF)
	{
		clean();
		_scale->setString(
			std::to_string(scale())
		);
	}
	_edge->runAction(
		cocos2d::MoveBy::create(
			EDGE_STEP_TIME,
			cocos2d::Vec2(0.0f, -Application::Metric::instance().absolute(EDGE_STEP))
		)
	);
	_act->transpoter()->increase();
}

void
Kit::reset()
{
	_combo = _combo < COMBO_PROOF ? 0 : _combo - COMBO_PROOF;
	_scale->setString(
		std::to_string(scale())
	);
	if (!_combo) {
		_edge->runAction(
			cocos2d::MoveTo::create(
				EDGE_STEP_TIME,
				Application::Metric::instance().origin()
			)
		);
	}
	else
	{
		_edge->runAction(
			cocos2d::MoveBy::create(
				EDGE_STEP_TIME,
				cocos2d::Vec2(0.0f, Application::Metric::instance().absolute(EDGE_STEP) * COMBO_PROOF)
			)
		);
	}
	_act->transpoter()->reset();
}

unsigned int
Kit::scale() const
{
	return 1 + static_cast<unsigned int>(std::floor(_combo / SCALE_KOEFICIENT));
}

void
Kit::clean()
{
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it;

	unsigned int lpoolCount =
		cocos2d::RandomHelper::random_int<
			unsigned int
		>(
			FIGURE_BURN_LIMIT.first,
			FIGURE_BURN_LIMIT.second
		);
	if (lpoolCount <= _lpool.size())
	{
		it = _lpool.begin();
		for (unsigned int i = 0; i < lpoolCount; ++i)
			it = _lpool.erase(it);
	}
	else
		_lpool.clear();

	unsigned int rpoolCount =
		cocos2d::RandomHelper::random_int<
			unsigned int
		>(
			FIGURE_BURN_LIMIT.first,
			FIGURE_BURN_LIMIT.second
		);
	if (rpoolCount <= _rpool.size())
	{
		it = _rpool.begin();
		for (unsigned int i = 0; i < rpoolCount; ++i)
			it = _rpool.erase(it);
	}
	else
		_rpool.clear();
}

bool
Kit::contact(cocos2d::PhysicsContact & contact) const
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