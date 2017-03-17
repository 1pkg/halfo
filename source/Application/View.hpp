#ifndef APPLICATION_VIEW
#define APPLICATION_VIEW

#include "Wrapper.hpp"

namespace cocos2d{class Layer;}
namespace Application
{

class View : public Wrapper
{
public:

	virtual void attach(cocos2d::Layer *) {}
};

}

#endif