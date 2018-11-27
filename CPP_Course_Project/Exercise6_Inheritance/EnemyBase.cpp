
#include "EnemyBase.h"
#include "Player.h"

EnemyBaseClass::EnemyBaseClass(int healthamount, float speedamount, float rangeamount)
{
	health = healthamount;
	speed = speedamount;
	range = rangeamount;
}
EnemyBaseClass::EnemyBaseClass()
{
	health = 1;
	speed = 1;
	range = 1;
}

EnemyBaseClass::~EnemyBaseClass()
{
	std::cout << name << " has been Defeated" << "\n";
	system("clear");
}

void EnemyBaseClass::TakeDamage(int amount)
{
	health -= amount;
}

void EnemyBaseClass::DealDamage(int amount, PlayerClass *object)
{
	object->TakeDamage(amount);
}

void EnemyBaseClass::PrintInfo(std::string dName, std::string dRace)
{
	try
	{
		std::cout << "You are facing " << dName << std::endl;
		std::cout << "And it seems to be a type of " << dRace << std::endl;

	}
	catch (const std::exception& e)
	{
		std::cout << "Exception occurred" << e.what() << std::endl;
	}
}
