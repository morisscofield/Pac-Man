#include "GatesAndKeys.h"

GatesAndKeys::GatesAndKeys(shared_ptr<Grid> & grid): grid_(grid), widthH_(grid_->getBlockDimentions().getX()),
			widthV_(grid_->getBlockDimentions().getX()/4), heightH_(grid_->getBlockDimentions().getY()/3),
			heightV_(grid_->getBlockDimentions().getY()), xOffset_(3.f/8 * grid_->getBlockDimentions().getX()),
			yOffset_(grid_->getBlockDimentions().getY()/3), keyWidth_(grid_->getBlockDimentions().getX()),
			keyHeight_(grid_->getBlockDimentions().getY())

{
	generateGatesAndKeys();
}

void GatesAndKeys::keyColissions(const Pacman & pacman)
{

	if(gates_.empty())
		return;

	auto keyIndex = 0;
	bool eaten = false;
	for(auto key : keys_)
	{
		if(colissions_.isOverlapping(pacman.getVerticies(), key.getVerticies()))
		{
			eaten = true;
			break;
		}
		keyIndex++;
	}

	if(eaten)
	{
		deleteGate();
		deleteGate();
		deleteGate();
		keys_.erase(keys_.begin() + keyIndex);
	}
}

void GatesAndKeys::drawGatesAndKeys(Presentation & presentation) const
{
	for_each(gates_.begin(), gates_.end(), [&presentation](auto gate){presentation.drawStatic(gate, EntityKey::GATE);});
	for_each(keys_.begin(), keys_.end(), [&presentation](auto key){presentation.draw(key, EntityKey::KEY);});
}

void GatesAndKeys::horizontalGate(const int & row, const int & col)
{
	auto position = grid_->convertToScreenPos(row, col);
	position.setY(position.getY() + yOffset_);
	gates_.push_back(Entity(position, Coordinates(widthH_,heightH_)));
}

void GatesAndKeys::verticalGate(const int & row, const int & col)
{
	auto position = grid_->convertToScreenPos(row, col);
	position.setX(position.getX() + xOffset_);
	gates_.push_back(Entity(position, Coordinates(widthV_,heightV_)));
}

void GatesAndKeys::generateKey(const int & row, const int & col)
{
	keys_.push_back(Entity(grid_->convertToScreenPos(row, col), Coordinates(keyWidth_, keyHeight_)));
}

void GatesAndKeys::generateGatesAndKeys()
{
	for(auto row = 0u; row < grid_->getMatrix().size(); row ++)
		for(auto col = 0u; col < grid_->getMatrix().at(row).size(); col ++)
			if(grid_->getMatrix().at(row).at(col) == 13)
				horizontalGate(row, col);
			else if(grid_->getMatrix().at(row).at(col) == 14)
				verticalGate(row, col);
			else if(grid_->getMatrix().at(row).at(col) == 15)
				generateKey(row, col);
}

void GatesAndKeys::deleteGate()
{
	if(!gates_.empty())
	{
		grid_->clearSpace(gates_.back().getPosition());
		gates_.pop_back();
	}
}
