#pragma once
#include "gameState.h"
#include "defines.h"
#include "sgg/graphics.h"
#include "player.h"
#include <iostream>
#include "bulletEnemy.h"

GameState* GameState::m_instance = nullptr;

GameState::GameState() {}

void GameState::init()
{
	player1 = new Player(this, "Player1", 1);
	player1->init(5.0f, CANVAS_HEIGHT - 2.0f);

	player2 = new Player(this, "Player2", 2);
	player2->init(CANVAS_WIDTH - 5.0f, CANVAS_HEIGHT - 2.0f);

	enemies.clear();
	spawnEnemies();
	m_state = STATE_INIT;
}

void GameState::update(float dt)
{

	if (m_state == STATE_INIT)
	{
		if (graphics::getKeyState(graphics::SCANCODE_R)) { m_state = STATE_LOADING; }
		if (graphics::getKeyState(graphics::SCANCODE_ESCAPE)) { exit(0); }
		return;
	}
	if (m_state == STATE_LOADING) { init(); m_state = STATE_RUNNING; }
	if (m_state == STATE_RUNNING)
	{
		if (player1) { player1->update(dt); }
		if (player2) { player2->update(dt); }
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

		for (auto it = enemy_bullets.begin(); it != enemy_bullets.end();) {
			(*it)->update(dt);
			if (!(*it)->isActive()) {
				delete* it;
				it = enemy_bullets.erase(it);
			}
			else {
				++it;
			}
		}

		//enemy bullets
		en_bullet_spawn_timer += dt / 1000.0f;
		if (en_bullet_spawn_timer >= en_bullet_spawn_period) {
			en_bullet_spawn_timer = 0.0f;
			spawnRandomBullet();
		}
		// Check for collisions
		checkCollisions();
		// delete a player once he dies
		if (player1->getRemainingLife() <= 0) { player1->setActive(false); }
		if (player2->getRemainingLife() <= 0) { player2->setActive(false); }
		// Example: Check for game-over conditions
		if (player1->getRemainingLife() <= 0 && player2->getRemainingLife() <= 0) {
			m_state = STATE_GAME_OVER; // Transition to game over
		}
		//game over when all the enemies are defeated
		if (EnemiesDefeated()) { m_state = STATE_GAME_OVER; }

	}
	else if (m_state == STATE_GAME_OVER) {
		// Handle game-over state
		if (graphics::getKeyState(graphics::SCANCODE_R)) { m_state = STATE_INIT; }
		if (graphics::getKeyState(graphics::SCANCODE_ESCAPE)) { exit(0); }
		return;
	}
}

void GameState::draw()
{

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	if (m_state == STATE_INIT)
	{
		graphics::Brush init_br;
		graphics::setFont(ASSET_PATH + std::string("OpenSans-Bold.ttf"));
		graphics::drawText(CANVAS_WIDTH / 2.0f - 4.0f, CANVAS_HEIGHT / 2.0f - 1.0f, 1.0f, "Press R to Start", init_br);

		SETCOLOR(init_br.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::drawText(CANVAS_WIDTH / 2.0f - 4.0f, CANVAS_HEIGHT / 2.0f + 1.0f, 1.0f, "Press ESC to Quit", init_br);
		return;
	}

	if (m_state == STATE_LOADING) {
		graphics::Brush loading_br;
		SETCOLOR(loading_br.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::setFont(ASSET_PATH + std::string("OpenSans-Bold.ttf"));
		graphics::drawText(CANVAS_WIDTH / 2 - 2.0f, CANVAS_HEIGHT / 2, 1.0f, "Loading...", loading_br);
		return;
	}


	if (m_state == STATE_RUNNING) {
		// Draw background
		br.outline_opacity = 0.0f;
		br.texture = ASSET_PATH + std::string("background.png");
		SETCOLOR(br.fill_color, 0.0f, 0.0f, 1.0f);
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

		// Draw players
		if (player1->isActive()) player1->draw();
		if (player2->isActive()) player2->draw();

		//Draw enemy
		for (const auto& enemy : enemies) {
			enemy->draw();
		}

		// Draw player bullets
		for (const auto& bullet : bullets_p) {
			if (bullet->isActive())
				bullet->draw();
		}

		for (auto bullet : enemy_bullets) {
			if (bullet->isActive())
				bullet->draw();
		}
		//Draw player hearts
		graphics::Brush heart_br;
		heart_br.outline_opacity = 0.0f;
		heart_br.texture = ASSET_PATH + std::string("heart.png");
		heart_br.fill_color[0] = 1.0f;
		heart_br.fill_color[1] = 0.0f;
		heart_br.fill_color[2] = 0.0f;
		for (int i = 0; i < player1->getRemainingLife(); ++i) {
			graphics::drawRect(i + 1.5f, CANVAS_HEIGHT - 2.0f, 0.5f, 0.5f, heart_br);
		}
		for (int i = 0; i < player2->getRemainingLife(); ++i) {
			graphics::drawRect(CANVAS_WIDTH - i - 1.5f, CANVAS_HEIGHT - 2.0f, 0.5f, 0.5f, heart_br);
		}
	}
	else if (m_state == STATE_GAME_OVER) {
		// Draw game-over screen
		graphics::Brush game_over_br;
		graphics::setFont(ASSET_PATH + std::string("OpenSans-Bold.ttf"));
		graphics::drawText(CANVAS_WIDTH / 2.0f - 7.0f, CANVAS_HEIGHT / 2.0f, 2.5f, "Game Over!", game_over_br);
		graphics::drawText(CANVAS_WIDTH / 2.0f - 4.0f, CANVAS_HEIGHT / 2.0f + 2.0f, 1.0f, "Press R to Restart", game_over_br);
		//score text
		graphics::drawText(CANVAS_WIDTH / 2.0f - 4.0f, CANVAS_HEIGHT / 2.0f - 4.0f, 1.0f, "Final Score: " + std::to_string(getScore()), game_over_br);
		//Quit text
		SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::drawText(CANVAS_WIDTH / 2.0f - 4.0f, CANVAS_HEIGHT / 2.0f + 4.0f, 1.0f, "Press ESC to Quit", game_over_br);
		return;
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
		if (e) e->setPosX(e->getPosX() + gridDirection * gridSpeed * dt * 0.005f);
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
	if (!player || !(player->isActive())) return;

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

bool GameState::EnemiesDefeated() const
{
	for (auto& enemy : enemies) {
		if (enemy->isActive()) { return false; }
	}
	return true;
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
				if (player1) {
					player1->setScore(player1->getScore() + 100);
					setScore(player1->getScore() + 100);
				}
				if (player2) {
					player2->setScore(player2->getScore() + 100);
					setScore(player2->getScore() + 100);
				}

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
	for (auto& en_bullet : enemy_bullets)
	{
		bulletEnemy* enemy_bullet = static_cast<bulletEnemy*>(en_bullet);
		float x1 = enemy_bullet->getPosX() - player1->getPosX();
		float y1 = enemy_bullet->getPosY() - player1->getPosY();

		float dist1 = sqrt(pow(x1, 2) + pow(y1, 2)) - player1->getCollisionDisk().radius -
			enemy_bullet->getCollisionDisk().radius;
		if (dist1 < 0) {
			if (dist1 < 0) {
				if (player1->getRemainingLife() >= enemy_bullet->getDamage())
				{
					player1->setRemainingLife(player1->getRemainingLife()
						- enemy_bullet->getDamage());
				}
				else
				{
					player1->setRemainingLife(0);
				}
				en_bullet->setActive(false);
			}
		}

		float x2 = enemy_bullet->getPosX() - player2->getPosX();
		float y2 = enemy_bullet->getPosY() - player2->getPosY();

		float dist2 = sqrt(pow(x2, 2) + pow(y2, 2)) -
			player1->getCollisionDisk().radius
			- enemy_bullet->getCollisionDisk().radius;
		if (dist2 < 0) {
			if (player2->getRemainingLife() >= enemy_bullet->getDamage())
			{
				player2->setRemainingLife(player2->getRemainingLife()
					- enemy_bullet->getDamage());
			}
			else {
				player2->setRemainingLife(0);
			}
			en_bullet->setActive(false);
		}
	}

}

void GameState::spawnRandomBullet()
{
	float randomX = getRandomFloat(0.0f, CANVAS_WIDTH);
	float randomY = getRandomFloat(0.0f, CANVAS_HEIGHT / 2.0f);
	bulletEnemy* en_bullet = new bulletEnemy(this, "EnemyBullet");
	en_bullet->init(randomX, randomY);
	enemy_bullets.push_back(en_bullet);
}

float GameState::getRandomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (max - min));
}

GameState::~GameState()
{
	delete player1;
	delete player2;

	for (auto bullet : bullets_p) delete bullet;
	for (auto enemy : enemies) delete enemy;
	for (auto bullet : enemy_bullets) {
		delete bullet;
	}
}