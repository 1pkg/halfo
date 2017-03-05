#ifndef VIEWS_OVER
#define VIEWS_OVER

#include "include.hpp"

namespace Views
{

class Over : public Application::View
{
public:

	Over();
	~Over();
	void attach(cocos2d::Layer * layer) override;

private:

	cocos2d::DrawNode * _draw;
};

}

#endif