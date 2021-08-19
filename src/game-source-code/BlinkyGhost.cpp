#include "BlinkyGhost.h"

BlinkyGhost::BlinkyGhost(shared_ptr<Grid> & grid): Ghost(grid, GhostColour::BLINKY)
{
	srand(1);
}

void BlinkyGhost::move()
{
	if(isWallIntersection(Entity{getTempPosition(),getDimentions()}))
	{
		if(wallCollide_ == 0)
			exitBox();
		else
			dir_ = blinkyAI();
		wallCollide_++;
	}
	else
		setHitbox(getTempPosition().getX(), getTempPosition().getY());
}

Direction BlinkyGhost::blinkyAI() const
{
	unsigned int dir = static_cast<unsigned int>(dir_);
	dir = rand();
	dir %= 4;


	return static_cast<Direction>(dir);
}
