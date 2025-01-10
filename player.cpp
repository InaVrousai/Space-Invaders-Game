#include "player.h"
#include "gameState.h"
#include "sgg/graphics.h"
#include<iostream>
#include <vector>
#include "defines.h"
#include "bulletPlayer.h"

Player::Player(GameState* gs, const std::string& name, int id)
    : GameObject(gs, name) , playerId(id) , score(0)
    {
    }

// Initialize the player
void Player::init(float x, float y)
{
    m_pos[0] = x;
    m_pos[1] = y;
    
}

void Player::update(float dt)
{
    if (playerId == 1) { // Left player controls (A, D, S)
        if (graphics::getKeyState(graphics::SCANCODE_A)) {
            m_pos[0] -= speed * dt / 5.0;
        }
        if (graphics::getKeyState(graphics::SCANCODE_D)) {
            m_pos[0] += speed * dt /5.0f;
        }
        if (graphics::getKeyState(graphics::SCANCODE_S) /* && m_state->canShoot(playerId)*/) {
            m_state->shootBulletForPlayer(this);
        }


    }
    else if (playerId == 2) { // Right player controls (Left, Right, Space)
        if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {
            m_pos[0] -= speed * dt/5.0f;
        }
        if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
            m_pos[0] += speed * dt/5.0f;
        }
        if (graphics::getKeyState(graphics::SCANCODE_SPACE)/* && m_state->canShoot(playerId)*/) {
            m_state->shootBulletForPlayer(this);
        }
    }

    // Clamp the player's position to stay within the canvas
    if (m_pos[0] < 0) m_pos[0] = 0;
    if (m_pos[0] > CANVAS_WIDTH) m_pos[0] = CANVAS_WIDTH;
}

int Player::getId()
{
    return playerId;
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

    //float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);

    graphics::Brush br;
    
    br.texture = std::string(ASSET_PATH) + "milleniumfalcon.png";
    br.outline_opacity = 0.0f;
    
    graphics::drawRect(m_pos[0], m_pos[1], p_size, p_size, br);

    br.texture = "";
    SETCOLOR(br.fill_color, 1.0f, 0.5f, 0.0f);
    br.fill_opacity = 0.5f;
   
  
    graphics::drawDisk(m_pos[0], m_pos[1] + 20, p_size / 3.0f, br);

    // Optionally draw the player's score or other stats
    graphics::drawText(20.0f, 10.0f, 0.5f, "Score: " + std::to_string(score), br);
}

void Player::shoot(std::vector<GameObject*>& bullets)
{
    // Creating a new bullet starting from the player's position
    float bulletX = getPosX();
    float bulletY = getPosY() - 2.0f; // Position slightly above the player

    BulletPlayer* bullet = new BulletPlayer(m_state, "Bullet", bulletX, bulletY);
    bullets.push_back(bullet);
}


