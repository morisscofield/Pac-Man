#ifndef BLINKYGHOST_H_
#define BLINKYGHOST_H_
#include "Ghost.h"
#include <cmath>
using namespace std;

class BlinkyGhost: public Ghost
{
public:
	BlinkyGhost(shared_ptr<Grid> & grid);
	virtual void move() override;
private:
	Direction blinkyAI() const;
};

#endif
