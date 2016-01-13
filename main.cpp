#include <SFML/Window.hpp>

#include "globals.hpp"

#include "ResourceManager.hpp"
#include "WindowManager.hpp"
#include "GameScreenManager.hpp"

WindowManager     window;
GameScreenManager gstate;

int main() {

    //LOAD RESOURCES -------------------------------------------------------------------------------
    ResourceManager::addFont("mono", "res/font/DejaVuSansMono.ttf");
    ResourceManager::addFont("unique", "res/font/Unique.ttf");

    ResourceManager::addTexture("uarr", "res/gfx/uarr.png");
    ResourceManager::addTexture("ammo", "res/gfx/ammo.png");
    ResourceManager::addTexture("ship", "res/gfx/ship.png");
    ResourceManager::addTexture("rock0", "res/gfx/rock (0).png");
    ResourceManager::addTexture("rock1", "res/gfx/rock (1).png");
    ResourceManager::addTexture("rock2", "res/gfx/rock (2).png");
    ResourceManager::addTexture("rock3", "res/gfx/rock (3).png");
    ResourceManager::addTexture("rock4", "res/gfx/rock (4).png");
    ResourceManager::addTexture("rock5", "res/gfx/rock (5).png");
    ResourceManager::addTexture("rock6", "res/gfx/rock (6).png");
    ResourceManager::addTexture("rock7", "res/gfx/rock (7).png");
    ResourceManager::addTexture("rock8", "res/gfx/rock (8).png");
    ResourceManager::addTexture("rock9", "res/gfx/rock (9).png");
    //----------------------------------------------------------------------------------------------

    //INITIALIZE OPTIONS AND GAME DATA -------------------------------------------------------------
    window.gameInfo.maxAsteroids   = 2500;
    window.gameInfo.maxCheckpoints = 5;
    window.gameInfo.maxShoots      = 100;
    window.gameInfo.maxStars       = 500;
    window.gameInfo.maxShips       = 1;
    //----------------------------------------------------------------------------------------------

    //INITIALIZE GAME STATES -----------------------------------------------------------------------
    gstate.addState(LOAD,    new GameScreenLoad());
    gstate.addState(CONFIG,  new GameScreenConfig());
    gstate.addState(PLAY,    new GameScreenPlay());
    gstate.addState(PAUSED,  new GameScreenPause());
    gstate.addState(RESET,   new GameScreenReset());
    gstate.addState(OVER,    new GameScreenOver());
    gstate.addState(WIN,     new GameScreenWin());
    gstate.addState(CREDITS, new GameScreenCredits());
    gstate.addState(EXIT,    new GameScreenExit());
    gstate.status = LOAD;
    //----------------------------------------------------------------------------------------------

    //MAIN LOOP-------------------------------------------------------------------------------------
    while (window.isOpen()) {

        window.getWindowEvents(gstate.status);

        gstate.getState()->getEvents(window, gstate.status);
        gstate.getState()->run(window, gstate.status);
    }
    //----------------------------------------------------------------------------------------------

    return EXIT_SUCCESS;
}
