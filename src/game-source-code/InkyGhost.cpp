#include "InkyGhost.h"

InkyGhost::InkyGhost(shared_ptr<Grid> & grid): Ghost(grid, GhostColour::INKY)
{
	srand(5);
}

void InkyGhost::move()
{
	if(isWallIntersection(Entity{getTempPosition(),getDimentions()}))
	{
		if(wallCollide_ == 0)
			exitBox();
		else
			dir_ = inkyAI();
		wallCollide_++;
	}
	else
		setHitbox(getTempPosition().getX(), getTempPosition().getY());
}

Direction InkyGhost::inkyAI() const
{
	unsigned int dir = static_cast<unsigned int>(dir_);
	dir = rand();
	dir %= 4;


	return static_cast<Direction>(dir);
}
