#include "enemy.h"
#include "defines.h"
#include "bulletEnemy.h"
#include "gamestate.h"
#include <sgg/graphics.h>

void Enemy::init(float x, float y)
{
	setPosX(x);
	setPosY(y);
}

void Enemy::draw()
{
	brush_en.fill_opacity = 1.0f;
	brush_en.outline_opacity = 0.0f;
	brush_en.texture = ASSET_PATH + std::string("spaceship.png");
	SETCOLOR(brush_en.fill_color, 1.0f, 0.0f, 0.0f);
	graphics::drawRect(getPosX(), getPosY(), 3.0f, 3.0f, brush_en);
}

void Enemy::takeDamage(int damage)
{
	if (health >= damage)
		health -= damage;
	else
		health = 0;
}

void Enemy::shoot()
{
	if (!isActive()) { return; }

	bulletEnemy* bullet = new bulletEnemy(m_state, "EnemyBullet");
	bullet->init(getPosX(), getPosY());
	m_state->addBullet(bullet);
}

Enemy::Enemy(GameState* gs, const std::string& name)
	:GameObject(gs, name)
{
	//initialize enemy position
	x = 5.0f;
	y = 5.0f;
}

void Enemy::update(float dt)
{
	shoot_timer += dt / 1000.0f; // Convert to seconds
	if (shoot_timer >= shoot_interval) {
		shoot_timer = 0.0f; // Reset timer
		shoot();
	}
	setPosX(getPosX() + speed * dir * dt * 0.005f);
	speed += 0.001f;

	if (isDead()) { setActive(false); return; }
	//Boundary check:
	/*if (getPosX() < 0 || getPosX() > CANVAS_WIDTH ||
		getPosY() < 0 || getPosY() > CANVAS_HEIGHT) {
		setActive(false); // Deactivate the enemy
	}*/
	//Change directions in the boundaries
	if (getPosX() < 0 || getPosX() > CANVAS_WIDTH)
	{
		dir *= -1;
	}
}

//takeDamage when enemy gets hit by bulletPlayer