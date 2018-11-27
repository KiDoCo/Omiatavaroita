#pragma once

#include <iostream>
#include <string>

class EnemyBaseClass
{
public:
	EnemyBaseClass();
	EnemyBaseClass(int healthamount, float speedamount, float rangeamount);
	~EnemyBaseClass();
	void TakeDamage(int amount);
	void DealDamage(int amount, class PlayerClass *object);
	void PrintInfo(std::string dName, std::string dRace);

protected:
	int health;
	float speed;
	float range;
	float damage;
	std::string name;
	std::string race;
	///declaring pure function
	virtual void Ability(class PlayerClass *object) = 0;
	int level;
};


