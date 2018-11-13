#pragma once
#include <iostream>
#include <string>

class Vector2D
{

	friend Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator-(const Vector2D &v1, const Vector2D &v2);

public:
	Vector2D(float x, float y);
	Vector2D();
	~Vector2D();
	std::string print();

private:
	float x;
	float y;

};



