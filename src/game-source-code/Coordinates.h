#ifndef COORDINATES_H_
#define COORDINATES_H_


class Coordinates
{
public:
	Coordinates();
	Coordinates(const float & x, const float & y);
	bool operator==(const Coordinates& rhs) const;
	void setX(const float & x);
	void setY(const float & y);
	void set(const float & x, const float & y);
	float getX() const;
	float getY() const;
private:
	float x_;
	float y_;
};

#endif
