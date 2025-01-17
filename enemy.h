#pragma once
#include "gameObject.h"
#include <sgg/graphics.h>

class Enemy : public GameObject, public Collision {
    float x, y;     // Enemy's position
    float speed = 1.0f;    // Movement speed
    int health;     // Enemy health points
    float shoot_timer = 0.0f;       // Timer for controlling shooting intervals
    const float shoot_interval = 2.0f; // Time in seconds between shots
public:

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
    //void shoot();
    Disk getCollisionDisk() const override;



};