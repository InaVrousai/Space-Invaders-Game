#include "player.h"
#include "gameState.h"
#include "sgg/graphics.h"
#include<iostream>
#include <vector>
#include "defines.h"

Player::Player(GameState* gs, const std::string& name)
    : GameObject(gs, name)
    {
    }

// Initialize the player
void Player::init(float x, float y) {
    setPosX(x);
    setPosY(y);
}

void Player::update(float dt)
{
}

Disk Player::getCollisionDisk() const
{
    Disk disk;
    disk.cx = m_pos[0];
    disk.cy = m_pos[1] - 5;
    disk.radius = p_size / 2.0f;
    return disk;
}


//Draw the player

void Player::draw() {
    if (!isActive()) return;

    graphics::Brush brush;
    brush.outline_opacity = 0.0f;
    brush.texture = ""; // No texture
    SETCOLOR(brush.fill_color, 1.0f, 0.0f, 0,0f);
    graphics::drawRect(m_pos[0], m_pos[2], 50, 50, brush);

    // Optionally draw the player's score or other stats
    graphics::drawText(10, 10, 20, "Score: " + std::to_string(score), brush);
}

void Player::shoot(std::vector<GameObject*>& bullets)
{
}
