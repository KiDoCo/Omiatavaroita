#include "BowlingBall.h"
#include "Player.h"

BowlingBall::BowlingBall(int healtha, float speeda, float rangea, int levela) : EnemyBaseClass(healtha, speeda, rangea)
{
	level = levela;
	damage = 2 * level;
	name = "BowlingBall";

}

///implementing function which was declared in baseclass
void BowlingBall::Ability(PlayerClass *object)
{
	DealDamage(speed * damage);
}




