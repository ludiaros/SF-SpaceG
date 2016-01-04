#include "WindowManager.hpp"

WindowManager::WindowManager():
    rot_fixed(false),
    no_info(false),
    no_fps(false),
    fullscr(false),
    zoom(1),
    zoom_min(0.25),
    zoom_max(50),
    px(0),
    py(0),
    title("SF.SpaceG"),
    limits(LinesStrip, 5)
{
    video.bitsPerPixel = video.getDesktopMode().bitsPerPixel;
    video.width = SCR_W;
    video.height = SCR_H;

    style = Style::Default;

    view.reset(FloatRect(0, 0, video.width, video.height));

    setZoom(zoom);
    setVerticalSyncEnabled(true);
    setMouseCursorVisible(false);
    setKeyRepeatEnabled(false);
    create(video, title, style);

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

    create(video, title, style);

    setVerticalSyncEnabled(true);
    setMouseCursorVisible(false);
    setKeyRepeatEnabled(false);

    fullscr = !fullscr;
}

void WindowManager::resetZoom() {

    view.zoom(1 / zoom);
    zoom = 1;
}

void WindowManager::setZoom(float z) {

    if (z * zoom > 0.25 && z * zoom < 4) {
        zoom = z * zoom;
        view.zoom(z);
    }
}

void WindowManager::setCenter(Vector2f center) {

    px = center.x;
    py = center.y;

    view.setCenter(center);
}

void WindowManager::drawLimits() {
    draw(limits);
}

void WindowManager::drawFPS() {

    if (no_fps) {
        text = Text("FPS: " + fps, font, 16);
        text.setStyle(Text::Bold);
        text.setPosition(5, 5);
        draw(text);
    }
}

void WindowManager::drawInfo() {

    if (no_info) {
        text = Text(info, font, 16);
        text.setStyle(Text::Bold);
        text.setPosition(5, video.height-200);
        draw(text);
    }
}

void WindowManager::drawText(String txt, int fontsize, int x, int y) {

    text = Text(txt, font, fontsize);
    text.setStyle(Text::Bold);
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(x, y);
    draw(text);
}
