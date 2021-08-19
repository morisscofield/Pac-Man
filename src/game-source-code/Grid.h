#ifndef GRID_H_
#define GRID_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include "Coordinates.h"
#include "GhostColour.h"
using namespace std;
using Matrix = vector<vector<int> >;

class Grid
{
public:
	Grid(const Coordinates & gridSize, const Coordinates & screenDimentions, ifstream & mazeFile);
	Matrix getMatrix() const;
	void clearSpace(const Coordinates & gridPos);
	Coordinates getBlockDimentions() const;
	Coordinates convertToGridPos(const float & screenWidth, const float & screenHeight) const;
	Coordinates convertToScreenPos(const int & gridRow, const int & gridCol) const;
	Coordinates getScreenDimentions() const;
	Coordinates getPacInitialPos() const;
	Coordinates getGhostPos(const GhostColour & ghost) const;
private:
	Coordinates screen_;
	Coordinates pacPos_;
	Matrix matrix_;
	const float blockWidth_;
	const float blockHeight_;
	void readMaze(ifstream & mazeFile);
	void resizeMatrix(const int &width, const int &height);
	Coordinates findEntity(const int & entity) const;
};

#endif
