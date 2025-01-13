#pragma once
#include "gameState.h"
#include "defines.h"
#include "sgg/graphics.h"
#include "player.h"
#include <iostream>
#include "enemy.h"
#include "bulletEnemy.h"

GameState* GameState::m_instance = nullptr;

GameState::GameState() {}

void GameState::init()
{
	player1 = new Player(this, "Player1", 1);
	player1->init(5.0f, CANVAS_HEIGHT - 2.0f);

	player2 = new Player(this, "Player2", 2);
	player2->init(CANVAS_WIDTH - 5.0f, CANVAS_HEIGHT - 2.0f);

	//spawnEnemies();
	m_state = STATE_RUNNING;

	//enemy init
	spawnEnemies();
}

void GameState::update(float dt)
{

	if (m_state == STATE_INIT)
	{
		return;
	}
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
		for (auto enemy : enemies)
		{
			if (enemy) { enemy->update(dt); }
		}
		for (auto it = enemy_bullets.begin(); it != enemy_bullets.end();) {
			(*it)->update(dt);
			if (!(*it)->isActive()) {
				// Remove from active bullets map if it matches
				for (auto& pair : en_activeBullets) {
					if (pair.second == *it) {
						en_activeBullets[pair.first] = nullptr;  // Clear active bullet for the player
						break;
					}
				}

				delete* it; // Clean up memory
				it = enemy_bullets.erase(it); // Remove bullet from list
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

		checkCollisions();
		if (player1->getRemainingLife() <= 0) { player1->setActive(false); }
		if (player2->getRemainingLife() <= 0) { player2->setActive(false); }

		// Example: Check for game-over conditions
		if (player1->getRemainingLife() <= 0 && player2->getRemainingLife() <= 0) {
			m_state = STATE_GAME_OVER; // Transition to game over
		}
	}
	else if (m_state == STATE_GAME_OVER) {
		// Handle game-over state
		// Possibly wait for user input to restart or quit
	}

	//enemy updates
}

void GameState::draw()
{


	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	if (m_state == STATE_INIT)
	{
		graphics::setFont("free-sans.ttf");
		graphics::drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 0.5f, "Loading assets...", br);
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
		br.texture = ASSET_PATH + std::string("background.png");
		SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

		// Draw players
		if (player1) player1->draw();
		if (player2) player2->draw();

		// Draw player bullets
		for (const auto& bullet : bullets_p) {
			bullet->draw();

		}

		//enemy draw
		for (auto enemy : enemies) {
			if (enemy->isActive()) {
				enemy->draw();
			}
		}
		for (auto bullet : enemy_bullets) {
			if (bullet->isActive())
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

void GameState::spawnEnemies()
{
	for (int i = 0; i <= 3; ++i) {
		for (int j = 0; j <= 7; ++j) {
			Enemy* enemy = new Enemy(this, "Enemy");
			enemy->init(j * 2.0f, i + 5.0f);
			enemies.push_back(enemy);
		}
	}
}

void GameState::checkCollisions()
{
	for (auto& en_bullet : enemy_bullets)
	{
		float x1 = en_bullet->getPosX() - player1->getPosX();
		float y1 = en_bullet->getPosY() - player1->getPosY();

		float dist1 = sqrt(pow(x1, 2) + pow(y1, 2)) - player1->getCollisionDisk().radius -
			en_bullet->getCollisionDisk().radius;
		if (dist1 < 0) {
			if (dist1 < 0) {
				if (player1->getRemainingLife() >= en_bullet->getDamage())
				{
					player1->setRemainingLife(player1->getRemainingLife()
						- en_bullet->getDamage());
				}
				else
				{
					player1->setRemainingLife(0);
				}
				en_bullet->setActive(false);
			}
		}

		float x2 = en_bullet->getPosX() - player2->getPosX();
		float y2 = en_bullet->getPosY() - player2->getPosY();

		float dist2 = sqrt(pow(x2, 2) + pow(y2, 2)) -
			player1->getCollisionDisk().radius
			- en_bullet->getCollisionDisk().radius;
		if (dist2 < 0) {
			if (player2->getRemainingLife() >= en_bullet->getDamage())
			{
				player2->setRemainingLife(player2->getRemainingLife()
					- en_bullet->getDamage());
			}
			else {
				player2->setRemainingLife(0);
			}
			en_bullet->setActive(false);
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

void GameState::spawnRandomBullet()
{
	float randomX = getRandomFloat(0.0f, CANVAS_WIDTH);
	float randomY = getRandomFloat(0.0f, CANVAS_HEIGHT / 2.0f);
	bulletEnemy* en_bullet = new bulletEnemy(this, "EnemyBullet");
	en_bullet->init(randomX, randomY);
	addBullet(en_bullet);
}

void GameState::addBullet(bulletEnemy* bullet)
{
	enemy_bullets.push_back(bullet);
}

float GameState::getRandomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (max - min));
}

GameState::~GameState()
{
	delete player1;
	delete player2;

	for (auto bullet : bullets_p) delete bullet;
	for (auto enemy : enemies) { delete enemy; }
	enemies.clear();
	for (auto bullet : enemy_bullets) {
		delete bullet;
	}
	enemy_bullets.clear();
}