#include "platform.h"

#include <stdio.h>
#include <SDL3/SDL.h>

const int WINDOW_WIDTH = 256;
const int WINDOW_HEIGHT = 196;

SDL_Window* win;
SDL_Renderer* renderer;
SDL_Texture* texture;

const SDL_FRect window_rect_f = {0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT};
const SDL_Rect window_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

void *pixels;

void setup_gfx(LunaOS* os_instance) {
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("LunaOS Emulator", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, NULL, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB1555, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

    int pitch;
    SDL_LockTexture(texture, &window_rect, &pixels, &pitch);

    os.vram0 = pixels;
}

void setup_fat() {

}

void setup_platform(LunaOS* os_instance) {
    setup_gfx(os_instance);
    setup_fat();
}

void platform_fire_error(const char* error_message) {
    printf("%s \n", error_message);
    exit(1);
}

void platform_wait_vblank() {
    SDL_UnlockTexture(texture);
    SDL_RenderTexture(renderer, texture, &window_rect_f, &window_rect_f);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                // loopShouldStop = 1;
                break;
        }
    }

    SDL_RenderClear(renderer);
    int pitch;
    SDL_LockTexture(texture, &window_rect, &pixels, &pitch);

    os.vram0 = pixels;
}