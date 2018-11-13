#include "Vector2D.h"
#include <sstream>

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

std::string Vector2D::print()
{
	std::ostringstream temp;
	temp << x << "   " << y << std::endl;

	return temp.str();
}