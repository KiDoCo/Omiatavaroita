#pragma once

#include <string>

class PlayerClass
{
public:
	PlayerClass(std::string setname, std::string setrace);
	~PlayerClass();
	void TakeDamage(int amount);
	void PrintInfo(std::string dName, std::string dRace);

private:
	int level;
	float speed;
	float damage;
	int health;
	std::string name;
	std::string race;
};

