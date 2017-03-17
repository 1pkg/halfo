#ifndef UI_LABEL
#define UI_LABEL

#include "include.hpp"

namespace Ui
{

class Label : public Application::View
{
public:

	Label(float fontSize);
	~Label();
	void attach(cocos2d::Layer * layer) override;
	cocos2d::Vec2 getPosition() const;
	void setPosition(cocos2d::Vec2 position);
	const std::string & getText() const;
	void setText(const std::string & text);

private:

	cocos2d::Label * _label;
};

}

#endif