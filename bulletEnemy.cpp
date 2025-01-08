#include "bulletEnemy.h"

bulletEnemy::bulletEnemy(GameState* gs, const std::string& name)
{
	GameObject(gs, name);
	x = Enemy::getPosX();
	y = Enemy::getPosY();
}

void bulletEnemy::fireBullet()
{
}

void bulletEnemy::init() 
{
	bulletBrush.outline_opacity = 0.0f;
	bulletBrush.fill_opacity = 1.0f;
	bulletBrush.fill_color[0] = 1.0f;
	bulletBrush.fill_color[1] = 0.0f;
	bulletBrush.fill_color[2] = 0.0f;
	//bulletBrush.texture = "";
}

void bulletEnemy::draw()
{
	if (!isActive()) return;
	graphics::drawRect(x, y, 1.0f, 1.0f, bulletBrush);
}

void bulletEnemy::update(dt)
{
	y += speed * (dt / 1000.0f);
	//outofbound deactivation
	if (y < 0) setActive(false);
}