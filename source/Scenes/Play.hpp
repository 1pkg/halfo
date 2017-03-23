#ifndef SCENES_ACT
#define SCENES_ACT

#include "include.hpp"
#include "Play/Transporter/Kit.hpp"
#include "Play/Slicer/Kit.hpp"
#include "Play/Cleaner/Kit.hpp"

namespace Scenes
{

using namespace Play;
class Play : public Application::Scene
{
public:

	Play();
	~Play();
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
