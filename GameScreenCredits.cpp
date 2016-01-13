#include "GameScreenCredits.hpp"

GameScreenCredits::GameScreenCredits() {

    start = false;
    maxTimeActive = 3;
}

void GameScreenCredits::run(WindowManager& window, unsigned int& status) {

    if (!start) {
        start = true;
        timeActive.restart();
    }

    window.clear();
    window.drawText("SF-SpaceG (WIP)", "unique", 64, MIDCENTER, 650, 150);
    window.drawText("<A SFML GameScreen by LuDiArOs>", "unique", 32, MIDCENTER, 650, 225);
    window.drawText("Here goes the credits", "mono", 32, MIDCENTER, 650, 300);
    window.drawText("Press ENTER to return", "mono", 32, MIDCENTER, 650, 400);
    window.drawText("Press ESC to exit", "mono", 32, MIDCENTER, 650, 450);
    window.drawText("It returns to GameScreenLoad automatically after 3 seconds", "mono", 32, MIDCENTER, 650, 500);
    window.display();

    if (timeActive.getElapsedTime().asSeconds() > maxTimeActive) {

        start = false;
        status = LOAD;
    }
}

void GameScreenCredits::getEvents(WindowManager& window, unsigned int& status) {

    if (window.eventMap["VK_RETURN"]) {
        window.eventMap["VK_RETURN"] = false;

        start = false;
        status = LOAD;
    }

    if (window.eventMap["VK_ESCAPE"]) {
        window.eventMap["VK_ESCAPE"] = false;

        status = EXIT;
    }
}
