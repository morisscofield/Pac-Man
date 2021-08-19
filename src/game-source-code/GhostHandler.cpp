#include "GhostHandler.h"

GhostHandler::GhostHandler(shared_ptr<Grid> & grid) :
		scared_(false), scaredDuration_(5.0f), red_(grid), inky_(grid), blinky_(grid), clyde_(grid)
{}

void GhostHandler::moveGhosts()
{
	red_.move();
	inky_.move();
	blinky_.move();
	clyde_.move();

	if (scared_ && timer_.getTimeElapsed() > scaredDuration_)
		scared_ = false;
}

bool GhostHandler::isGhostColission(const Pacman & pacman)
{
	if(colissions_.isOverlapping(pacman.getVerticies(), red_.getVerticies()))
		return handleColissions(GhostColour::RED);
	if(colissions_.isOverlapping(pacman.getVerticies(), inky_.getVerticies()))
		return handleColissions(GhostColour::INKY);
	if(colissions_.isOverlapping(pacman.getVerticies(), blinky_.getVerticies()))
		return handleColissions(GhostColour::BLINKY);
	if(colissions_.isOverlapping(pacman.getVerticies(), clyde_.getVerticies()))
		return handleColissions(GhostColour::CLYDE);

	return false;
}

bool GhostHandler::handleColissions(const GhostColour & colour)
{
	if(!scared_)
		return true;

	switch(colour)
	{
	case GhostColour::RED:
		red_.reset();
		break;
	case GhostColour::INKY:
		inky_.reset();
		break;
	case GhostColour::BLINKY:
		blinky_.reset();
		break;
	case GhostColour::CLYDE:
		clyde_.reset();
		break;
	default:
		break;
	}

	return false;
}

void GhostHandler::drawGhosts(Presentation & presentation) const
{
	if(!scared_)
	{
		presentation.draw(red_, EntityKey::RED);
		presentation.draw(inky_, EntityKey::INKY);
		presentation.draw(blinky_, EntityKey::BLINKY);
		presentation.draw(clyde_, EntityKey::CLYDE);
	}
	else
	{
		presentation.draw(red_, EntityKey::SCAREDGHOST);
		presentation.draw(inky_, EntityKey::SCAREDGHOST);
		presentation.draw(blinky_, EntityKey::SCAREDGHOST);
		presentation.draw(clyde_, EntityKey::SCAREDGHOST);

	}
}

void GhostHandler::scareGhosts()
{
	timer_.start();
	scared_ = true;
}
