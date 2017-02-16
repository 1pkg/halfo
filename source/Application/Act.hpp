#ifndef APPLICATION_ACT
#define APPLICATION_ACT

#include "include.hpp"
#include "Transporter/Kit.hpp"
#include "Slicer/Kit.hpp"
#include "Cleaner/Kit.hpp"

namespace Application
{

class Act : public cocos2d::LayerColor
{
public:

	CREATE_FUNC(Act);
    static cocos2d::Scene* scene();
    virtual bool init();

	Transporter::Kit * transpoter() const;
	Slicer::Kit * slicer() const;
	Cleaner::Kit * cleaner() const;
	void over();

private:

	void update(float dt);
	std::unique_ptr<Transporter::Kit> _transpoter;
	std::unique_ptr<Slicer::Kit> _slicer;
	std::unique_ptr<Cleaner::Kit> _cleaner;
};

}
#endif
