#include "Pacman.h"

Pacman::Pacman(shared_ptr<Grid> & grid) :
		Entity(grid->getPacInitialPos(),
				Coordinates(grid->getBlockDimentions().getY() / 2,
				grid->getBlockDimentions().getY() / 2)), grid_(grid), move_step_(3, 3)
{
}

void Pacman::move(const Direction &dir)
{
	auto x = hitBox_.topLeft.getX();
	auto y = hitBox_.topLeft.getY();

	switch(dir)
	{
	case Direction::UP:
		y -= move_step_.getY();
		break;
	case Direction::DOWN:
		y += move_step_.getY();
		break;
	case Direction::LEFT:
		x -= move_step_.getX();
		break;
	case Direction::RIGHT:
		x += move_step_.getX();
		break;
	default:
		break;
	}

	if(!isWallIntersection(Entity(Coordinates(x,y), getDimentions()), dir))
		setHitbox(x, y);
}

Coordinates Pacman::getStep() const
{
	return move_step_;
}

bool Pacman::isWallIntersection(const Entity & tempPos, const Direction & dir)
{
	auto gridIndex1 = Coordinates{};
	auto gridIndex2 = Coordinates{};
	if (dir == Direction::UP || dir == Direction::LEFT)
	{
		gridIndex1 = grid_->convertToGridPos(tempPos.getPosition().getX(),
				tempPos.getPosition().getY());
		gridIndex2 = grid_->convertToGridPos(tempPos.getVerticies().topRight.getX(),
				tempPos.getVerticies().topRight.getY());
	}

	else if (dir == Direction::DOWN || dir == Direction::RIGHT)
	{
		gridIndex1 = grid_->convertToGridPos(tempPos.getVerticies().bottomRight.getX(),
				tempPos.getVerticies().bottomRight.getY());
		gridIndex2 = grid_->convertToGridPos(tempPos.getVerticies().bottomLeft.getX(),
				tempPos.getVerticies().bottomLeft.getY());
	}

	auto index = grid_->getMatrix().at(gridIndex1.getY()).at(gridIndex1.getX());
	auto index2 = grid_->getMatrix().at(gridIndex2.getY()).at(gridIndex2.getX());
	if(index == 1 || index == 2 || index == 3 || index == 4 || index == 5 || index == 6 || index == 13 || index == 14)
		return true;
	if(index2 == 1 || index2 == 2 || index2 == 3 || index2 == 4 || index2 == 5 || index2 == 6 || index2 == 13 || index2 == 14)
		return true;

	return false;
}
