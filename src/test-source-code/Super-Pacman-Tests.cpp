#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <fstream>
#include <memory.h>
#include "../game-source-code/Coordinates.h"
#include "../game-source-code/Entity.h"
#include "../game-source-code/Grid.h"
#include "../game-source-code/Maze.h"
#include "../game-source-code/FruitsAndPellets.h"
#include "../game-source-code/Pacman.h"
#include "../game-source-code/SeparatingAxisTheorem.h"
#include "../game-source-code/RedGhost.h"
#include "../game-source-code/BlinkyGhost.h"
#include "../game-source-code/InkyGhost.h"
#include "../game-source-code/ClydeGhost.h"
#include "../game-source-code/Stopwatch.h"

TEST_CASE("Coordinate Tests")
{
	SUBCASE("A default coordinate object is initialized correctly")
	{
		auto coordinates = Coordinates{};
		CHECK(coordinates.getX() == 0);
		CHECK(coordinates.getY() == 0);
	}

	SUBCASE("A coordinate object is initialized correctly")
	{
		auto coordinates = Coordinates{3.1f, 6.8f};
		CHECK(coordinates.getX() == 3.1f);
		CHECK(coordinates.getY() == 6.8f);
	}

	SUBCASE("The x-coordinate is set correctly")
	{
		auto coordinates = Coordinates{2.5f, 9.3f};
		coordinates.setX(4.5f);
		CHECK(coordinates.getX() == 4.5f);
		CHECK(coordinates.getY() == 9.3f);
	}

	SUBCASE("The y-coordinate is set correctly")
	{
		auto coordinates = Coordinates{8.9f, 16.8f};
		coordinates.setY(32.5f);
		CHECK(coordinates.getX() == 8.9f);
		CHECK(coordinates.getY() == 32.5f);
	}

	SUBCASE("Identical coordinates are equal")
	{
		auto coordinate1 = Coordinates{13.8f, 23.6f};
		auto coordinate2 = Coordinates{13.8f, 23.6f};
		CHECK(coordinate1 == coordinate2);
	}

	SUBCASE("Coordinates with different x values are not equal")
	{
		auto coordinate1 = Coordinates{7.8f, 23.6f};
		auto coordinate2 = Coordinates{13.3f, 23.6f};
		CHECK_FALSE(coordinate1 == coordinate2);
	}

	SUBCASE("Coordinates with different x values are not equal")
	{
		auto coordinate1 = Coordinates{7.8f, 23.6f};
		auto coordinate2 = Coordinates{7.8f, 12.9f};
		CHECK_FALSE(coordinate1 == coordinate2);
	}

	SUBCASE("Different coordinates are not equal")
	{
		auto coordinate1 = Coordinates{7.8f, 23.6f};
		auto coordinate2 = Coordinates{13.6f, 12.9f};
		CHECK_FALSE(coordinate1 == coordinate2);
	}

}

TEST_CASE("Entity Tests")
{
	SUBCASE("A default entity's vertices are returned correctly")
	{
		auto entity = Entity {};
		CHECK(entity.getVerticies().topLeft.getX() == 0);
		CHECK(entity.getVerticies().topLeft.getY() == 0);
		CHECK(entity.getVerticies().topRight.getX() == 1);
		CHECK(entity.getVerticies().topRight.getY() == 0);
		CHECK(entity.getVerticies().bottomLeft.getX() == 0);
		CHECK(entity.getVerticies().bottomLeft.getY() == 1);
		CHECK(entity.getVerticies().bottomRight.getX() == 1);
		CHECK(entity.getVerticies().bottomRight.getY() == 1);
	}

	SUBCASE("A default entity's position is returned correctly")
	{
		auto entity = Entity {};
		CHECK(entity.getPosition().getX() == 0);
		CHECK(entity.getPosition().getY() == 0);
	}

	SUBCASE("An entity's vertices are initialized correctly")
	{
		auto x = 3.6f;
		auto y = 5.2f;
		auto width = 6.9f;
		auto length = 5.6f;
		auto entity = Entity {Coordinates{x, y}, Coordinates{width, length}};
		CHECK(entity.getVerticies().topLeft.getX() == x);
		CHECK(entity.getVerticies().topLeft.getY() == y);
		CHECK(entity.getVerticies().topRight.getX() == x + width);
		CHECK(entity.getVerticies().topRight.getY() == y);
		CHECK(entity.getVerticies().bottomLeft.getX() == x);
		CHECK(entity.getVerticies().bottomLeft.getY() == y + length);
		CHECK(entity.getVerticies().bottomRight.getX() == x + width);
		CHECK(entity.getVerticies().bottomRight.getY() == y + length);
	}

	SUBCASE("An entity's position is initialized correctly")
	{
		auto x = 3.6f;
		auto y = 5.2f;
		auto width = 6.9f;
		auto length = 5.6f;
		auto entity = Entity {Coordinates{x, y}, Coordinates{width, length}};
		CHECK(entity.getPosition().getX() == x);
		CHECK(entity.getPosition().getY() == y);

	}

	SUBCASE("An entity can be killed")
	{
		auto entity = Entity {};
		CHECK(entity.isAlive() == true);
		entity.kill();
		CHECK(entity.isAlive() == false);
	}

	SUBCASE("An entity can be resurrected")
	{
		auto entity = Entity {};
		CHECK(entity.isAlive() == true);
		entity.kill();
		CHECK(entity.isAlive() == false);
		entity.resurrect();
		CHECK(entity.isAlive() == true);
	}
}

TEST_CASE("Grid Tests")
{
	auto gridSize = Coordinates(23,25);
	auto screenDimentions = Coordinates(920,750);

	SUBCASE("A maze is properly loaded from a file")
	{
		auto file = std::ifstream("Maze.txt");
		CHECK(file.is_open());
		file.close();
	}

	auto file = std::ifstream("Maze.txt");
	auto grid = Grid(gridSize, screenDimentions, file);

	SUBCASE("The grid dimentions are prperly set")
	{
		auto matrix = grid.getMatrix();
		CHECK(matrix.size() == 25); // Rows
		CHECK(matrix.at(0).size() == 23); //Columns
	}

	SUBCASE("The screen dimensions of a grid block are returned properly")
	{
		auto dimensions = grid.getBlockDimentions();
		CHECK(dimensions.getX() == 40);
		CHECK(dimensions.getY() == 30);
	}

	SUBCASE("A block's screen coordinates can be converted to a grid position")
	{
		auto position = grid.convertToGridPos(0, 0);
		CHECK(position.getX() == 0);
		CHECK(position.getY() == 0);

		position = grid.convertToGridPos(40, 30);
		CHECK(position.getX() == 1);
		CHECK(position.getY() == 1);

		position = grid.convertToGridPos(79, 59);
		CHECK(position.getX() == 1);
		CHECK(position.getY() == 1);

		position = grid.convertToGridPos(79.999, 59.999);
		CHECK(position.getX() == 1);
		CHECK(position.getY() == 1);

		position = grid.convertToGridPos(80, 60);
		CHECK(position.getX() == 2);
		CHECK(position.getY() == 2);

		position = grid.convertToGridPos(120, 60);
		CHECK(position.getX() == 3);
		CHECK(position.getY() == 2);

		position = grid.convertToGridPos(910, 740);
		CHECK(position.getX() == 22);
		CHECK(position.getY() == 24);
	}

	SUBCASE("A block's grid position can be converted to screen coordinates")
	{
		auto position = grid.convertToScreenPos(0, 0);
		CHECK(position.getX() == 0);
		CHECK(position.getY() == 0);

		position = grid.convertToScreenPos(1, 1);
		CHECK(position.getX() == 40);
		CHECK(position.getY() == 30);

		position = grid.convertToScreenPos(2, 1);
		CHECK(position.getX() == 40);
		CHECK(position.getY() == 60);

		position = grid.convertToScreenPos(1, 2);
		CHECK(position.getX() == 80);
		CHECK(position.getY() == 30);

		position = grid.convertToScreenPos(24, 22);
		CHECK(position.getX() == 880);
		CHECK(position.getY() == 720);
	}

	file.close();
}

TEST_CASE("Static Object Tests")
{
	auto file = std::ifstream("Maze.txt");
	auto grid = std::make_shared <Grid> (Coordinates(23,25), Coordinates(920,750), file);

	SUBCASE("The correct number of maze wall objects is returned")
	{
		auto maze = Maze(grid);
		auto counter = 0;
		for(auto mat: grid->getMatrix())
			for(auto index: mat)
			{
				if(index == 1 || index == 2)
					counter ++;
				if(index == 3 || index == 4 ||
				   index == 5 || index == 6)
					counter +=2;
			}

		CHECK(maze.getWalls().size() == counter);
	}

	SUBCASE("The correct number of fruit objects is returned")
	{
		auto fruits = FruitsAndPellets(grid);
		auto counter = 0;

		for(auto mat: grid->getMatrix())
			for(auto index: mat)
				if(index == 7)
					counter++;

		CHECK(fruits.getFruits().size() == counter);
	}

	file.close();
}

TEST_CASE("Collision Tests")
{

	auto collisions = SeparatingAxisTheorem{};
	SUBCASE("Objects not overlapping are not colliding")
	{
		auto entity1 = Entity{Coordinates{10,10},Coordinates{10,10}};
		auto entity2 = Entity{Coordinates{30,10},Coordinates{10,10}};

		CHECK_FALSE(collisions.isOverlapping(entity1.getVerticies(), entity2.getVerticies()));
		CHECK_FALSE(collisions.isOverlapping(entity2.getVerticies(), entity1.getVerticies()));
	}

	SUBCASE("Overlapping objects are colliding")
	{
		auto entity1 = Entity{Coordinates{10,10},Coordinates{10,10}};
		auto entity2 = Entity{Coordinates{15,15},Coordinates{10,10}};

		CHECK(collisions.isOverlapping(entity1.getVerticies(), entity2.getVerticies()));
		CHECK(collisions.isOverlapping(entity2.getVerticies(), entity1.getVerticies()));
	}

	SUBCASE("Overlapping objects of different sizes are colliding")
	{
		auto entity1 = Entity{Coordinates{13,15},Coordinates{12,5}};
		auto entity2 = Entity{Coordinates{16,18},Coordinates{2,7}};

		CHECK(collisions.isOverlapping(entity1.getVerticies(), entity2.getVerticies()));
		CHECK(collisions.isOverlapping(entity2.getVerticies(), entity1.getVerticies()));
	}

	SUBCASE("Objects that are barely touching are colliding")
	{
		auto entity1 = Entity{Coordinates{36,9},Coordinates{8,5}};
		auto entity2 = Entity{Coordinates{44,11},Coordinates{13,7}};

		CHECK(collisions.isOverlapping(entity1.getVerticies(), entity2.getVerticies()));
		CHECK(collisions.isOverlapping(entity2.getVerticies(), entity1.getVerticies()));
	}
}

TEST_CASE("Pacman Tests")
{
	auto file = std::ifstream("Maze.txt");
	auto grid = std::make_shared <Grid> (Coordinates(23,25), Coordinates(920,750), file);
	auto pacman = Pacman(grid);

	SUBCASE("Pacman's position is initialized correctly")
	{
		CHECK(pacman.getPosition() == grid->getPacInitialPos());
	}

	SUBCASE("Pacman's size is initialized correctly")
	{
		auto size = pacman.getDimentions();
		CHECK(size.getX() == grid->getBlockDimentions().getY()/2);
		CHECK(size.getY() == grid->getBlockDimentions().getY()/2);
	}

	SUBCASE("Pacman's movement step is initialized correctly")
	{
		auto step = pacman.getStep();
		CHECK(step.getX() == 3);
		CHECK(step.getY() == 3);
	}

	SUBCASE("Pacman can move up")
	{
		auto oldPosition = pacman.getPosition();
		pacman.move(Direction::UP);
		auto newPosition = pacman.getPosition();
		CHECK(newPosition.getX() == oldPosition.getX());
		CHECK(newPosition.getY() == oldPosition.getY() - pacman.getStep().getY());
	}

	SUBCASE("Pacman can move down")
	{
		auto oldPosition = pacman.getPosition();
		pacman.move(Direction::DOWN);
		auto newPosition = pacman.getPosition();
		CHECK(newPosition.getX() == oldPosition.getX());
		CHECK(newPosition.getY() == oldPosition.getY() + pacman.getStep().getY());
	}

	SUBCASE("Pacman can move left")
	{
		auto oldPosition = pacman.getPosition();
		pacman.move(Direction::LEFT);
		auto newPosition = pacman.getPosition();
		CHECK(newPosition.getX() == oldPosition.getX() - pacman.getStep().getX());
		CHECK(newPosition.getY() == oldPosition.getY());
	}

	SUBCASE("Pacman can move right")
	{
		auto oldPosition = pacman.getPosition();
		pacman.move(Direction::RIGHT);
		auto newPosition = pacman.getPosition();
		CHECK(newPosition.getX() == oldPosition.getX() + pacman.getStep().getX());
		CHECK(newPosition.getY() == oldPosition.getY());
	}

	file.close();
}

TEST_CASE("Ghost Tests")
{
	auto file = std::ifstream("Maze.txt");
	auto grid = std::make_shared <Grid> (Coordinates(23,25), Coordinates(920,750), file);
	auto red = RedGhost{grid};
	auto blinky = BlinkyGhost{grid};
	auto inky = InkyGhost{grid};
	auto clyde = ClydeGhost{grid};

	SUBCASE("A Ghost's position is initialized correctly")
	{
		CHECK(red.getPosition() == grid->getGhostPos(GhostColour::RED));
		CHECK(blinky.getPosition() == grid->getGhostPos(GhostColour::BLINKY));
		CHECK(inky.getPosition() == grid->getGhostPos(GhostColour::INKY));
		CHECK(clyde.getPosition() == grid->getGhostPos(GhostColour::CLYDE));
	}

	SUBCASE("A Ghost's size is initialized correctly")
	{
		auto size = Coordinates{float(grid->getBlockDimentions().getY() / 1.2), float(grid->getBlockDimentions().getY() / 1.2)};
		CHECK(red.getDimentions() == size);
		CHECK(blinky.getDimentions() == size);
		CHECK(inky.getDimentions() == size);
		CHECK(clyde.getDimentions() == size);
	}

	SUBCASE("A Ghost's movement step is correctly initialised")
	{
		CHECK(red.getStep().getX() == 1.5);
		CHECK(red.getStep().getY() == 1.5);
		CHECK(blinky.getStep().getX() == 1.5);
		CHECK(blinky.getStep().getY() == 1.5);
		CHECK(inky.getStep().getX() == 1.5);
		CHECK(inky.getStep().getY() == 1.5);
		CHECK(clyde.getStep().getX() == 1.5);
		CHECK(clyde.getStep().getY() == 1.5);
	}

	file.close();
}

TEST_CASE("Stopwatch Tests")
{

	SUBCASE("A stopwatch is correctly initialized")
	{
		auto stopwatch = Stopwatch{};
		CHECK(stopwatch.getTimeElapsed() == 0);
		CHECK(stopwatch.isRunning() == false);
	}

	SUBCASE("A stopwatch runs correctly")
	{
		cout << endl << "Please allow for at least 5 seconds for the tests to complete" << endl;
		auto stopwatch = Stopwatch{};
		stopwatch.start();
		CHECK(stopwatch.isRunning() == true);

		while(stopwatch.getTimeElapsed() < 2.0f){}

		CHECK(stopwatch.getTimeElapsed() < 2.1f);
		CHECK(stopwatch.getTimeElapsed() > 1.9f);
		CHECK(stopwatch.isRunning() == true);
	}

	SUBCASE("A stopwatch stops correctly")
	{
		auto stopwatch = Stopwatch{};
		stopwatch.start();

		while(stopwatch.getTimeElapsed() < 2.0f){}

		stopwatch.stop();
		auto finalTime = stopwatch.getTimeElapsed();
		CHECK(finalTime < 2.1f);
		CHECK(finalTime > 1.9f);
		CHECK(stopwatch.isRunning() == false);
		CHECK(finalTime == stopwatch.getTimeElapsed());
	}
}
