#ifndef SHAPE_H
#define SHAPE_H

#include "Vector2D.h"

class Shape
{
public:
	Shape(float setx, float sety, float setWidth, float setHeight);
	~Shape();

	float GetWidth() { return Width; };
	float GetHeight() { return Height; };
	float GetX() { return properties->x; };
	float GetY() { return properties->y; };

private:
	Vector2D *properties;

	float Width;
	float Height;
};


#endif // !SHAPE_H

