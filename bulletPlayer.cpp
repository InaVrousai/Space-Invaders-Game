#include "bulletPlayer.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <iostream>

BulletPlayer::BulletPlayer(GameState* gs, const std::string& name, float x, float y)
	:GameObject(gs, name), bx(x),by(y)
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
	br.texture = "";
	br.outline_opacity = 0.0f;
	br.gradient = false;
	graphics::drawRect(bx, by, 0.3f, 0.6f, br);

}

void BulletPlayer:: update(float dt)
{
	by -= speed * dt; // Move the bullet upwards based on normalized dt
	if (isOutOfBounds()) {
		setActive(false);
	}

}

Disk BulletPlayer::getCollisionDisk() const {
	Disk disk;
	disk.cx = bx;
	disk.cy = by;
	disk.radius = b_size / 2.0f;
	return disk;
}

bool BulletPlayer::isOutOfBounds() const {
	return by < -1.0f; // The bullet goes out of bounds if it crosses the top of the screen
}

BulletPlayer::~BulletPlayer() {
	// Cleanup if necessary
}