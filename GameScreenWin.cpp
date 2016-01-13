#include "GameScreenWin.hpp"

GameScreenWin::GameScreenWin() {
}

void GameScreenWin::run(WindowManager& window, unsigned int& status) {

    window.clear();
    window.drawText("    YOU WIN    \nPlay again? Y/n", "mono", 32, MIDCENTER, SCR_W/2, SCR_H/2);
    window.drawInfo(TOPCENTER, SCR_W/2, SCR_H/2+100);
    window.display();
}

void GameScreenWin::getEvents(WindowManager& window, unsigned int& status) {

    if (window.eventMap["VK_N"]) {
        window.eventMap["VK_N"] = false;

        status = LOAD;
    }

    if (window.eventMap["VK_Y"]) {
        window.eventMap["VK_Y"] = false;

        status = PLAY;
    }

    if (window.eventMap["VK_ESCAPE"]) {
        window.eventMap["VK_ESCAPE"] = false;

        status = LOAD;
    }

    if (window.eventMap["VK_RETURN"]) {
        window.eventMap["VK_RETURN"] = false;

        status = PLAY;
    }
}
