#include "bulletPlayer.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <iostream>

BulletPlayer::BulletPlayer(GameState* gs, const std::string& name, float x, float y)
	:GameObject(gs, name), bx(x), by(y)
{
	init(x, y);
}

void BulletPlayer::init(float x, float y) {
	bx = x;
	by = y;
}

void BulletPlayer::draw() {
	if (by < 0 || by > CANVAS_HEIGHT) return;

	graphics::Brush br;

	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.texture = ASSET_PATH + std::string("bullet.png");
	br.outline_opacity = 0.0f;
	br.gradient = false;
	graphics::drawRect(bx, by, 0.3f, 0.6f, br);

}