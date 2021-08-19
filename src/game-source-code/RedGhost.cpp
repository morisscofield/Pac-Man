#include "RedGhost.h"

RedGhost::RedGhost(shared_ptr<Grid> & grid): Ghost(grid, GhostColour::RED)
{
	srand(7);
}

void RedGhost::move()
{
	if(isWallIntersection(Entity{getTempPosition(),getDimentions()}))
	{
		if(wallCollide_ == 0)
			exitBox();
		else
			dir_ = redAI();
		wallCollide_++;
	}
	else
		setHitbox(getTempPosition().getX(), getTempPosition().getY());
}

Direction RedGhost::redAI() const
{
	unsigned int dir = static_cast<unsigned int>(dir_);
	dir = rand();
	dir %= 4;

	return static_cast<Direction>(dir);
}
