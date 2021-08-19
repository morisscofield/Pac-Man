#include "Entity.h"

Entity::Entity() :
		width_(1), length_(1), status_(true)
{
	setHitbox(0, 0);
}

Entity::~Entity()
{

}

Entity::Entity(const Coordinates & position, const Coordinates & dimentions) :
		width_(dimentions.getX()), length_(dimentions.getY()), status_(true)
{
	if (position.getX() < 0 || position.getY() < 0)
		throw InvalidDimentions {};
	if (width_ <= 0 || length_ <= 0)
		throw InvalidCoordinates {};

	setHitbox(position.getX(), position.getY());
}

Coordinates Entity::getPosition() const
{
	return hitBox_.topLeft;
}

Coordinates Entity::getDimentions() const
{
	return Coordinates{width_,length_};
}

HitBox Entity::getVerticies() const
{
	return hitBox_;
}

void Entity::setHitbox(const float &xPos, const float &yPos)
{
	hitBox_.topLeft.set(xPos, yPos);
	hitBox_.topRight.set(xPos + width_, yPos);
	hitBox_.bottomLeft.set(xPos, yPos + length_);
	hitBox_.bottomRight.set(xPos + width_, yPos + length_);
}

bool Entity::isAlive() const
{
	return status_;
}

void Entity::kill()
{
	status_ = false;
}

void Entity::resurrect()
{
	status_ = true;
}


