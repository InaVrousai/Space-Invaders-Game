#pragma once
#include "gameState.h"
#include "defines.h"
#include "sgg/graphics.h"
#include "player.h"
#include <iostream>



GameState* GameState::m_instance = nullptr;

GameState::GameState() {}




void GameState::init()
{
	player1 = new Player(this, "Player1", 1);
	player1->init(5.0f, CANVAS_HEIGHT - 2.0f);

	player2 = new Player(this, "Player2", 2);
	player2->init(CANVAS_WIDTH - 5.0f, CANVAS_HEIGHT - 2.0f);

	
	spawnEnemies();
	m_state = STATE_RUNNING;
}

void GameState::update(float dt)
{
	
	if (m_state == STATE_INIT)
	{
		return;
	}
	if (m_state == STATE_RUNNING)
	{
		if (player1) {player1->update(dt);}
		if (player2) {player2->update(dt);}
		// Update bullets
		for (auto it = bullets_p.begin(); it != bullets_p.end();) {
			(*it)->update(dt);

			// Check if the bullet is no longer active
			if (!(*it)->isActive()) {
				// Remove from active bullets map if it matches
				for (auto& pair : activeBullets) {
					if (pair.second == *it) {
						activeBullets[pair.first] = nullptr;  // Clear active bullet for the player
						break;
					}
				}

				delete* it; // Clean up memory
				it = bullets_p.erase(it); // Remove bullet from list
			}
			else {
				++it;
			}
		}
		//UPDATE ENEMY
		 // Move the enemy grid
		updateEnemyGrid(dt);

		for (auto it = bullets_p.begin(); it != bullets_p.end();) {
			(*it)->update(dt);
			if (!(*it)->isActive()) {
				delete* it;
				it = bullets_p.erase(it);
			}
			else {
				++it;
			}
		}

		// Check for collisions
		checkCollisions();

		// Example: Check for game-over conditions
		if (player1->getRemainingLife() <= 0 && player2->getRemainingLife() <= 0) {
			m_state = STATE_GAME_OVER; // Transition to game over
		}
	}else if (m_state == STATE_GAME_OVER) {
		// Handle game-over state
		// Possibly wait for user input to restart or quit
	}

	

}

void GameState::draw()
{
	

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	if (m_state == STATE_INIT)
	{
		graphics::setFont("free-sans.ttf");
		graphics::drawText(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, 0.5f, "Loading assets...",br);
		m_state = STATE_LOADING;
		return;
	}
	
	if (m_state == STATE_LOADING) {
		graphics::setFont("free-sans.ttf");
		graphics::drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 0.5f, "Game is starting...", br);
		init(); // Call init to set up the game
		return;
	}
	

	if (m_state == STATE_RUNNING) {
		// Draw background
		br.outline_opacity = 0.0f;
		br.texture = ASSET_PATH + std::string("backround.png");
		SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f);
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

		// Draw players
		if (player1) player1->draw();
		if (player2) player2->draw();

		//Draw enemy
		for (const auto& enemy : enemies) {
			enemy->draw();
		}

		// Draw player bullets
		for (const auto& bullet : bullets_p) {
			bullet->draw();
			 
		}

	}
	else if (m_state == STATE_GAME_OVER) {
		// Draw game-over screen
		graphics::setFont("free-sans.ttf");
		graphics::drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 0.5f, "Game Over!", br);
		graphics::drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 1.0f, 0.3f, "Press R to Restart", br);

		// Wait for restart input
		if (graphics::getKeyState(graphics::SCANCODE_R)) {
			m_state = STATE_INIT; // Restart the game
		}

	}
}

void GameState::updateEnemyGrid(float dt) {
	static float gridDirection = 1.0f; // 1: moving right, -1: moving left
	static float gridSpeed = 0.5f;
	const float BORDER_BUFFER = 1.0f; // Adjust buffer size as needed


	float gridEdgeLeft = CANVAS_WIDTH, gridEdgeRight = 0;

	for (const auto& enemy : enemies) {
		Enemy* e = dynamic_cast<Enemy*>(enemy);
		if (e) {
			float ex = e->getPosX();
			if (ex < gridEdgeLeft) gridEdgeLeft = ex;
			if (ex > gridEdgeRight) gridEdgeRight = ex;
		}
	}
	

	// Reverse direction at boundaries
	if ((gridEdgeRight >= CANVAS_WIDTH - BORDER_BUFFER && gridDirection > 0) || (gridEdgeLeft <= 0 && gridDirection < 0)) {
		gridDirection *= -1; // Reverse horizontal direction
	}
	if (gridEdgeLeft <= BORDER_BUFFER && gridDirection < 0) {
		gridDirection *= -1; // Reverse direction
	}

	// Move all enemies in the current direction
	for (auto& enemy : enemies) {
		Enemy* e = dynamic_cast<Enemy*>(enemy);
		if (e) e->setPosX(e->getPosX() + gridDirection * gridSpeed * dt);
	}

}



void GameState::spawnEnemies()
{
	float spacing_x = (CANVAS_WIDTH - 2.0f) / COLUMNS;  // Horizontal spacing
	float spacing_y = ENEMY_HEIGHT + 1.0;  // Vertical spacing (adjust as needed)

	float start_x = spacing_x / 2.0f;  // Center the first enemy horizontally
	float start_y = CANVAS_HEIGHT / 15.0f;  // Move the grid higher (adjust the divisor as needed)

	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLUMNS; ++col) {
			float x = start_x + col * spacing_x; // Calculate x position
			float y = start_y + row * spacing_y; // Calculate y position

			Enemy* enemy = new Enemy(this, "Enemy_" + std::to_string(row * COLUMNS + col));
			enemy->init(x, y);
			enemies.push_back(enemy);

			std::cout << "Spawned enemy at (" << x << ", " << y << ")\n";
		}
	}
}

void GameState::shootBulletForPlayer(Player* player)
{
	if (!player) return;

	// Check if there is an active bullet for the player
	if (activeBullets[player->getId()] != nullptr && activeBullets[player->getId()]->isActive()) {
		return; // Skip creating a new bullet
	}

	BulletPlayer* bullet = new BulletPlayer(this, "Bullet", player->getPosX(), player->getPosY() - 0.5f);
	bullets_p.push_back(bullet);
	activeBullets[player->getId()] = bullet; 
	
}

bool GameState::canShoot(int playerId) const
{
	auto it = lastShootTime.find(playerId);
	if (it == lastShootTime.end()) return true; // Player has not shot before
	return (graphics::getGlobalTime() - it->second) > shootCooldown; // Allow shooting after cooldown
}

GameState* GameState::getInstance()
{
	if (!m_instance)
		m_instance = new GameState();
	return m_instance;
}

void GameState::checkCollisions() {
	for (auto bulletIt = bullets_p.begin(); bulletIt != bullets_p.end();) {
		BulletPlayer* bullet = dynamic_cast<BulletPlayer*>(*bulletIt);
		if (!bullet || !bullet->isActive()) {
			// Remove bullet from activeBullets map if it matches
			for (auto& pair : activeBullets) {
				if (pair.second == bullet) {
					activeBullets[pair.first] = nullptr;
					break;
				}
			}

			// Delete and remove the bullet
			delete bullet;
			bulletIt = bullets_p.erase(bulletIt);
			continue;
		}

		bool bulletRemoved = false;

		for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
			Enemy* enemy = dynamic_cast<Enemy*>(*enemyIt);
			if (!enemy || !enemy->isActive()) {
				++enemyIt;
				continue;
			}

			// Check for collision using disks
			Disk bulletDisk = bullet->getCollisionDisk();
			Disk enemyDisk = enemy->getCollisionDisk();
			float distance = sqrt(pow(bulletDisk.cx - enemyDisk.cx, 2) + pow(bulletDisk.cy - enemyDisk.cy, 2));

			if (distance < (bulletDisk.radius + enemyDisk.radius)) {
				// Collision detected
				enemy->takeDamage(100); // Assume full damage
				bullet->setActive(false); // Deactivate bullet
				bulletRemoved = true;

				// Remove enemy if destroyed
				if (enemy->isDead()) {
					delete enemy;
					enemyIt = enemies.erase(enemyIt);
				}
				else {
					++enemyIt;
				}

				break; // Exit loop for this bullet
			}
			else {
				++enemyIt;
			}
		}

		if (bulletRemoved) {
			// Remove bullet from activeBullets map
			for (auto& pair : activeBullets) {
				if (pair.second == bullet) {
					activeBullets[pair.first] = nullptr;
					break;
				}
			}

			// Delete and remove the bullet
			delete bullet;
			bulletIt = bullets_p.erase(bulletIt);
		}
		else {
			++bulletIt;
		}
	}
}




GameState::~GameState()
{
	delete player1;
	delete player2;

	for (auto bullet : bullets_p) delete bullet;
	//for (auto enemy : enemies) delete enemy;
}

