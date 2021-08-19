#ifndef SEPARATINGAXISTHEOREM_H_
#define SEPARATINGAXISTHEOREM_H_
#include "Entity.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class SeparatingAxisTheorem
{
public:
	bool isOverlapping(const HitBox & entity1, const HitBox & entity2);
private:
	vector<Coordinates> axis_;
	void createAxes(const HitBox & entity1, const HitBox & entity2);
	float calculateDot(const Coordinates & pointA, const Coordinates & pointB);
	Coordinates normalizeAxes(const Coordinates & axis);
	Coordinates projectAxes(const Coordinates & axis, const HitBox & verticies);
	bool isProjectionOverlapping(const HitBox & entity1, const HitBox & entity2);
};

#endif
