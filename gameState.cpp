#pragma once
#include "gameState.h"
#include "defines.h"
#include "sgg/graphics.h"


GameState::GameState() {
	// Initialization logic
}




void GameState::update(float dt)
{
	/*if (m_state == state_init)
	{
		return;
	}
	if (m_state == state_loading)
	{
		init();
		m_state = state_idle;
		return;
	}*/

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

	//DRAW BACKROUND
	br.outline_opacity = 0.0f;

	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//draw enemy bullets
	drawBullets();
}

void GameState::addBullet(bulletEnemy* bullet)
{
	m_bullets.push_back(bullet);
}

void GameState::updateBullets(float dt)
{
	for (auto bullet : m_bullets) {
		if (bullet->isActive())
			bullet->update(dt);
	}
	m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(),
		[](Bullet* b) { return !b->isActive(); }),
		m_bullets.end());
}

void GameState::drawBullets()
{
	for (auto bullet : m_bullets) {
		if (bullet->isActive())
			bullet->draw();
	}
}

GameState* GameState::getInstance()
{
	if (!m_instance)
		m_instance = new GameState();
	return m_instance;
}

GameState::~GameState()
{
}
GameState* GameState::m_instance = nullptr;
