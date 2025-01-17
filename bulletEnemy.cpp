#include "bulletEnemy.h"
#include "defines.h"

bulletEnemy::bulletEnemy(GameState* gs, const std::string& name)
	:GameObject(gs, name)
{
}

void bulletEnemy::init(float x, float y)
{
	setPosX(x);
	setPosY(y);

	bulletBrush.outline_opacity = 0.0f;
	bulletBrush.fill_opacity = 1.0f;
	bulletBrush.fill_color[0] = 0.0f;
	bulletBrush.fill_color[1] = 0.0f;
	bulletBrush.fill_color[2] = 0.0f;
	bulletBrush.texture = ASSET_PATH + std::string("bullet.png");
}

void bulletEnemy::draw()
{
	if (!isActive()) return;
	graphics::drawRect(x, y, 1.0f, 1.0f, bulletBrush);
}

void bulletEnemy::update(float dt)
{
	y += speed * (dt / 1000.0f);
	//outofbound deactivation
	if (y < 0 || y > CANVAS_HEIGHT || x < 0 || x > CANVAS_WIDTH) setActive(false);
}

Disk bulletEnemy::getCollisionDisk() const
{
	Disk disk;
	disk.cx = x;
	disk.cy = y - 5;
	disk.radius = b_en_size / 2.0f;
	return disk;
}
