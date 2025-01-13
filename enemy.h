#pragma once
#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>

class Enemy : public GameObject {
    float x = 0.0f, y = 0.0f;     // Enemy's position
    float speed = 0.1f;    // Movement speed
    float en_size = 2.0f;
    int health = 10;     // Enemy health points
    int dirX = 1;  //Move direction
    int dirY = 1;
    graphics::Brush brush_en;
    float shoot_timer = 0.0f;       // Timer for controlling shooting intervals
    const float shoot_idle = 2.0f; // Time in seconds between shots
    const float max_speed = 1.0f;
    const float slowdown_rate = 0.01f;
public:
    //Enemy(GameState* gs, const std::string& name, float initX, float initY, float initSpeed, int initHealth)
      //  : GameObject(gs, name), x(initX), y(initY), speed(initSpeed), health(initHealth) {}

    Enemy(GameState* gs, const std::string& name);
    void init(float x, float y) override;
    void update(float dt) override; // Update enemy state
    void draw() override;           // Render enemy
    bool isDead() const { return health <= 0; } // Check if enemy is dead
    void takeDamage(int damage);    // Reduce health when hit
    float getPosX() { return this->x; }
    float getPosY() { return this->y; }
    void setPosX(float x) { this->x = x; }
    void setPosY(float y) { this->y = y; }
    void shoot();

};