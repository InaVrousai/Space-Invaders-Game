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
	graphics::drawRect(getPosX(), getPosY(), 1.5f, 1.5f, brush_en);
}

void Enemy::takeDamage(int damage)
{
	if (health >= damage)
		health -= damage;
	else
		health = 0;
	setActive(false);
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
}

void Enemy::update(float dt)
{
	shoot_timer += dt / 1000.0f; // Convert to seconds
	if (shoot_timer >= shoot_idle) {
		shoot_timer = 0.0f; // Reset timer
		shoot();
	}
	setPosX(getPosX() + dirX * speed * dt * 0.005f);
	setPosY(getPosY() + speed * dirY * dt * 0.005f);
	speed += 0.001f;

	if (speed > max_speed) {
		speed -= slowdown_rate;
		if (speed < max_speed) { speed = max_speed; }
	}

	if (isDead()) { setActive(false); return; }
	//Change directions in the boundaries
	if (getPosX() < 0 || getPosX() > CANVAS_WIDTH)
	{
		dirX *= -1;
	}
	if (getPosY() < 0 || getPosY() > CANVAS_HEIGHT - 5.0f)
	{
		dirY *= -1;
	}
}

//takeDamage when enemy gets hit by bulletPlayer