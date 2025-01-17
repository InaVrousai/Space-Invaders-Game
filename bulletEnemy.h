pragma once
#include <sgg/graphics.h>
#include "enemy.h"

class bulletEnemy :public GameObject, public Collision
{
public:
	bulletEnemy(GameState* gs, const std::string& name);

	void init(float x, float y) override;
	void draw() override;
	void update(float dt) override;
	float getPosX() const { return this->x; }
	float getPosY() const { return this->y; }
	void setPosX(float x) { this->x = x; }
	void setPosY(float y) { this->y = y; }
	float getDamage() const { return damage; }
	Disk getCollisionDisk()const override;

protected:
	float speed = 7.0f;
	float x = 0.0f;
	float y = 0.0f;
	const float damage = 1.0f;
	const float b_en_size = 2.0f;
	graphics::Brush bulletBrush;
};

