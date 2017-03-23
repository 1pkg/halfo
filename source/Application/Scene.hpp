#ifndef APPLICATION_SCENE
#define APPLICATION_SCENE

#include "Wrapper.hpp"
#include <cocos2d.h>

namespace Application
{

class Scene : public Wrapper
{
public:

	Scene(cocos2d::Scene * scene) : _scene(scene), _ui(cocos2d::Layer::create()), _play(cocos2d::LayerColor::create(cocos2d::Color4B::WHITE)) {_scene->addChild(_play), _scene->addChild(_ui);}
	virtual void add(cocos2d::Node * node, bool ui) {ui ? _ui->addChild(node) : _play->addChild(node);}
	virtual cocos2d::EventDispatcher * eventDispatcher() {return _scene->getEventDispatcher();}
	operator cocos2d::Scene *() {return _scene;}

protected:

	cocos2d::Scene * _scene;
	cocos2d::Layer * _ui, * _play;
};

}

#endif