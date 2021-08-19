#include "SeparatingAxisTheorem.h"

bool SeparatingAxisTheorem::isOverlapping(const HitBox & entity1, const HitBox & entity2)
{
	if(!axis_.empty())
		axis_.clear();

	createAxes(entity1, entity2);

	return isProjectionOverlapping(entity1, entity2);
}

Coordinates SeparatingAxisTheorem::normalizeAxes(const Coordinates & axis)
{
	auto magnitude = sqrt(pow(axis.getX(),2) + pow(axis.getY(),2));

	return Coordinates{float(axis.getX()/magnitude), float(axis.getY()/magnitude)};
}

void SeparatingAxisTheorem::createAxes(const HitBox & entity1, const HitBox & entity2)
{
	auto entity1_x = entity1.topRight.getX() - entity1.topLeft.getX();
	auto entity1_y = entity1.topRight.getY() - entity1.topLeft.getY();
	axis_.push_back(normalizeAxes(Coordinates{entity1_x, entity1_y}));

	entity1_x = entity1.topRight.getX() - entity1.bottomRight.getX();
	entity1_y = entity1.topRight.getY() - entity1.bottomRight.getY();
	axis_.push_back(normalizeAxes(Coordinates{entity1_x, entity1_y}));

	entity1_x = entity1.topLeft.getX() - entity1.bottomLeft.getX();
	entity1_y = entity1.topLeft.getY() - entity1.bottomLeft.getY();
	axis_.push_back(normalizeAxes(Coordinates{entity1_x, entity1_y}));

	entity1_x = entity1.topLeft.getX() - entity1.topRight.getX();
	entity1_y = entity1.topLeft.getY() - entity1.topRight.getY();
	axis_.push_back(normalizeAxes(Coordinates{entity1_x, entity1_y}));
}

float SeparatingAxisTheorem::calculateDot(const Coordinates & pointA, const Coordinates & pointB)
{
	auto dotProduct = (pointA.getX() * pointB.getX()) + (pointA.getY() * pointB.getY());
	return dotProduct;
}

Coordinates SeparatingAxisTheorem::projectAxes(const Coordinates & axis, const HitBox & verticies)
{
	auto projectedVerticies = vector<Coordinates>{};
	auto axisMagnitude = pow(axis.getX(),2) + pow(axis.getY(),2);

	auto dotProduct = calculateDot(verticies.topLeft, axis)/axisMagnitude;
	projectedVerticies.push_back(Coordinates(dotProduct * axis.getX(), dotProduct * axis.getY()));
	dotProduct = calculateDot(verticies.topRight, axis)/axisMagnitude;
	projectedVerticies.push_back(Coordinates(dotProduct * axis.getX(), dotProduct * axis.getY()));
	dotProduct = calculateDot(verticies.bottomLeft, axis)/axisMagnitude;
	projectedVerticies.push_back(Coordinates(dotProduct * axis.getX(), dotProduct * axis.getY()));
	dotProduct = calculateDot(verticies.bottomRight, axis)/axisMagnitude;
	projectedVerticies.push_back(Coordinates(dotProduct * axis.getX(), dotProduct * axis.getY()));

	auto minimumProjection = calculateDot(axis, projectedVerticies.at(0));
	auto maximumProjection = minimumProjection;

	for(auto vertex: projectedVerticies)
	{
		auto projection = calculateDot(axis, vertex);

		if(projection < minimumProjection)
			minimumProjection = projection;
		else if(projection > maximumProjection)
			maximumProjection = projection;
	}

	return Coordinates{minimumProjection, maximumProjection};
}

bool SeparatingAxisTheorem::isProjectionOverlapping(const HitBox & entity1, const HitBox & entity2)
{
	for(auto axis: axis_)
	{
		auto projectionA = projectAxes(axis, entity1);
		auto projectionB = projectAxes(axis, entity2);

		auto overlap = projectionB.getX() <= projectionA.getY() && projectionB.getY() >= projectionA.getX();

		if(!overlap)
			return false;
	}

	return true;
}

