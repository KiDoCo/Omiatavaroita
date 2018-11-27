#pragma once

#include "Player.h"
#include <iostream>

PlayerClass::PlayerClass(std::string setname, std::string setrace)
{
	name = setname;
	race = setrace;
}

PlayerClass::~PlayerClass()
{
	std::cout << "You have been slayed" << std::endl;
}

void PlayerClass::TakeDamage(int amount)
{
	
}

void PlayerClass::PrintInfo(std::string dName, std::string dRace)
{
	try
	{
		std::cout << "Your name is " << dName << std::endl;

		std::cout << "And you are a " << dRace << std::endl;

	}
	catch (const std::exception& e)
	{
		std::cout << "Exception error occurred: " << e.what() << std::endl;
	}
}