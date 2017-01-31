#include "Act.hpp"
#include "Kit.hpp"

namespace Cleaner
{

Kit::Kit(Act * act)
	: _act(act)
{
}

Kit::~Kit()
{
}

void
Kit::update(float dt)
{
	return;
}

}