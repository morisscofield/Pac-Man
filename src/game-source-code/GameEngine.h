#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_
#include "Presentation.h"
#include "Coordinates.h"
#include "FruitsAndPellets.h"
#include "Maze.h"
#include "Pacman.h"
#include "GhostHandler.h"
#include "GatesAndKeys.h"
#include "ScreenStates.h"

class GameEngine
{
public:
	GameEngine(const Coordinates & gridSize, const Coordinates & screenDimentions, ifstream & mazeFile);
	void runGame();
private:
	Presentation presentation_;
	shared_ptr<Grid> grid_;
	Maze maze_;
	FruitsAndPellets fruits_;
	Pacman pacman_;
	GhostHandler ghostHandler_;
	GatesAndKeys gatesAndKeys_;
	ScreenStates state_;
	void playGame(const Direction & dir);
};

#endif
