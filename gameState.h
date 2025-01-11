#pragma once
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

	Player* player1 = nullptr;
	Player* player2 = nullptr;

	std::vector<GameObject*> bullets_p;  // Active player bullets
	std::unordered_map<int, float> lastShootTime; // Last shoot time for each player
	std::unordered_map<int, BulletPlayer*> activeBullets; // Tracks active bullets for each player

	float shootCooldown = 0.5f;



	//std::vector<GameObject*> enemies; // Active enemies

	
	//int state;//MENU, RUNNING, GAME_OVER

	game_state_t m_state = STATE_INIT;

	GameState();

public:
	
	void init();
	void update(float dt);
	void draw();
	void spawnEnemies();//this methodt is responsible for creating and adding new enemy
	void checkCollisions();
	void shootBulletForPlayer(Player* player);
	bool canShoot(int playerId) const;
	

	
	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static GameState* getInstance();

	~GameState();
};