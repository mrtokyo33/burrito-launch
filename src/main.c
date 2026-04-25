#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>

#include "Constants.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL2: %s\n", SDL_GetError());
        return 1;
    }

    printf("SDL2 Initialized successfully!\n");

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "Error initializing SDL2_image: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    printf("SDL2_image (PNG) Initialized successfully!\n");

    if (TTF_Init() != 0) {
        fprintf(stderr, "Error initializing SDL2_ttf: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    printf("SDL2_ttf Initialized successfully!\n");

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        fprintf(stderr, "Error initializing SDL2_mixer: %s\n", Mix_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    printf("SDL2_mixer Initialized successfully!\n");

    SDL_Window *window = SDL_CreateWindow("Burrito Launch", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr, "Error creating the window: %s\n", SDL_GetError());
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

    if (!renderer) { 
        fprintf(stderr, "Error creating the renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;
    Uint32 previous_tick = SDL_GetTicks();
    float deltaTime = 0.0f;

    while (running) {
        Uint32 current_tick = SDL_GetTicks();
        deltaTime = (current_tick - previous_tick) / 1000.0f;
        previous_tick = current_tick;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 56, 142, 24, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        (void)deltaTime;
    }
    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    puts("\nGame Closed with successfull");

    return 0;
}