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

int keys[12] = { 0 };

void p_setup_gfx(LunaOS* os_instance) {
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("LunaOS Emulator", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, NULL, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB1555, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

    int pitch;
    SDL_LockTexture(texture, &window_rect, &pixels, &pitch);

    os.vram = pixels;
}

void p_setup_fat() {

}

void p_setup(LunaOS* os_instance) {
    p_setup_gfx(os_instance);
    p_setup_fat();
}

void p_fire_error(const char* error_message) {
    printf("%s \n", error_message);
    exit(1);
}

void p_wait_vblank() {
    SDL_UnlockTexture(texture);
    SDL_RenderTexture(renderer, texture, &window_rect_f, &window_rect_f);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                break;

            case SDL_EVENT_KEY_DOWN: {
                int key = event.key.keysym.scancode;

                if(key == SDL_SCANCODE_A)       keys[0] = 1;
                if(key == SDL_SCANCODE_B)       keys[1] = 1;
                if(key == SDL_SCANCODE_SELECT)  keys[2] = 1;
                if(key == SDL_SCANCODE_KP_ENTER)keys[3] = 1;
                if(key == SDL_SCANCODE_RIGHT)   keys[4] = 1;
                if(key == SDL_SCANCODE_LEFT)    keys[5] = 1;
                if(key == SDL_SCANCODE_UP)      keys[6] = 1;
                if(key == SDL_SCANCODE_DOWN)    keys[7] = 1;
                if(key == SDL_SCANCODE_R)       keys[8] = 1;
                if(key == SDL_SCANCODE_L)       keys[9] = 1;
                if(key == SDL_SCANCODE_X)       keys[10] = 1;
                if(key == SDL_SCANCODE_Y)       keys[11] = 1;

                break;
            }
            case SDL_EVENT_KEY_UP: {
                int key = event.key.keysym.scancode;

                if(key == SDL_SCANCODE_A)       keys[0] = 0;
                if(key == SDL_SCANCODE_B)       keys[1] = 0;
                if(key == SDL_SCANCODE_SELECT)  keys[2] = 0;
                if(key == SDL_SCANCODE_KP_ENTER)keys[3] = 0;
                if(key == SDL_SCANCODE_RIGHT)   keys[4] = 0;
                if(key == SDL_SCANCODE_LEFT)    keys[5] = 0;
                if(key == SDL_SCANCODE_UP)      keys[6] = 0;
                if(key == SDL_SCANCODE_DOWN)    keys[7] = 0;
                if(key == SDL_SCANCODE_R)       keys[8] = 0;
                if(key == SDL_SCANCODE_L)       keys[9] = 0;
                if(key == SDL_SCANCODE_X)       keys[10] = 0;
                if(key == SDL_SCANCODE_Y)       keys[11] = 0;

                break;
            }
        }
    }

    SDL_RenderClear(renderer);
    int pitch;
    SDL_LockTexture(texture, &window_rect, &pixels, &pitch);

    os.vram = pixels;
}

int p_get_key(long long keyCode) {
    return keys[keyCode];
}

void p_memcpy(void* src, void* dst, unsigned long size) {
    memcpy(dst, src, size);
}

Platform p_get_platform() {
    return DESKTOP;
}