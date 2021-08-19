#ifndef INKYGHOST_H_
#define INKYGHOST_H_
#include "Ghost.h"

class InkyGhost: public Ghost
{
public:
	InkyGhost(shared_ptr<Grid> & grid);
	virtual void move() override;
private:
	Direction inkyAI() const;
};

#endif
