#include "GameEngine.h"

GameEngine::GameEngine(const Coordinates & gridSize, const Coordinates & screenDimentions, ifstream & mazeFile) :
		presentation_(screenDimentions), grid_(make_shared<Grid>(gridSize, screenDimentions,mazeFile)), maze_(grid_), fruits_(grid_),
		pacman_(grid_), ghostHandler_(grid_), gatesAndKeys_(grid_), state_(ScreenStates::SPLASHSCREEN)
{
}

void GameEngine::runGame()
{

	while(presentation_.isWindowOpen())
	{
		auto dir = presentation_.getKeyInputs();

		switch(state_)
		{
		case ScreenStates::SPLASHSCREEN:
			presentation_.drawSplashScreen(state_);
			if(dir == Direction::SPACE)
				state_ = ScreenStates::GAMESCREEN;
			break;
		case ScreenStates::GAMESCREEN:
			playGame(dir);
			break;
		case ScreenStates::GAMEOVER:
			presentation_.drawSplashScreen(state_);
			if(dir == Direction::SPACE)
				presentation_.close();
			break;
		case ScreenStates::GAMEWIN:
			presentation_.drawSplashScreen(state_);
			if(dir == Direction::SPACE)
				presentation_.close();
			break;
		}

		presentation_.render();
	}
}

void GameEngine::playGame(const Direction & dir)
{
	pacman_.move(dir);
	fruits_.fruitColissions(pacman_);
	ghostHandler_.moveGhosts();

	if(ghostHandler_.isGhostColission(pacman_))
		state_ = ScreenStates::GAMEOVER;

	if(fruits_.isPelletCollision(pacman_))
		ghostHandler_.scareGhosts();

	if(fruits_.noPelletsLeft())
		state_ = ScreenStates::GAMEWIN;

	gatesAndKeys_.keyColissions(pacman_);
	maze_.drawWalls(presentation_);
	fruits_.drawFruitsAndPellets(presentation_);
	gatesAndKeys_.drawGatesAndKeys(presentation_);
	ghostHandler_.drawGhosts(presentation_);
	presentation_.drawPacMan(pacman_);
}
