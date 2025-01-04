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
