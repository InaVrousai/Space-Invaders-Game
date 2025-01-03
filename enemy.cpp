#include "enemy.h"

void Enemy::init()
{

}

void Enemy::draw() 
{
}

void Enemy::update(float dt)
{
}

void Enemy::takeDamage(int damage)
{
	if (health >= damage)
		health -= damage;
	else
		health = 0;
}
