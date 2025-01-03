//#pragma once
//#include "GameObject.h"
//
//class Player : public GameObject {
//    float x, y;   // Player's position
//    float speed; 
//    int score;
//    char moveLeftKey, moveRightKey, shootKey;
//
//public:
//    // Constructor
//    Player(GameState* gs, const std::string& name, float initX, float initY, char leftKey, char rightKey, char shootKey, std::vector<GameObject*>* bulletContainer)
//        : GameObject(gs, name), x(initX), y(initY), speed(200.0f), score(0),
//        moveLeftKey(leftKey), moveRightKey(rightKey), shootKey(shootKey) {}
//
//    void init() override;
//    void update(float dt) override;
//    void draw() override;
//    void shoot(std::vector<GameObject*>& bullets);
//    int getScore() const { return score; }
//    void addScore(int points) { score += points; }
//
//
//};