#ifndef MAZE_H_
#define MAZE_H_
#include "Entity.h"
#include "Grid.h"
#include "Presentation.h"
#include <vector>
#include <algorithm>
using namespace std;
using EntityVec = std::vector<Entity>;

class Maze
{
public:
	Maze(shared_ptr<Grid> & grid);
	void drawWalls(Presentation & presentation) const;
	EntityVec getWalls() const;
private:
	shared_ptr<Grid> & grid_;
	const float widthV_;
	const float heightShortV_;
	const float heightH_;
	const float widthShortH_;
	const float xOffset_;
	const float yOffset_;
	EntityVec wallCoords_;
	void generateMaze();
	void generateWall(const int & row, const int & col);
	void horizontalWall(const int & row, const int & col);
	void verticalWall(const int & row, const int & col);
	void topLeftWall(const int & row, const int & col);
	void topRightWall(const int & row, const int & col);
	void bottomRightWall(const int & row, const int & col);
	void bottomLeftWall(const int & row, const int & col);
};

#endif
