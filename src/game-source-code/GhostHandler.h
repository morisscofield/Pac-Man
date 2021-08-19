#ifndef GHOSTHANDLER_H_
#define GHOSTHANDLER_H_
#include "RedGhost.h"
#include "InkyGhost.h"
#include "BlinkyGhost.h"
#include "ClydeGhost.h"
#include "Pacman.h"
#include "Presentation.h"
#include "SeparatingAxisTheorem.h"
#include "Stopwatch.h"
using namespace std;

class GhostHandler
{
public:
	GhostHandler(shared_ptr<Grid> & grid);
	void moveGhosts();
	bool isGhostColission(const Pacman & pacman);
	void scareGhosts();
	bool handleColissions(const GhostColour & colour);
	void drawGhosts(Presentation & presentation) const;
private:
	bool scared_;
	float scaredDuration_;
	RedGhost red_;
	InkyGhost inky_;
	BlinkyGhost blinky_;
	ClydeGhost clyde_;
	SeparatingAxisTheorem colissions_;
	Stopwatch timer_;
};

#endif
