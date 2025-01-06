#pragma once
#include "GameObject.h"
#include <sgg/graphics.h>

class Enemy : public GameObject,public Collision {
    float x, y;     // Enemy's position
    float speed = 0.1f;    // Movement speed
    int health;     // Enemy health points
    graphics::Brush brush_en;

public:
    //Enemy(GameState* gs, const std::string& name, float initX, float initY, float initSpeed, int initHealth)
      //  : GameObject(gs, name), x(initX), y(initY), speed(initSpeed), health(initHealth) {}
	
    Enemy(GameState* gs, const std::string& name);
    void init() override
    void update(float dt) override; // Update enemy state
    void draw() override;           // Render enemy
    bool isDead() const { return health <= 0; } // Check if enemy is dead
    void takeDamage(int damage);    // Reduce health when hit
    float getPosX() { return this->x; }
    float getPosY() { return this->y; }
    void setPosX(float x) { this->x = x; }
    void setPosY(float y) { this->y = y; }
};