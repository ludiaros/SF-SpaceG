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
    py(0)
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
    create(video, "SF.SpaceG", style);
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

    create(video, "Ivernia Legend", style);

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
