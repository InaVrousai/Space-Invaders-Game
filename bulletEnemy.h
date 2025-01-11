#pragma once
#include <sgg/graphics.h>
#include "enemy.h"

class bulletEnemy:public GameObject
{
public:
	bulletEnemy(GameState* gs, const std::string& name);
	void fireBullet();
	void init() override;
	void draw() override;
	void update(float dt) override;

private:
	float speed;
	float x;
	float y;
	graphics::Brush bulletBrush;
};


