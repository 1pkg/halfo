#ifndef VIEWS_UI_LABEL
#define VIEWS_UI_LABEL

#include "include.hpp"

namespace Views
{

namespace Ui
{

class Label : public Application::Views::Ui
{
public:

	Label(float fontSize);
	const std::string & getText() const;
	void setText(const std::string & text);

private:

	cocos2d::Label * _label;
};

}

}

#endif