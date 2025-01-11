#pragma once
#include "bulletEnemy.h"
#include <vector>
#include <unordered_map>
#include "defines.h"
#include "player.h"
#include "sgg/graphics.h"
#include "bulletPlayer.h"
#include "gameObject.h"

class GameState {
public:
	enum game_state_t { STATE_INIT, STATE_LOADING,STATE_RUNNING, STATE_GAME_OVER, STATE_RECORD };
	
	//Score
	int score = 0;
	int highscore;




protected:
	static GameState* m_instance;

	//Player* player1;
	//Player* player2;
	//std::vector<GameObject*> bullets;  // Dynamic list of all active bullets in the game.
	//std::vector<GameObject*> enemies;  // Dynamic list of all active enemies in the game.
	//int state;//MENU, RUNNING, GAME_OVER

	game_state_t m_state = STATE_INIT;

	GameState();

public:
	
	void init();
	void update(float dt);
	void draw();
	//void spawnEnemies();//this methodt is responsible for creating and adding new enemy
	//void checkCollisions();

	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static GameState* getInstance();

	void addBullet(bulletEnemy* bullet);

	~GameState();
};

