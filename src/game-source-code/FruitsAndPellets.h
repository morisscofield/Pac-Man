#ifndef FRUITSANDPELLETS_H_
#define FRUITSANDPELLETS_H_
#include <algorithm>
#include <vector>
#include "Entity.h"
#include "Grid.h"
#include "Presentation.h"
#include "Pacman.h"
#include "SeparatingAxisTheorem.h"
using namespace std;
using EntityVec = std::vector<Entity>;

class FruitsAndPellets
{
public:
	FruitsAndPellets(shared_ptr<Grid> & grid);
	void drawFruitsAndPellets(Presentation & presentation) const;
	void fruitColissions(const Pacman & pacman);
	bool isPelletCollision(const Pacman & pacman);
	bool noPelletsLeft() const;
	EntityVec getFruits() const;
	EntityVec getPellets() const;
private:
	shared_ptr<Grid> & grid_;
	const float width_;
	const float height_;
	SeparatingAxisTheorem colissions_;
	EntityVec fruits_;
	EntityVec powerPellets_;
	void checkColissions(int & index, bool & eaten, const Pacman & pacman, const EntityVec & enVec);
};
#endif
