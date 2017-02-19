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

	Transporter::Kit * transpoter() const;
	Slicer::Kit * slicer() const;
	Cleaner::Kit * cleaner() const;

private:

	void update(float dt);
	unsigned int _time;
	std::unique_ptr<Transporter::Kit> _transpoter;
	std::unique_ptr<Slicer::Kit> _slicer;
	std::unique_ptr<Cleaner::Kit> _cleaner;
};

}
#endif
