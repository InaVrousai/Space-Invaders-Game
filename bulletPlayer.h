#pragma once
#include "gameObject.h"

class BulletPlayer : public GameObject, public Collision{

    float bx, by;
    float speed = 3.0f;
    float b_size = 1.0f;

public:
    BulletPlayer(GameState* gs, const std::string& name, float x, float y);

    void update(float dt) override;
    void draw() override;
    void init(float x, float y) override;

    Disk getCollisionDisk() const override;

    bool isOutOfBounds() const; // Check if the bullet leaves the screen

    ~BulletPlayer();
    
};
