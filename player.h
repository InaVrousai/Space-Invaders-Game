#pragma once
#include "GameObject.h"

class Player : public GameObject ,public Collision{
    float m_pos[2];   // Player's position
    float speed = 8.0f; 
    int score;
    int playerId;
    float life = 3.0f;
    float p_size = 2.0f;

public:
    // Constructor
    Player(GameState* gs, const std::string& name, int id);
      
    void init(float x, float y) override;
    void update(float dt) override;
    void draw() override;
    void shoot(std::vector<GameObject*>& bullets);
    float getPosX() { return m_pos[0]; }
    float getPosY() { return m_pos[1]; }
    void setPosX(float x) { m_pos[0] = x; }
    void setPosY(float y) { m_pos[1] = y; }
    int getId();
    Disk getCollisionDisk()const override;

    float getRemainingLife() const { return life; };
    void setRemainingLife(float life) { this->life = life; }

    int getScore() const { return score; }
    void addScore(int points) { score += points; }


};