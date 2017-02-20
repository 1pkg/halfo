#ifndef SCENES_ACT
#define SCENES_ACT

#include "Application/Wrapper.hpp"
#include "Transporter/Kit.hpp"
#include "Slicer/Kit.hpp"
#include "Cleaner/Kit.hpp"
#include <cocos2d.h>

namespace Scenes
{

class Act : public Application::Wrapper, public cocos2d::LayerColor
{
public:

    static cocos2d::Scene * instantiate();

	Act();
	~Act();
	static Act * create();

	Transporter::Kit * transpoter() const;
	Slicer::Kit * slicer() const;
	Cleaner::Kit * cleaner() const;

private:

	const cocos2d::Vec2 GRAVITY = cocos2d::Vec2(0.0f, -100.0f);
	const float UPDATE_TIME = 1.0f;

	void update(float delta);
	std::unique_ptr<Transporter::Kit> _transpoter;
	std::unique_ptr<Slicer::Kit> _slicer;
	std::unique_ptr<Cleaner::Kit> _cleaner;
};

}
#endif
