#pragma once

#include "EnemyBase.h"

class BowlingBall : public EnemyBaseClass
{
public:
	BowlingBall(int health, float speed, float range, int levela);
private:
	void Roll();

};

