#ifndef GATESANDKEYS_H_
#define GATESANDKEYS_H_
#include <vector>
#include <algorithm>
#include "Grid.h"
#include "Entity.h"
#include "Pacman.h"
#include "Presentation.h"
#include "SeparatingAxisTheorem.h"
using namespace std;
using EntityVec = std::vector<Entity>;

class GatesAndKeys
{
public:
	GatesAndKeys(shared_ptr<Grid> & grid);
	void drawGatesAndKeys(Presentation & presentation) const;
	void keyColissions(const Pacman & pacman);
private:
	shared_ptr<Grid> & grid_;
	float widthH_;
	float widthV_;
	float heightH_;
	float heightV_;
	float xOffset_;
	float yOffset_;
	float keyWidth_;
	float keyHeight_;
	EntityVec gates_;
	EntityVec keys_;
	SeparatingAxisTheorem colissions_;
	void generateGatesAndKeys();
	void generateKey();
	void deleteGate();
	void horizontalGate(const int & row, const int & col);
	void verticalGate(const int & row, const int & col);
	void generateKey(const int & row, const int & col);
};

#endif
