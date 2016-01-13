#include "GameScreenReset.hpp"

GameScreenReset::GameScreenReset() {
    start = false;
    maxTimeActive = 2;
}

void GameScreenReset::run(WindowManager& window, unsigned int& status) {

    if (!start) {
        start = true;
        timeActive.restart();
    }

    window.clear();
    window.drawText("Reset", "mono", 32, MIDCENTER, SCR_W/2, SCR_H/2);
    window.display();

    if (timeActive.getElapsedTime().asSeconds() > maxTimeActive) {

        start = false;
        status = PLAY;
    }
}

void GameScreenReset::getEvents(WindowManager& window, unsigned int& status) {


    if (window.eventMap["VK_RETURN"]) {
        window.eventMap["VK_RETURN"] = false;
        start = false;
        status = PLAY;
    }
}
