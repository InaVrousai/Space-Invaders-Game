//#pragma once
//#include "GameObject.h"
//
//class Enemy : public GameObject {
//    float x, y;     // Enemy's position
//    float speed;    // Movement speed
//    int health;     // Enemy health points
//
//public:
//    Enemy(GameState* gs, const std::string& name, float initX, float initY, float initSpeed, int initHealth)
//        : GameObject(gs, name), x(initX), y(initY), speed(initSpeed), health(initHealth) {}
//
//    void update(float dt) override; // Update enemy state
//    void draw() override;           // Render enemy
//    bool isDead() const { return health <= 0; } // Check if enemy is dead
//    void takeDamage(int damage);    // Reduce health when hit
//};