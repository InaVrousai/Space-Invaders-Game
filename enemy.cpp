#include "enemy.h"
#include "bulletEnemy.h"
#include <sgg/graphics.h>
#include <iostream>
#include"defines.h"


Enemy::Enemy(GameState* gs, const std::string& name)
	: GameObject(gs, name), x(0.0f), y(0.0f), speed(0.0f), health(100)
{
	std::cout << "Enemy created: " << name << ", Speed: " << speed << ", Health: " << health << "\n";
}

void Enemy::init(float x, float y)
{
	setPosX(x);
	setPosY(y);

	std::cout << "Enemy initialized at: (" << x << ", " << y << ")\n";
}

void Enemy::draw()
{
	graphics::Brush br;
	br.texture = ASSET_PATH + std::string("enemy.png");
	br.outline_opacity = 0.0f;


	graphics::drawRect(x, y, ENEMY_WIDTH, ENEMY_HEIGHT, br); // Smaller enemy size
	//Show health bar
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f);
	br.fill_opacity = 0.0f;
	graphics::drawRect(x, y - 1.5f, 2.0f * (health / 100.0f), 0.3f, br); // Health proportional to full bar
}

void Enemy::update(float dt)
{

	// Move the enemy horizontally
	x += speed * dt * 0.0001f;
	if (speed > 1.0f) {
		speed -= 0.1f;
		if (speed < 1.0f) { speed = 1.0f; }
	}
	std::cout << "Updated Enemy Position: (" << x << ", " << y << "), Speed: " << speed << "\n";

	// Reverse direction if the enemy hits the canvas edges
	if (x <= 0.0f) {
		x = 0.0f;  // Clamp to the left edge
		speed = -speed; // Reverse direction
	}
	if (x >= CANVAS_WIDTH) {
		x = CANVAS_WIDTH; // Clamp to the right edge
		speed = -speed; // Reverse direction
	}

	// Log the updated position for debugging
	std::cout << "Updated Enemy Position: (" << x << ", " << y << "), Speed: " << speed << "\n";

}

void Enemy::takeDamage(int damage)
{
	health -= damage;
	std::cout << "Enemy took damage: " << damage << ", Remaining health: " << health << "\n";

	if (health <= 0) {
		health = 0;
		setActive(false); // Deactivate enemy when health reaches 0
		std::cout << "Enemy destroyed\n";
	}
}

Disk Enemy::getCollisionDisk() const
{
	Disk disk;
	disk.cx = x;          // x-coordinate of the enemy
	disk.cy = y;          // y-coordinate of the enemy
	disk.radius = ENEMY_WIDTH * 0.4f; // Smaller radius based on the enemy's width	return disk;
	return disk;
}