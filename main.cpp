#include "sgg/graphics.h"
#include "sgg/scancodes.h"
#include "defines.h"
#include "gameState.h"
#include <iostream>


void updateGame(float dt) 
{
    if (dt > 0.033f) { // Cap dt to avoid large jumps (equivalent to ~30 FPS)
        dt = 0.033f;
    }
    GameState::getInstance()->update(dt);

}
void drawGame()
{
    GameState::getInstance()->draw();
}

int main(int argc, char** argv)
{
    graphics::createWindow(800, 600, "Space Invaders 2P");

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    GameState::getInstance()->init();
    graphics::setUpdateFunction(updateGame);
    graphics::setDrawFunction(drawGame);

    graphics::startMessageLoop();

    GameState::releaseInstance();

    return 0;

}
