#include <creek/creek.hpp>

#include <SDL2/SDL.h>

struct SDL {
    // SDL(int flags) {
    //     SDL_Init(flags);
    // }

    // ~SDL() {
    //     SDL_Quit();
    // }

    static int init(int flags) { return SDL_Init(flags); }
    static void quit() { SDL_Quit(); }
};

int func_SDL_SetError(const char* m) {
    return SDL_SetError(m);
}

int func_SDL_INIT_EVERYTHING() {
    return SDL_INIT_EVERYTHING;
}

CREEK_FUNC(SDL_Init,        &SDL_Init);
CREEK_FUNC(SDL_Quit,        &SDL_Quit);
CREEK_FUNC(SDL_GetError,    &SDL_GetError);
CREEK_FUNC(SDL_SetError,    &func_SDL_SetError);
CREEK_FUNC(SDL_WasInit,     &SDL_WasInit);
CREEK_FUNC(FLAG_INIT_EVERYTHING, &func_SDL_INIT_EVERYTHING);

CREEK_CLASS(SDL, SDL) {
    CREEK_CLASS_METHOD(init,    &SDL::init),
    CREEK_CLASS_METHOD(quit,    &SDL::quit),
};
