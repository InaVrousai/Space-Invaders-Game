#include "enemy.h"
#include <sgg/graphics.h>

void Enemy::init()
{
	setPosX(en_x);
	setPosY(en_y);

	brush_en.fill_opacity = 1.0f;
	brush_en.texture = "";
}

void Enemy::draw()
{
	graphics::drawRect(getPosX(), getPosY(), 1.0f, 1.0f, brush_en);
}

void Enemy::takeDamage(int damage)
{
	if (health >= damage)
		health -= damage;
	else
		health = 0;
}

Enemy::Enemy(GameState* gs, const std::string& name)
	:GameObject(gs,name)
{
	//skefthka na arxikopoihte h thesh twn enemies edw
	en_x = 5.0f;
	en_y = 5.0f;
}

void Enemy::update(float dt)
{
	//gia ena xroniko diasthma na phgainei aristera,gia to idio panw klp.
	while (dt <= 50)
		if (dt <= 10)
			x += x * speed;
		else if (dt <= 20)
			speed += 0.1f;
			x -= x * speed;
		else if(dt<=40)
			speed += 0.1f;
			y -= y * speed;
		else
			speed -= 0.1f;
			y += y * speed;

	if (isDead())
		//delete?
	//Boundary check:
	/*if (x < 0 || x > m_state->getCanvasWidth() ||
		y < 0 || y > m_state->getCanvasHeight()) {
		setActive(false); // Deactivate the enemy
	}*/
	//takeDamage otan ton petyxainei bulletPlayer
	/*
	* if bullet gets enemy call takeDamage
	*/
			/*
			*/
}