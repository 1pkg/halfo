#ifndef SCENES_ACT
#define SCENES_ACT

#include "include.hpp"
#include "Act/Transporter/Kit.hpp"
#include "Act/Slicer/Kit.hpp"
#include "Act/Cleaner/Kit.hpp"

namespace Scenes
{

using namespace Act;
class Act : public Application::Wrapper, public cocos2d::LayerColor
{
public:

	static Act * create();
	Act();
	~Act();
	Transporter::Kit * transpoter() const;
	Slicer::Kit * slicer() const;
	Cleaner::Kit * cleaner() const;

private:

	void update(float delta);
	std::unique_ptr<Transporter::Kit> _transpoter;
	std::unique_ptr<Slicer::Kit> _slicer;
	std::unique_ptr<Cleaner::Kit> _cleaner;
};

}
#endif
