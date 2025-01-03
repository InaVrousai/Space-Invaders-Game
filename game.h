#pragma once
#include <vector>
#include "defines.h"
//#include "Player.h"

class Game {
public:
	//enum game_state_t { STATE_INIT, STATE_LOADING, STATE_IDLE, STATE_MOVING, STATE_ATTACKING };
	


protected:
	static Game* m_instance;

	//Player* player1;
	//Player* player2;
	//std::vector<GameObject*> bullets;  // Dynamic list of all active bullets in the game.
	//std::vector<GameObject*> enemies;  // Dynamic list of all active enemies in the game.
	//int state;//MENU, RUNNING, GAME_OVER

	//game_state_t m_state = STATE_INIT;

	Game();

public:
	
	//void init();
	void update(float dt);
	void draw();
	//void spawnEnemies();//this methodt is responsible for creating and adding new enemy
	//void checkCollisions();

	

	
	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static Game* getInstance();

	~Game();
};