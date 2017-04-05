#include "Scene.hpp"
#include "View.hpp"
#include <cocos2d.h>

namespace Application
{

Scene::Scene(cocos2d::Scene * scene)
	: _scene(scene)
{
}

void
Scene::append(View * view)
{
	_scene->addChild(view->node());
}

Scene::operator cocos2d::Scene * ()
{
	return _scene;
}

}