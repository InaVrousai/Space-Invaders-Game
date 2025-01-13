#include "gameobject.h"
#include <sgg/graphics.h>

class Enemy : public GameObject {
    float x = 0.0f, y = 0.0f;     // Enemy's position
    float speed = 0.1f;    // Movement speed
    float en_size = 2.0f;
    int health = 10;     // Enemy health points
    int dir = 1;  //Move direction

    graphics::Brush brush_en;

    const float max_speed = 1.0f;
    const float slowdown_rate = 0.01f;
public:
    Enemy(GameState* gs, const std::string& name);
    void init(float x, float y) override;
    void update(float dt) override;
    void draw() override;
    bool isDead() const { return health <= 0; }
    void takeDamage(int damage);

    float getPosX() const { return this->x; }
    float getPosY() const { return this->y; }
    void setPosX(float x) { this->x = x; }
    void setPosY(float y) { this->y = y; }
};