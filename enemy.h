#pragma once
#include "GameObject.h"
#include <sgg/graphics.h>

class Enemy : public GameObject {
    float x, y;     // Enemy's position
    float speed = 0.1f;    // Movement speed
    int health = 10;     // Enemy health points
    int dir = 1;  //Move direction
    graphics::Brush brush_en;
    float shoot_timer = 0.0f;       // Timer for controlling shooting intervals
    const float shoot_interval = 2.0f; // Time in seconds between shots
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