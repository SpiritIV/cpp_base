#ifndef SBOMBERIMPL_H
# define SBOMBERIMPL_H

#include <vector>
#include "DynamicObject.h"
#include "GameObject.h"
#include "SBomber.h"

class SBomber::SBomberImpl
{
private:
    bool		exitFlag;

public:
    SBomberImpl() : exitFlag(false) {}
    ~SBomberImpl() {};

	void	setExitFlag(bool _value) { exitFlag = _value; }
	bool	getExitFlag() { return (exitFlag); }
};

#endif