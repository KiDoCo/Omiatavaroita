#pragma once
#include <iostream>
#include <string>

class Vector2D
{

	friend Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator*(const Vector2D &v1, float val);
	friend Vector2D operator*(const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator/(const Vector2D &v1, float val);
	friend std::ostream& operator<<(std::ostream &os, const Vector2D &v1);
	friend Vector2D Normalize(Vector2D &v1);
public:
	Vector2D(float x, float y);
	Vector2D();
	~Vector2D();
	std::string print();

private:
	float x;
	float y;
	bool normalized;
};

class  EvenNumb
{
public:

	void operator()(int a) { if (a % 2 == 0) print(a); };



	void print(int a) { std::cout << a << std::endl; };

};

class PrimeNumb
{
public:

	bool operator()(int b) {

		int  i, flag = 0;
		for (i = 2; i <= b / 2; ++i)
		{
			if (b % i == 0)
			{
				flag = 1;
				break;
			}
		}

		if (b == 1)
		{
			std::cout << "CRIKEY" << std::endl;
			return false;
		}
		else
		{
			return flag == 0;
		}
	};
};





