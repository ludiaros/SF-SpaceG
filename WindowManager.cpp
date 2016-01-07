#include "WindowManager.hpp"

WindowManager::WindowManager():
    rot_fixed(false),
    show_info(true),
    show_fps(true),
    show_limits(false),
    fullscr(false),
    zoom(1),
    zoom_min(0.75),
    zoom_max(50),
    title("SF.SpaceG"),
    limits(LinesStrip, 5)
{

    font.loadFromFile("res/font/DejaVuSansMono.ttf");

    limits[0].position = Vector2f(0, MAP_H);
    limits[0].color = Color(0, 255, 0, 255);
    limits[1].position = Vector2f(0, 0);
    limits[1].color = Color(0, 255, 0, 255);
    limits[2].position = Vector2f(MAP_W, 0);
    limits[2].color = Color(0, 255, 0, 255);
    limits[3].position = Vector2f(MAP_W, MAP_H);
    limits[3].color = Color(0, 255, 0, 255);
    limits[4].position = Vector2f(0, MAP_H);
    limits[4].color = Color(0, 255, 0, 255);

    video.bitsPerPixel = video.getDesktopMode().bitsPerPixel;
    video.width = SCR_W;
    video.height = SCR_H;

    style = Style::Default;

    view.reset(FloatRect(0, 0, video.width, video.height));

    setKeyRepeatEnabled(false);
    setMouseCursorVisible(false);

    create(video, title, style);

    setFramerateLimit(60);
}

void WindowManager::setDefaultView() {

    setView(getDefaultView());
}

void WindowManager::toggleFullScreen() {

    if (fullscr) {

        video.width = video.getDesktopMode().width;
        video.height = video.getDesktopMode().height;
        style = Style::Fullscreen;
    }
    else {

        video.width = SCR_W;
        video.height = SCR_H;
        style = Style::Default;
    }

    setMouseCursorVisible(false);
    setKeyRepeatEnabled(false);

    create(video, title, style);

    setFramerateLimit(30);

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

    if (zoom >= zoom_min && zoom <= zoom_max) {
        zoom *= z;
        view.zoom(z);
    }

    if (zoom <= zoom_min) {
        z = zoom_min / zoom;
        zoom = zoom_min;
        view.zoom(z);
    }

    if (zoom >= zoom_max) {
        z = zoom_max / zoom;
        zoom = zoom_max;
        view.zoom(z);
    }
}

void WindowManager::setCenter(Vector2f center) {

    px = center.x;
    py = center.y;

    view.setCenter(center);
}

void WindowManager::drawLimits() {

    if (show_limits) {
        draw(limits);
    }
}

void WindowManager::drawFPS() {

    if (show_fps) {
        drawText("FPS: " + fps, TOPLEFT, 16, 10, 10);
    }
}

void WindowManager::drawInfo() {

    if (show_info) {
        drawText(info, BOTLEFT, 16, 10, video.height-10);
    }
}

void WindowManager::drawText(String txt, int align, int fontsize, int x, int y) {

    text = Text(txt, font, fontsize);
    text.setStyle(Text::Bold);

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
        case BOTLEFT:
            text.setOrigin(0, text.getLocalBounds().height);
        break;
        case BOTCENTER:
            text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height);
        break;
        case BOTRIGHT:
            text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height);
        break;
    }

    text.setPosition(x, y);
    draw(text);
}
