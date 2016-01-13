#include "GameScreenPause.hpp"

GameScreenPause::GameScreenPause() {
}

void GameScreenPause::run(WindowManager& window, unsigned int& status) {

    //window.clear();
    window.drawText("PAUSED", "mono", 32, MIDCENTER, SCR_W/2, SCR_H/2);
    window.display();
}

void GameScreenPause::getEvents(WindowManager& window, unsigned int& status) {

    if (window.eventMap["VK_ESCAPE"]) {
        window.eventMap["VK_ESCAPE"] = false;
        status = LOAD;
    }

    if (window.eventMap["VK_RETURN"]) {
        window.eventMap["VK_RETURN"] = false;
        status = PLAY;
    }
}
