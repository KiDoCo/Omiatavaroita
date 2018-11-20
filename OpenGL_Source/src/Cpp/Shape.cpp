#include "src/Headers/Shape.h"

Shape::Shape(float setx, float sety, float setWidth, float setHeight)
{
	Width = setWidth;
	Height = setHeight;
	properties->x = setx;
	properties->y = sety;
}

Shape::~Shape()
{
}