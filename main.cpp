#include "sgg/graphics.h"
#include "sgg/scancodes.h"
#include "defines.h"
#include "game.h"
#include <iostream>


void updateGame(float dt) 
{
    Game::getInstance()->update(dt);

}
void drawGame()
{
    Game::getInstance()->draw();
}

int main(int argc, char** argv)
{
    graphics::createWindow(800, 600, "Space Invaders 2P");

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::setUpdateFunction(updateGame);
    graphics::setDrawFunction(drawGame);

    graphics::startMessageLoop();

    Game::releaseInstance();

    return 0;

}
