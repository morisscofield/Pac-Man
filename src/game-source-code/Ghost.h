#ifndef GHOST_H_
#define GHOST_H_
#include "Grid.h"
#include "Entity.h"
#include "Direction.h"

class Ghost: public Entity
{
public:
	Ghost(shared_ptr<Grid> & grid, const GhostColour & colour);
	virtual void move()=0;
	void reset();
	Coordinates getStep() const;
protected:
	shared_ptr<Grid> & grid_;
	Coordinates step_;
	Coordinates pacDest_;
	Direction dir_;
	GhostColour colour_;
	unsigned int wallCollide_;
	Coordinates getTempPosition() const;
	bool isWallIntersection(const Entity & tempPos);
	void exitBox();
};

#endif
