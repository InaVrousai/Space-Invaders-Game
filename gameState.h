##pragma once
#include <vector>
#include <unordered_map>
#include "defines.h"
#include "player.h"
#include "sgg/graphics.h"
#include "bulletPlayer.h"
#include "gameObject.h"
#include "enemy.h"

class GameState {
public:
	enum game_state_t { STATE_INIT, STATE_LOADING, STATE_RUNNING, STATE_GAME_OVER, STATE_RECORD };

	//Score
	int score = 0;
	int highscore;




protected:
	static GameState* m_instance;

	// PLAYER

	Player* player1 = nullptr;
	Player* player2 = nullptr;

	//PLAYER BULLET
	std::vector<GameObject*> bullets_p;  // Active player bullets
	std::unordered_map<int, float> lastShootTime; // Last shoot time for each player
	std::unordered_map<int, BulletPlayer*> activeBullets; // Tracks active bullets for each player

	float shootCooldown = 0.5f;
	float en_bullet_spawn_timer = 0.0f;
	const float en_bullet_spawn_period = 2.0f;
	//ENEMY
	std::vector<GameObject*> enemies; // List of active enemies
	std::list<GameObject*> enemy_bullets;
	//int state;//MENU, RUNNING, GAME_OVER

	game_state_t m_state = STATE_INIT;

	GameState();

public:

	void init();
	void update(float dt);
	void draw();
	void spawnEnemies();//this methodt is responsible for creating and adding new enemy
	void updateEnemyGrid(float dt);
	void checkCollisions();
	void spawnRandomBullet();
	float getRandomFloat(float min, float max);
	void shootBulletForPlayer(Player* player);
	bool canShoot(int playerId) const;
	bool EnemiesDefeated() const;
	int getScore() const { return score; }
	void setScore(int score) { this->score = score; }

	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static GameState* getInstance();

	~GameState();
};