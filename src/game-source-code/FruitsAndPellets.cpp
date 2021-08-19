#include "FruitsAndPellets.h"

FruitsAndPellets::FruitsAndPellets(shared_ptr<Grid> & grid) : grid_(grid),
		width_(grid_->getBlockDimentions().getX()),
		height_(grid_->getBlockDimentions().getY())
{
	for(auto row = 0u; row < grid_->getMatrix().size(); row++)
		for(auto col = 0u; col < grid_->getMatrix().at(row).size(); col++)
		{
			if(grid_->getMatrix().at(row).at(col) == 7)
			{
				auto coords = grid_->convertToScreenPos(row, col);
				fruits_.push_back(Entity(coords, Coordinates(width_,height_)));
    		}

			if(grid_->getMatrix().at(row).at(col) == 16)
			{
				auto coords = grid_->convertToScreenPos(row, col);
				powerPellets_.push_back(Entity(coords, Coordinates(width_,height_)));
			}
		}
}

void FruitsAndPellets::drawFruitsAndPellets(Presentation & presentation) const
{
	for_each(fruits_.begin(), fruits_.end(), [&presentation](auto fruit){presentation.draw(fruit, EntityKey::FRUIT);});
	for_each(powerPellets_.begin(), powerPellets_.end(), [&presentation](auto pellet){presentation.draw(pellet, EntityKey::PELLET);});
}

EntityVec FruitsAndPellets::getFruits() const
{
	return fruits_;
}

EntityVec FruitsAndPellets::getPellets() const
{
	return powerPellets_;
}

bool FruitsAndPellets::noPelletsLeft() const
{
	return fruits_.empty();
}

void FruitsAndPellets::fruitColissions(const Pacman & pacman)
{
	auto fruitIndex = 0;
	bool eaten = false;
	checkColissions(fruitIndex, eaten, pacman, fruits_);

	if(eaten)
	fruits_.erase(fruits_.begin() + fruitIndex);
}

bool FruitsAndPellets::isPelletCollision(const Pacman & pacman)
{
	auto pelletIndex = 0;
	bool eaten = false;
	checkColissions(pelletIndex, eaten, pacman, powerPellets_);

	if(eaten)
	{
		powerPellets_.erase(powerPellets_.begin() + pelletIndex);
		return true;
	}

	return false;
}

void FruitsAndPellets::checkColissions(int & index, bool & eaten, const Pacman & pacman, const EntityVec & enVec)
{
	for(auto entity : enVec)
	{
		if(colissions_.isOverlapping(pacman.getVerticies(), entity.getVerticies()))
		{
			eaten = true;
			break;
		}
		index++;
	}
}
