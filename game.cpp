#pragma once
#include "game.h"
#include "defines.h"
#include "sgg/graphics.h"


Game::Game() {
	// Initialization logic
}




void Game::update(float dt)
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

void Game::draw()
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

Game* Game::getInstance()
{
	if (!m_instance)
		m_instance = new Game();
	return m_instance;
}

Game::~Game()
{
}
Game* Game::m_instance = nullptr;
