#ifndef REDGHOST_H_
#define REDGHOST_H_
#include "Ghost.h"

class RedGhost: public Ghost
{
public:
	RedGhost(shared_ptr<Grid> & grid);
	virtual void move() override;
private:
	Direction redAI() const;
};

#endif
