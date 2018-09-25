#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>

using namespace std;

void arrayMethod(int*p, int arraylength);

void askArray(int *p, int arraylength);

void swapIntegers(int &a, int &b);

void PauseMethod();

int main()
{
	const int arrayLength = 5;

	int testArray[arrayLength] = { 5,10,60,120,198 };

	int *p = testArray;

	char input = ' ';

	const char inputKeys[arrayLength] = { 'a','b','c','q' };

	int first = 2;

	int second = 7;

	while(input != 'q')
	{

		input = getchar();

		if (input == 'a')
		{
			arrayMethod(p, arrayLength);
		}
		if (input == 'b')
		{
			askArray(p, arrayLength);
		}
		if (input == 'c')
		{
			std::cout << "value first " << first << "\n" << "value second" << second << std::endl;
			swapIntegers(first, second);
		}
		if (input == 'q')
		{
			std::cout << "Exiting" << "\n";
		}
		else
		{
			std::cout << "There is nothing for this key" << "\n";

		}

		PauseMethod();
	} 
	
	system("pause");

	return 1;
}

void arrayMethod(int *p, int arraylength)
{
	for (int i = 0; i < arraylength; i++)
	{
		std::cout << *(p + i) << "\n";
	}
	PauseMethod();
}


void askArray(int *p, int arraylength)
{
	for (int i = 0; i < arraylength; i++)
	{
		std::cout << "Give array value in: " << i << "\n";
		std::cin >> *(p + i);
	}
	std::cout << "Numbers have been assigned" << "\n";
	PauseMethod();
}

void swapIntegers(int &a, int &b)
{

	std::cout << "Swapping numbers" << "\n";
	int c = a;
	a = b;
	b = c;

	std::cout << "Numbers after conversion" << "\n";

	std::cout << "value first: " << a << "\n" << "value second: " << b << std::endl;

	PauseMethod();
}

void PauseMethod()
{
	std::cout << "Press Any key..." << "\n";
	system("pause");
	system("cls");
}

