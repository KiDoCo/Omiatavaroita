#include "Vector2D.h"

int main()
{
	EvenNumb func;
	PrimeNumb funct;

	for (int i = 2; i < 100; i++)
	{
		if (funct(i))
		{
			std::cout << i << std::endl;
		}
	}
	
	return 1;
}

