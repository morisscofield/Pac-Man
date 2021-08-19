#include "ClydeGhost.h"

ClydeGhost::ClydeGhost(shared_ptr<Grid> & grid): Ghost(grid, GhostColour::CLYDE)
{
	srand(3);
}

void ClydeGhost::move()
{
	if(isWallIntersection(Entity{getTempPosition(),getDimentions()}))
	{
		if(wallCollide_ == 0)
			exitBox();
		else
			dir_ = clydeAI();
		wallCollide_++;
	}
	else
		setHitbox(getTempPosition().getX(), getTempPosition().getY());
}

Direction ClydeGhost::clydeAI() const
{
	unsigned int dir = static_cast<unsigned int>(dir_);
	dir += rand();
	dir %= 4;

	return static_cast<Direction>(dir);
}
