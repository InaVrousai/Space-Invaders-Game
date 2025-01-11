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

	//spawnEnemies();
	m_state = STATE_RUNNING;

	//init enemies
	Enemy* enemy = new Enemy(this, "Enemy");
	enemy->init(5.0f, 5.0f);
	enemies.push_back(enemy);
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

		// Example: Check for game-over conditions
		if (player1->getRemainingLife() <= 0 && player2->getRemainingLife() <= 0) {
			m_state = STATE_GAME_OVER; // Transition to game over
		}

		//Updates for enemy sheet
		for (auto enemy : enemies)
		{
			if (enemy) { enemy->update(dt); }
		}
		for (auto it = enemy_bullets.begin(); it != enemy_bullets.end();) {
			(*it)->update(dt);
			if (!(*it)->isActive()) {
				// Remove from active bullets map if it matches
				for (auto& pair : activeBullets) {
					if (pair.second == *it) {
						activeBullets[pair.first] = nullptr;  // Clear active bullet for the player
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

	}else if (m_state == STATE_GAME_OVER) {
		// Handle game-over state
		// Possibly wait for user input to restart or quit
	}

	

	//update enemy bullets
	updateBullets(dt);

}

void GameState::draw()
{
	

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);


	//graphics::setFont("free-sans.ttf");
	graphics::drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 0.5f, "Loading assets...", br);
		
		


	BulletPlayer* bullet = new BulletPlayer(this, "Bullet", player->getPosX(), player->getPosY() - 0.5f);
	bullets_p.push_back(bullet);
	activeBullets[player->getId()] = bullet; 

	//draw enema
	for (auto enemy : enemies) {
		if (enemy->isActive()) {
			enemy->draw();
		}
	}
	//draw enemy bullets
	for (auto bullet : enemy_bullets) {
		if (bullet->isActive())
			bullet->draw();
	}
}

}

GameState* GameState::getInstance()
{
	if (!m_instance)
		m_instance = new GameState();
	return m_instance;
}

void GameState::addBullet(bulletEnemy* bullet)
{
	enemy_bullets.push_back(bullet);
}


GameState::~GameState()
{
	delete player1;
	delete player2;

	for (auto bullet : bullets_p) delete bullet;
	//delete enemies and their bullets
	for (auto enemy : enemies) { delete enemy; }
	enemies.clear();
	for (auto bullet : enemy_bullets) {
		delete bullet;
	}
	enemy_bullets.clear();
}

