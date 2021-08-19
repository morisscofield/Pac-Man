#ifndef CLYDEGHOST_H_
#define CLYDEGHOST_H_
#include "Ghost.h"
#include <cmath>

class ClydeGhost: public Ghost
{
public:
	ClydeGhost(shared_ptr<Grid> & grid);
	virtual void move() override;
private:
	Direction clydeAI() const;
};

#endif
