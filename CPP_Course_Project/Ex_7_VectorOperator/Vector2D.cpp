#include "Vector2D.h"
#include <sstream>
#include <cmath>

Vector2D::Vector2D(float setx, float sety)
{
	x = setx;
	y = sety;
}

Vector2D::Vector2D()
{

}

Vector2D::~Vector2D()
{
}

Vector2D operator+(const Vector2D &f1, const Vector2D &f2)
{
	Vector2D result;

	result.x = f2.x + f1.x;
	result.y = f2.y + f1.y;

	return result;
}

Vector2D operator-(const Vector2D &f1, const Vector2D &f2)
{
	Vector2D result;

	result.x = f2.x - f1.x;
	result.y = f2.y - f1.y;

	return result;
}

Vector2D operator*(const Vector2D &f1, float val)
{
	Vector2D result;

	result.x = f1.x * val;
	result.y = f1.y * val;

	return result;
}

Vector2D operator*(const Vector2D &f1, const Vector2D &f2)
{
	return Vector2D(f1.x*f2.x ,f1.y*f2.y);
}

Vector2D operator/(const Vector2D &f1, float val)
{
	Vector2D result;

	result.x = f1.x * (1 / val);
	result.y = f1.y * (1 / val);

	return result;
}

Vector2D Normalize(Vector2D &v1)
{
	if (!v1.normalized)
	{
		float vectorlenght = sqrt(pow(v1.x, 2)  * pow(v1.y, 2));
		v1.x = v1.x /vectorlenght;
		v1.y = v1.y /vectorlenght;
	}
	return v1;
}

std::ostream& operator<<(std::ostream &os, const Vector2D &v1)
{
	os << "X:" << v1.x << "Y:" << v1.y;
	return os;
}

std::string Vector2D::print()
{
	std::ostringstream temp;
	temp << x << "   " << y << std::endl;

	return temp.str();
}

