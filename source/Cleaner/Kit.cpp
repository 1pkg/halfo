#include "Kit.hpp"
#include "Scenes/Act.hpp"
#include "Objects/Figure.hpp"

namespace Cleaner
{

Kit::Kit(Scenes::Act * act)
	: _combo(0), _result(0),
	_platfrom(cocos2d::DrawNode::create()),
	_over(cocos2d::DrawNode::create()),
	_score(cocos2d::Label::createWithTTF(std::to_string(_result), FONT_NAME, FONT_SIZE)),
	_sensor(cocos2d::EventListenerPhysicsContact::create()),
	_act(act)
{
	/*
		Initialize platform edge.
	*/
	const std::array<
		cocos2d::Vec2, 2
	> & platformVector = Application::Main::instance().metric().platformEdge();
	_platfrom->drawLine(
		platformVector[0],
		platformVector[1],
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody * edgeBody =
		cocos2d::PhysicsBody::createEdgeChain(platformVector.data(), platformVector.size());
	edgeBody->setDynamic(false);
	edgeBody->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_platfrom->setPhysicsBody(edgeBody);
	_act->addChild(_platfrom);

	/*
		Initialize over edge.
	*/
	const std::array<
		cocos2d::Vec2, 2
	> & overVector = Application::Main::instance().metric().overEdge();
	_over->drawLine(
		overVector[0],
		overVector[1],
		cocos2d::Color4F::BLACK
	);
	_act->addChild(_over);
	_over->runAction(
		cocos2d::RepeatForever::create(
			cocos2d::Sequence::create(
				cocos2d::CallFunc::create(
					std::bind(&Kit::inspection, this)
				),
				cocos2d::DelayTime::create(INSPECTION_TIME),
				nullptr
			)
		)
	);

	/*
		Initialize score label.
	*/
	_score->setPosition(Application::Main::instance().metric().score());
	_act->addChild(_score);

	/*
		Initialize physic sensor.
	*/
	_sensor->onContactBegin = [this](cocos2d::PhysicsContact & contact)
	{
		return this->contact(contact);
	};
	_act->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_sensor, _act);
}

Kit::~Kit()
{
	_platfrom->removeFromParentAndCleanup(true);
	_over->removeFromParentAndCleanup(true);
	_score->removeFromParentAndCleanup(true);
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
	if (figure->view()->getPosition().x < Application::Main::instance().metric().center().x)
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
		clean();

	_platfrom->runAction(
		cocos2d::MoveBy::create(
			EDGE_STEP_TIME,
			cocos2d::Vec2(0.0f, -Application::Main::instance().metric().absolute(EDGE_STEP))
		)
	);
	_act->transpoter()->increase();
}

void
Kit::reset()
{
	_combo = _combo < COMBO_PROOF ? 0 : _combo - COMBO_PROOF;
	if (_combo == 0) {
		_platfrom->runAction(
			cocos2d::MoveTo::create(
				EDGE_STEP_TIME,
				Application::Main::instance().metric().origin()
			)
		);
	}
	else
	{
		_platfrom->runAction(
			cocos2d::MoveBy::create(
				EDGE_STEP_TIME,
				cocos2d::Vec2(0.0f, Application::Main::instance().metric().absolute(EDGE_STEP) * COMBO_PROOF)
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

void
Kit::inspection() const
{
	float overLimit = 
		Application::Main::instance().metric().origin().y + Application::Main::instance().metric().anvilLength();
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::const_iterator it = _lpool.begin();
	while (it != _lpool.end())
	{

		if (
			it->second->view()->getPosition().y > overLimit &&
			abs(it->second->view()->body()->getVelocity().y) < DELTA
		)
		{
			_act->over();
			return;
		}
		++it;
	}

	it = _rpool.begin();;
	while (it != _rpool.end())
	{
		if (
			it->second->view()->getPosition().y > overLimit &&
			abs(it->second->view()->body()->getVelocity().y) < DELTA
		)
		{
			_act->over();
			return;
		}
		++it;
	}
}

bool
Kit::contact(cocos2d::PhysicsContact & contact) const
{
	cocos2d::PhysicsBody
		* first = contact.getShapeA()->getBody(),
		* second = contact.getShapeB()->getBody();

	/*
		Figures from lpool or rpool on contact with platform edge.
		Set contact result to true.
	*/
	return contact.getResult() ||
		_lpool.find(first) != _lpool.end() && _lpool.find(second) != _lpool.end() ||
		_rpool.find(first) != _rpool.end() && _rpool.find(second) != _rpool.end() ||
		_lpool.find(first) != _lpool.end() && _platfrom->getPhysicsBody() == second ||
		_lpool.find(second) != _lpool.end() && _platfrom->getPhysicsBody() == first ||
		_rpool.find(first) != _rpool.end() && _platfrom->getPhysicsBody() == second ||
		_rpool.find(second) != _rpool.end() && _platfrom->getPhysicsBody() == first;
}

}