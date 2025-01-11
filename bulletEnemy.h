#pragma once
#include <sgg/graphics.h>
#include "enemy.h"

class bulletEnemy :public GameObject
{
public:
	bulletEnemy(GameState* gs, const std::string& name);

	void init(float x, float y) override;
	void draw() override;
	void update(float dt) override;

protected:
	float speed = 7.0f;
	float x;
	float y;
	graphics::Brush bulletBrush;
};


