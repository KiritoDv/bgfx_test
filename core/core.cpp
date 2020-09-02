#include "core.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <iostream>

using namespace std;

void Core::init(std::function<void()> init, std::function<void()> update) {
    SDL_Window* window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        cout << "Error init video" << "\n";
    } else {
        window = SDL_CreateWindow(
            "Dungeon Dodge",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640, 480,
            SDL_WINDOW_SHOWN
        );
    }

    if (window == NULL) {
        cout << "Window Null" << "\n";
    }

    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        cout << "Error getting window info" << "\n";
        return;
    }

    bgfx::PlatformData pd;
    pd.ndt = wmi.info.x11.display;
    pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
    bgfx::setPlatformData(pd);

    bgfx::renderFrame();
    bgfx::init();
    init();

    bgfx::reset(640, 480, BGFX_RESET_VSYNC);
    bgfx::setDebug(BGFX_DEBUG_TEXT);
    bgfx::setViewRect(0, 0, 0, uint16_t(640), uint16_t(480));

    bgfx::setViewClear(
        0,
        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
        0x443355FF, 1.0f, 0
    );

    bgfx::touch(0);

    bool quit = false;
    SDL_Event ev;
    while (!quit) {
        bgfx::frame();

        update();

        while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT) quit = true;
        }
    }

    bgfx::shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
}
