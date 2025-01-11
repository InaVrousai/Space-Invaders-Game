#pragma once
#include "bulletEnemy.h"
#include <vector>
#include "defines.h"
//#include "Player.h"

class GameState {
public:
	//enum game_state_t { STATE_INIT, STATE_LOADING, STATE_IDLE, STATE_MOVING, STATE_ATTACKING };
	


protected:
	static GameState* m_instance;

	//Player* player1;
	//Player* player2;
	//std::vector<GameObject*> bullets;  // Dynamic list of all active bullets in the game.
	//std::vector<GameObject*> enemies;  // Dynamic list of all active enemies in the game.
	std::vector<bulletEnemy*> enemy_bullets;
	//int state;//MENU, RUNNING, GAME_OVER

	//game_state_t m_state = STATE_INIT;

	GameState();

public:
	
	//void init();
	void update(float dt);
	void draw();
	//void spawnEnemies();//this methodt is responsible for creating and adding new enemy
	//void checkCollisions();
	
	//methods for bulletEnemy
	void addBullet(bulletEnemy* bullet);

	void updateBullets(float dt);

	void drawBullets();

	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static GameState* getInstance();

	~GameState();
};

