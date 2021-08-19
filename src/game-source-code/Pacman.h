#ifndef PACMAN_H_
#define PACMAN_H_
#include "Grid.h"
#include "Entity.h"
#include "Direction.h"
#include "Presentation.h"

class Pacman: public Entity
{
public:
	Pacman(shared_ptr<Grid> & grid);
	void move(const Direction & direction);
	void drawPacman(Presentation & presentation);
	Coordinates getStep() const;
private:
	shared_ptr<Grid> & grid_;
	Coordinates move_step_;
	bool isWallIntersection(const Entity & tempPos, const Direction & dir);
};

#endif
