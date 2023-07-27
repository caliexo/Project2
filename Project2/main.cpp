#ifndef _WIN32   
int exit() { return 1 };
#endif


#include <SDL.h>
#include <iostream>
#include <cmath>

#include"Main_Game.hpp"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) 
{

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* background_texture = nullptr;
    SDL_Surface* image_surface_background = nullptr;

    BasketBall_Main main_game;

    
    if (!main_game.Main_Game(&window, &renderer, &background_texture, &image_surface_background))
    {
        std::cout << "error gg" << std::endl;
        return 1;
    }

    SDL_FreeSurface(image_surface_background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
