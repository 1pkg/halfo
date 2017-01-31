#ifndef ACT
#define ACT

#include "Transporter/Kit.hpp"
#include "Slicer/Kit.hpp"
#include "Cleaner/Kit.hpp"
#include <cocos2d.h>

namespace Cleaner{class Kit;}

class Act : public cocos2d::LayerColor
{
public:

    static cocos2d::Scene* scene();
	CREATE_FUNC(Act);
    virtual bool init();

	Transporter::Kit * transpoter() const;
	Slicer::Kit * slicer() const;
	Cleaner::Kit * cleaner() const;

private:

	void update(float dt);
	std::unique_ptr<Transporter::Kit> _transpoter;
	std::unique_ptr<Slicer::Kit> _slicer;
	std::unique_ptr<Cleaner::Kit> _cleaner;
};

#endif
