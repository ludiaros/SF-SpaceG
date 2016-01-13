#include "GameScreenConfig.hpp"

GameScreenConfig::GameScreenConfig() {

    cursor = 0;

    menuOptions.push_back("[  Back  ]");
    clickArea.push_back(sf::IntRect(575, 385, 160, 40));
}

void GameScreenConfig::run(WindowManager& window, unsigned int& status) {

    window.clear();

    window.drawText("SF-SpaceG (WIP)", "unique", 64, MIDCENTER, 650, 150);
    window.drawText("<A SFML GameScreen by LuDiArOs>", "unique", 32, MIDCENTER, 650, 225);
    window.drawText("CONFIGURATION MENU", "mono", 32, MIDCENTER, 650, 300);

    for (std::size_t i=0; i<menuOptions.size(); i++) {
        window.drawText(menuOptions[i], "mono", 24, MIDCENTER, 650, 400 + (i * 50));
    }

    sf::RectangleShape r;
    r.setSize(sf::Vector2f(clickArea[cursor].width, clickArea[cursor].height));
    r.setPosition(clickArea[cursor].left, clickArea[cursor].top);
    r.setFillColor(sf::Color(128, 255, 128, 128));

    window.draw(r);

    window.display();
}

void GameScreenConfig::getEvents(WindowManager& window, unsigned int& status) {

    mousePos = sf::Mouse::getPosition(window);

    for (std::size_t i=0; i<menuOptions.size(); i++) {

        if (clickArea[i].contains(mousePos.x, mousePos.y)) {

            cursor = i;

            if (window.eventMap["VK_LBUTTON"]) {
                window.eventMap["VK_LBUTTON"] = false;

                window.eventMap["VK_RETURN"] = true;
            }
        }
    }

    if (window.eventMap["VK_DOWN"]) {
        window.eventMap["VK_DOWN"] = false;

        cursor = (cursor < menuOptions.size() - 1 ? cursor + 1 : 0);
    }

    if (window.eventMap["VK_UP"]) {
        window.eventMap["VK_UP"] = false;

        cursor = (cursor > 0 ? cursor - 1 : menuOptions.size() - 1);
    }

    if (window.eventMap["VK_ESCAPE"]) {
        window.eventMap["VK_ESCAPE"] = false;

        status = LOAD;
    }

    if (window.eventMap["VK_RETURN"]) {
        window.eventMap["VK_RETURN"] = false;

        switch (cursor) {

            case 0:
                status = LOAD;
            break;
        }
    }
}
