#include "WindowManager.hpp"

WindowManager::WindowManager():
    rotationRef(false),
    showInfo(true),
    showFPS(true),
    showLimits(false),
    fullscr(false),
    zoom(1),
    zoomMin(0.75),
    zoomMax(50),
    title("SF.SpaceG"),
    limits(sf::LinesStrip, 5)
{

    limits[0].position = sf::Vector2f(0, MAP_H);
    limits[0].color = sf::Color(0, 255, 0, 255);
    limits[1].position = sf::Vector2f(0, 0);
    limits[1].color = sf::Color(0, 255, 0, 255);
    limits[2].position = sf::Vector2f(MAP_W, 0);
    limits[2].color = sf::Color(0, 255, 0, 255);
    limits[3].position = sf::Vector2f(MAP_W, MAP_H);
    limits[3].color = sf::Color(0, 255, 0, 255);
    limits[4].position = sf::Vector2f(0, MAP_H);
    limits[4].color = sf::Color(0, 255, 0, 255);

    video.bitsPerPixel = video.getDesktopMode().bitsPerPixel;
    video.width = SCR_W;
    video.height = SCR_H;

    style = sf::Style::Default;

    view.reset(sf::FloatRect(0, 0, video.width, video.height));

    setKeyRepeatEnabled(false);
    setMouseCursorVisible(false);

    create(video, title, style);

    setFramerateLimit(FPS);
}

void WindowManager::drawCompass() {

    sf::Sprite compass;
    compass.setTexture(*ResourceManager::getTexture("compass"));
    compass.setOrigin(compass.getLocalBounds().width/2, compass.getLocalBounds().height/2);
    compass.setPosition(SCR_W-64, SCR_H-64);
    float x = gameInfo.playerPosX - gameInfo.nextCheckpointX;
    float y = gameInfo.playerPosY - gameInfo.nextCheckpointY;
    float theta = std::acos(y / (sqrt(x*x + y*y))) * 180 / PI;
    compass.setRotation(theta);
    draw(compass);
}

void WindowManager::setDefaultView() {

    setView(getDefaultView());
}

void WindowManager::restartClock() {

    frameTime = clockFPS.restart().asMilliseconds();
}

void WindowManager::toggleFullScreen() {

    if (fullscr) {

        video.width = video.getDesktopMode().width;
        video.height = video.getDesktopMode().height;
        style = sf::Style::Fullscreen;
    }
    else {

        video.width = SCR_W;
        video.height = SCR_H;
        style = sf::Style::Default;
    }

    setMouseCursorVisible(false);
    setKeyRepeatEnabled(false);

    create(video, title, style);

    setFramerateLimit(FPS);

    fullscr = !fullscr;
}

void WindowManager::resetZoom() {

    view.zoom(1 / zoom);
    zoom = 1;
}

void WindowManager::resetView() {

    setView(view);
}

void WindowManager::setZoom(float z) {

    if (zoom >= zoomMin && zoom <= zoomMax) {
        zoom *= z;
        view.zoom(z);
    }

    if (zoom <= zoomMin) {
        z = zoomMin / zoom;
        zoom = zoomMin;
        view.zoom(z);
    }

    if (zoom >= zoomMax) {
        z = zoomMax / zoom;
        zoom = zoomMax;
        view.zoom(z);
    }
}

void WindowManager::setCenter(sf::Vector2f center) {

    px = center.x;
    py = center.y;

    view.setCenter(center);
}

void WindowManager::drawLimits() {

    if (showLimits) {
        draw(limits);
    }
}

void WindowManager::drawFPS() {

    if (showFPS) {

        convert.str("");
        convert.clear();
        if (frameTime > 0) {
            convert << static_cast<int>(1000 / frameTime);
        }
        else {
             convert << 0;
        }
        fps = convert.str();

        drawText("FPS: " + fps, "mono", 16, TOPLEFT, 10, 10);
    }
}

void WindowManager::drawInfo(int align, int x, int y) {

    if (showInfo) {

        convert.str("");
        convert.clear();
        convert << "Checkpoints - " << gameInfo.worldCheckpoints << std::endl;
        convert << "Asteroids   - " << gameInfo.worldAsteroids << std::endl;
        convert << "AMMO        - " << gameInfo.gunShoots << std::endl;
        convert << std::endl;
        convert << "Speed       - " << gameInfo.playerSpeed << std::endl;
        convert << "Damage      - " << gameInfo.playerDamage << std::endl;
        convert << "Shield      - " << gameInfo.playerShields << std::endl;
        convert << "Time        - ";
        convert << static_cast<int>(gameInfo.playerTime/60) << "'";
        convert << ":";
        convert << static_cast<int>(gameInfo.playerTime) % 60 << "''";
        info = convert.str();

        drawText(info, "mono", 16, align, x, y);
    }
}

void WindowManager::drawText(sf::String txt, sf::String fontId, int fontsize, int align, int x, int y) {

    font = *ResourceManager::getFont(fontId);
    text = sf::Text(txt, font, fontsize);
    text.setStyle(sf::Text::Bold);

    switch (align) {
        case TOPLEFT:
            text.setOrigin(0, 0);
        break;
        case TOPCENTER:
            text.setOrigin(text.getLocalBounds().width/2, 0);
        break;
        case TOPRIGHT:
            text.setOrigin(text.getLocalBounds().width, 0);
        break;
        case MIDLEFT:
            text.setOrigin(0, text.getLocalBounds().height/2);
        break;
        case MIDCENTER:
            text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
        break;
        case MIDRIGHT:
            text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height/2);
        break;
        case BOTTOMLEFT:
            text.setOrigin(0, text.getLocalBounds().height);
        break;
        case BOTTOMCENTER:
            text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height);
        break;
        case BOTTOMRIGHT:
            text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height);
        break;
    }

    text.setPosition(x, y);
    draw(text);
}

void WindowManager::getWindowEvents(unsigned int& status) {

    sf::Event event;

    while (pollEvent(event)) {

        if (event.type == sf::Event::Closed) {

            close();
        }

        if (event.type == sf::Event::MouseWheelMoved) {

            if (status == PLAY) {

                setZoom(1 - (float) event.mouseWheel.delta / 5);
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {

            switch (event.mouseButton.button) {

                case sf::Mouse::Left:
                    eventMap["VK_LBUTTON"] = true;
                break;
            }
        }

        if (event.type == sf::Event::KeyReleased) {

            switch (event.key.code) {

                case sf::Keyboard::Add:
                    setZoom(0.95);
                break;

                case sf::Keyboard::Subtract:
                    setZoom(1.05);
                break;

                case sf::Keyboard::F4:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
                        close();
                    }
                break;

                case sf::Keyboard::F11:
                    toggleFullScreen();
                break;

                case sf::Keyboard::Numpad0:
                    resetZoom();
                break;

                case sf::Keyboard::Escape:
                    eventMap["VK_ESCAPE"] = true;
                break;

                case sf::Keyboard::I:
                    showInfo = !showInfo;
                break;

                case sf::Keyboard::F:
                    showFPS = !showFPS;
                break;

                case sf::Keyboard::R:
                    if (status == PLAY) {
                        rotationRef = !rotationRef;
                    }
                break;

                case sf::Keyboard::Y:
                    eventMap["VK_Y"] = true;
                break;

                case sf::Keyboard::N:
                    eventMap["VK_N"] = true;
                break;

                case sf::Keyboard::Up:
                    eventMap["VK_UP"] = true;
                break;

                case sf::Keyboard::Down:
                    eventMap["VK_DOWN"] = true;
                break;

                case sf::Keyboard::Left:
                    eventMap["VK_LEFT"] = true;
                break;

                case sf::Keyboard::Right:
                    eventMap["VK_RIGHT"] = true;
                break;

                case sf::Keyboard::Return:
                    eventMap["VK_RETURN"] = true;
                break;
            }
        }
    }
}
