#include "GameEngine.h"
using namespace std;

int main()
{
	auto mazeFile = ifstream{"maze.txt"};
	auto engine = GameEngine{Coordinates(23,25),Coordinates(920,750),mazeFile};
	engine.runGame();
	mazeFile.close();
}
