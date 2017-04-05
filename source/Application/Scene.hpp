#ifndef APPLICATION_SCENE
#define APPLICATION_SCENE

#include "Wrapper.hpp"

namespace cocos2d
{
	class Layer;
	class Scene;
}

namespace Application
{

class View;
class Scene : public Wrapper
{
public:

	Scene(cocos2d::Scene * scene);
	virtual void append(View * view);
	virtual operator cocos2d::Scene * ();

protected:

	cocos2d::Scene * _scene;
};

}

#endif