#include "Maze.h"

Maze::Maze(shared_ptr<Grid> & grid) : grid_(grid),
		widthV_(1.f/4 * grid_->getBlockDimentions().getX()), heightShortV_(2.f/3 * grid_->getBlockDimentions().getY()),
		heightH_(1.f/3 * grid_->getBlockDimentions().getY()), widthShortH_(5.f/8 * grid_->getBlockDimentions().getX()),
		xOffset_(3.f/8 * grid_->getBlockDimentions().getX()), yOffset_(1.f/3 * grid_->getBlockDimentions().getY())
{
	generateMaze();
}

void Maze::drawWalls(Presentation & presentation) const
{
	for_each(wallCoords_.begin(), wallCoords_.end(), [&presentation](auto wall){presentation.drawStatic(wall, EntityKey::WALL);});
}

void Maze::generateMaze()
{
	for(auto row = 0u; row < grid_->getMatrix().size(); row++)
		for(auto col = 0u; col < grid_->getMatrix().at(row).size(); col++)
			generateWall(row, col);
}

EntityVec Maze::getWalls() const
{
	return wallCoords_;
}

void Maze::generateWall(const int & row, const int & col)
{
	switch(grid_->getMatrix().at(row).at(col))
	{
	case 1:
		verticalWall(row, col);
		break;
	case 2:
		horizontalWall(row, col);
		break;
	case 3:
		topLeftWall(row, col);
		break;
	case 4:
		topRightWall(row, col);
		break;
	case 5:
		bottomLeftWall(row, col);
		break;
	case 6:
		bottomRightWall(row, col);
		break;
	default:
		break;
	}
}

void Maze::verticalWall(const int & row, const int & col)
{
	auto positionX = col * grid_->getBlockDimentions().getX() + xOffset_;
	auto positionY = row * grid_->getBlockDimentions().getY();

	wallCoords_.push_back(Entity{Coordinates{positionX,positionY}, Coordinates{widthV_,grid_->getBlockDimentions().getY()}});

}

void Maze::horizontalWall(const int & row, const int & col)
{
	auto positionX = col * grid_->getBlockDimentions().getX();
	auto positionY = row * grid_->getBlockDimentions().getY() + yOffset_;

	wallCoords_.push_back(Entity{Coordinates{positionX,positionY}, Coordinates{grid_->getBlockDimentions().getX(),heightH_}});
}

void Maze::topLeftWall(const int & row, const int & col)
{
	auto positionX = col * grid_->getBlockDimentions().getX() + xOffset_;
	auto positionY = row * grid_->getBlockDimentions().getY() + yOffset_;

	wallCoords_.push_back(Entity{Coordinates{positionX,positionY}, Coordinates{widthShortH_,heightH_}});
	wallCoords_.push_back(Entity{Coordinates{positionX,positionY}, Coordinates{widthV_,heightShortV_}});
}

void Maze::topRightWall(const int & row, const int & col)
{
	auto positionXH = col * grid_->getBlockDimentions().getX();
	auto positionXV = col * grid_->getBlockDimentions().getX() + xOffset_;
	auto positionY = row * grid_->getBlockDimentions().getY() + yOffset_;

	wallCoords_.push_back(Entity{Coordinates{positionXH,positionY}, Coordinates{widthShortH_,heightH_}});
	wallCoords_.push_back(Entity{Coordinates{positionXV,positionY}, Coordinates{widthV_,heightShortV_}});
}

void Maze::bottomLeftWall(const int & row, const int & col)
{
	auto positionX = col * grid_->getBlockDimentions().getX() + xOffset_;
	auto positionYH = row * grid_->getBlockDimentions().getY() + yOffset_;
	auto positionYV = row * grid_->getBlockDimentions().getY();

	wallCoords_.push_back(Entity{Coordinates{positionX,positionYH}, Coordinates{widthShortH_,heightH_}});
	wallCoords_.push_back(Entity{Coordinates{positionX,positionYV}, Coordinates{widthV_,heightShortV_}});
}

void Maze::bottomRightWall(const int & row, const int & col)
{
	auto positionXH = col * grid_->getBlockDimentions().getX();
	auto positionYH = row * grid_->getBlockDimentions().getY() + yOffset_;
	auto positionXV = col * grid_->getBlockDimentions().getX() + xOffset_;
	auto positionYV = row * grid_->getBlockDimentions().getY();

	wallCoords_.push_back(Entity{Coordinates{positionXH,positionYH}, Coordinates{widthShortH_,heightH_}});
	wallCoords_.push_back(Entity{Coordinates{positionXV,positionYV}, Coordinates{widthV_,heightShortV_}});
}
