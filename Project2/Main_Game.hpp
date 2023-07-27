#pragma once
#include<iostream>
#include<Windows.h>
#include<string>
#include<vector>
#include<cmath>
#include<SDL.h>

#include"character&ball.hpp"

class BasketBall_Main
{
	const int width = 1546;
	const int height = 980;

	const char* map_file_path = "map.jpg";//background

	bool init_window(const char* title, int width, int height, Uint32 flag, SDL_Window** window, SDL_Renderer** renderer);

	bool init_renderer(SDL_Window* window, SDL_Renderer** renderer);
	
	bool init_surface(SDL_Window** window, SDL_Surface** window_surface, SDL_Surface** image_surface);

public:

	int Main_Game(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** background_texture, SDL_Surface** image_surface_background);
};