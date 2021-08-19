#include "Grid.h"

Grid::Grid(const Coordinates &gridSize, const Coordinates &screenDimentions, ifstream & mazeFile) :
		screen_(screenDimentions), blockWidth_(screenDimentions.getX()/gridSize.getX()),
		blockHeight_(screenDimentions.getY()/gridSize.getY())
{
	resizeMatrix(gridSize.getX(), gridSize.getY());
	readMaze(mazeFile);
	pacPos_ = findEntity(8);
}

void Grid::clearSpace(const Coordinates & screenPos)
{
	auto gridPos = convertToGridPos(screenPos.getX(), screenPos.getY());
	matrix_.at(gridPos.getY()).at(gridPos.getX()) = 0;
}

void Grid::readMaze(ifstream & mazeFile)
{
	for (auto row = 0u; row < matrix_.size(); row++)
		for (auto col = 0u; col < matrix_.at(row).size(); col++)
			mazeFile >> matrix_.at(row).at(col);
}

void Grid::resizeMatrix(const int &width, const int &height)
{
	matrix_.resize(height);
	for (auto index = 0u; index < matrix_.size(); index++)
		matrix_.at(index).resize(width);
}

Coordinates Grid::convertToGridPos(const float & screenWidth, const float & screenHeight) const
{
	auto x = int(screenWidth/blockWidth_);
	auto y = int(screenHeight/blockHeight_);

	return Coordinates{float(x),float(y)};
}

Coordinates Grid::convertToScreenPos(const int & gridRow, const int & gridCol) const
{
	return Coordinates{gridCol * blockWidth_, gridRow * blockHeight_};
}

Coordinates Grid::getBlockDimentions() const
{
	return Coordinates{blockWidth_, blockHeight_};
}

Coordinates Grid::getPacInitialPos() const
{
	return pacPos_;
}

Coordinates Grid::getScreenDimentions() const
{
	return screen_;
}

Coordinates Grid::getGhostPos(const GhostColour & ghost) const
{
	auto position = Coordinates{};
	switch(ghost)
	{
	case GhostColour::RED:
		position = findEntity(9);
		break;
	case GhostColour::INKY:
		position = findEntity(10);
		break;
	case GhostColour::BLINKY:
		position = findEntity(11);
		break;
	case GhostColour::CLYDE:
		position = findEntity(12);
		break;
	default:
		break;
	}

	return position;
}

Coordinates Grid::findEntity(const int & entityKey) const
{
	auto entity = Coordinates{};
	for(auto row = 0u; row < matrix_.size(); row++)
		for(auto col = 0u; col < matrix_.at(row).size(); col++)
			if(matrix_.at(row).at(col) == entityKey)
			{
				 entity = convertToScreenPos(row, col);
				 entity.set(entity.getX() + blockWidth_/3, entity.getY() + blockHeight_/4);
			}

	return entity;
}

Matrix Grid::getMatrix() const
{
	return matrix_;
}
