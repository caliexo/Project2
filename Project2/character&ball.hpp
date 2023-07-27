#pragma once
#include<iostream>
#include<SDL.h>

#include"character&ball.hpp"

struct character
{
	std::string img_skin;
	SDL_Texture* image_skin_loader;

	std::string identifir;
	std::string team;

	//helpful for movement
	int x, y;
	int movespeed_normal, movespeed_run;

	bool has_the_ball;
};

struct ball
{
	std::string img_skin;
	SDL_Surface* image_skin_loader;

	int x, y, z;
	int xVol, yVol, zVol;
};