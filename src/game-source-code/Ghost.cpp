#include "Ghost.h"

Ghost::Ghost(shared_ptr<Grid> & grid, const GhostColour & colour) : Entity(grid->getGhostPos(colour), Coordinates(grid->getBlockDimentions().getY() / 1.2,
				grid->getBlockDimentions().getY() / 1.2)), grid_(grid), step_(1.5, 1.5), dir_(Direction::UP), colour_(colour), wallCollide_(0)
{}

Coordinates Ghost::getTempPosition() const
{
	auto tempPosition = Coordinates{getPosition()};

	switch(dir_)
	{
	case Direction::UP:
		tempPosition.setY(getPosition().getY() - step_.getY());
		break;
	case Direction::DOWN:
		tempPosition.setY(getPosition().getY() + step_.getY());
		break;
	case Direction::LEFT:
		tempPosition.setX(getPosition().getX() - step_.getX());
		break;
	case Direction::RIGHT:
		tempPosition.setX(getPosition().getX() + step_.getX());
		break;
	default:
		break;
	}

	return tempPosition;
}

void Ghost::reset()
{
	auto pos = grid_->getGhostPos(colour_);
	setHitbox(pos.getX(), pos.getY());
	dir_ = Direction::UP;
	wallCollide_ = 0;
}

void Ghost::exitBox()
{
	auto dir = rand() % 2;

	if(dir == 0)
		dir_ = Direction::LEFT;
	else
		dir_ = Direction::RIGHT;
}

Coordinates Ghost::getStep() const
{
	return step_;
}

bool Ghost::isWallIntersection(const Entity & tempPos)
{
	auto gridIndex = Coordinates{};
	if (dir_ == Direction::UP || dir_ == Direction::LEFT)
		gridIndex = grid_->convertToGridPos(tempPos.getPosition().getX(),
				tempPos.getPosition().getY());

	else if (dir_ == Direction::DOWN || dir_ == Direction::RIGHT)
		gridIndex = grid_->convertToGridPos(tempPos.getVerticies().bottomRight.getX(),
				tempPos.getVerticies().bottomRight.getY());

	auto index = grid_->getMatrix().at(gridIndex.getY()).at(gridIndex.getX());
	if(index == 1 || index == 2 || index == 3 || index == 4 || index == 5 || index == 6 || index == 13 || index == 14)
		return true;

	return false;
}
