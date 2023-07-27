#include"Main_Game.hpp"
#include"character&ball.hpp"

#include<iostream>
#include<SDL.h>
#include<Windows.h>
#include<SDL_image.h>

/*
func will init the window
input: title, width, height, flag, double pointer to the window, and double pointer to the renderer
output: true if success else false
*/
bool BasketBall_Main::init_window(const char* title, int width, int height, Uint32 flag,  SDL_Window** window, SDL_Renderer** renderer)
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
		return false;
	}

	//init window
	*window = SDL_CreateWindow("BasketBallGame",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 
		width,
		height, 
		flag);


	//checks if window has been created
	if (window == NULL) {
		fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
		return false;
	}


	return true;
}

/*
will init the renderer
input: window and pointer to renderer
output: true if success else false
*/
bool BasketBall_Main::init_renderer(SDL_Window* window, SDL_Renderer** renderer)
{
	*renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!*renderer)
	{
		std::cout << "couldnt load renderer." << std::endl;
		return false;
		SDL_Quit();
	}
	return true;
}

/*
main func
checks if every other func went all right
input: double pointers to window, renderer, background img
output: true if success else false
*/
int BasketBall_Main::Main_Game(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** background_texture, SDL_Surface** image_surface_background)
{
	SDL_Surface* character_surface = nullptr;
	SDL_Texture* character_texture = nullptr;

	if (!init_window("BasketBall", width, height, NULL, window, renderer))
	{
		return false;
	}
	std::cout << "window loaded successfully!\n";

	if (!init_renderer(*window, renderer))
	{
		return false;
	}
	std::cout << "renderer loaded successfully!\n";



	character_surface = IMG_Load("pl.png");
	if (!character_surface)
	{
		std::cerr << "couldnt load character surface." << std::endl;
		return false;
	}
	std::cout << "character surface loaded successfully!" << std::endl;


	character_texture = SDL_CreateTextureFromSurface(*renderer, character_surface);
	if (!character_texture)
	{
		std::cerr << "Failed to create player texture: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(character_surface);
		return false;
	}
	std::cout << "Character texture loaded successfully!" << std::endl;

	SDL_FreeSurface(character_surface);

	character* character_ = new character{ "pl.png", character_texture, "labron nigga", "team 1", 100, 100, 3 , 5 , false };

	bool quit = false;
	SDL_Event event;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_A])
		{
			character_->x -= character_->movespeed_normal;
		}
		if (currentKeyStates[SDL_SCANCODE_D])
		{
			character_->x += character_->movespeed_normal;
		}
		if (currentKeyStates[SDL_SCANCODE_W])
		{
			character_->y -= character_->movespeed_normal;
		}
		if (currentKeyStates[SDL_SCANCODE_S])
		{
			character_->y += character_->movespeed_normal;
		}

		if (currentKeyStates[SDL_SCANCODE_LSHIFT] && currentKeyStates[SDL_SCANCODE_A])
		{
			character_->x -= character_->movespeed_run;
		}
		if (currentKeyStates[SDL_SCANCODE_LSHIFT] && currentKeyStates[SDL_SCANCODE_D])
		{
			character_->x += character_->movespeed_run;
		}
		if (currentKeyStates[SDL_SCANCODE_LSHIFT] && currentKeyStates[SDL_SCANCODE_W])
		{
			character_->y -= character_->movespeed_run;
		}
		if (currentKeyStates[SDL_SCANCODE_LSHIFT] && currentKeyStates[SDL_SCANCODE_S])
		{
			character_->y += character_->movespeed_run;
		}


		SDL_RenderClear(*renderer);

		*image_surface_background = SDL_LoadBMP("map.bmp");
		*background_texture = SDL_CreateTextureFromSurface(*renderer, *image_surface_background);

		SDL_RenderCopy(*renderer, *background_texture, NULL, NULL);

		SDL_Rect playerRect = { character_->x, character_->y, 50, 50 };
		SDL_RenderCopy(*renderer, character_texture, NULL, &playerRect);

		SDL_RenderCopy(*renderer, character_texture, NULL, &playerRect);

		
		SDL_RenderPresent(*renderer);
	}

	return true;
}


bool BasketBall_Main::init_surface(SDL_Window** window, SDL_Surface** window_surface, SDL_Surface** image_surface)
{
	*window_surface = SDL_GetWindowSurface(*window);

	*image_surface = IMG_Load(map_file_path);

	if (!image_surface)
	{
		std::cout << "Couldnt load map" << std::endl;
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return false;
	}

	SDL_BlitSurface(*image_surface, NULL, *window_surface, NULL);

	SDL_UpdateWindowSurface(*window);

	return true;
}


/*
	if (!init_surface(window, window_surface, image_surface))
	{
		return false;
	}
	std::cout << "background loaded successfully!\n";



	character_loader = IMG_Load("pl.png");
	if (!character_loader)
	{
		std::cout << "failed to load character" << std::endl;
	}










	int BasketBall_Main::Main_Game(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** background_texture, SDL_Surface** image_surface_background)
{

	if (!init_window("BasketBall", width, height, NULL, window, renderer))
	{
		return false;
	}
	std::cout << "window loaded successfully!\n";

	if (!init_renderer(*window, renderer))
	{
		return false;
	}
	std::cout << "renderer loaded successfully!\n";


	bool quit = false;
	SDL_Event event;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_RenderClear(*renderer);

		*image_surface_background = SDL_LoadBMP("map.bmp");
		*background_texture = SDL_CreateTextureFromSurface(*renderer, *image_surface_background);

		SDL_RenderCopy(*renderer, *background_texture, NULL, NULL);

		SDL_Surface* image = IMG_Load("pl.png");

		SDL_RenderPresent(*renderer);
	}
	return true;
}
*/