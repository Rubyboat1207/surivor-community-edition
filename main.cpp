// mingw32-make.exe
// gdb survivor.exe

#include <SDL.h>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <list>
#include <optional>
#include <stdexcept>
#include <math.h>
int WIDTH = 640;
int HEIGHT = 480;
bool init();
bool loadMedia();
void close();
void registerImages();
void frame();

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
const Uint8 *keys = SDL_GetKeyboardState(NULL);
double deltaTime = 0;


#include "./utils.cpp"
#include "./image_handling.cpp"
#include "./game_objects.cpp"
#include "./transform.cpp"
#include "./renderer.cpp"
#include "./player_controller.cpp"
#include "./health.cpp"
#include "./character_face_direction.cpp"
#include "./debug_renderer.cpp"

RubyImage *player = new RubyImage(0, 0, 1, "assets/character_small.bmp");
RubyImage *star = new RubyImage(0, 0, 1, "assets/star.bmp");
RubyImage *spritesheet = new RubyImage(0, 0, 1, "assets/charset.bmp");

GameObject *playerObject = new GameObject();
GameObject *referenceObject = new GameObject();
GameObject *spriteSheetTest = new GameObject();

Uint64 NOW = SDL_GetPerformanceCounter();
Uint64 LAST = 0;


int main(int argc, char *args[])
{
	//printf("Hello, world!\n");
	if (!init())
	{
		//printf("Failed to initalize!\n");
		return 1;
	}
	if (!loadMedia())
	{
		printf("Failed to load Assets\n");
		printf("Likely failed to resource aquisition, either the file is being modified/in use or it does not exist. More likely the latter than the former.\n");
		return 2;
	}
	try {
		Renderer* renderer = new Renderer();
		Renderer* starRenderer = new Renderer();
		MultispriteRenderer* spritesheetRenderTest = new MultispriteRenderer();
		// TextRenderer* text = new TextRenderer(new RubySpriteSheet(charset, 32, 32));
		// text->backingText = "abc";


		renderer->sharedSprite = player;
		starRenderer->sharedSprite = star;
		spritesheetRenderTest->sharedSprite = new RubySpriteSheet(spritesheet, 32, 32);

		playerObject->AddComponent(new Transform());
		playerObject->AddComponent(renderer);
		playerObject->AddComponent(new PlayerController());


		referenceObject->AddComponent(new Transform());
		referenceObject->AddComponent(starRenderer);

		spriteSheetTest->AddComponent(new Transform());
		spriteSheetTest->AddComponent(spritesheetRenderTest);

		// spriteSheetTest->setActive(false);

		// textTest->AddComponent(new Transform());
		// textTest->AddComponent(text);
	}catch(...) {
		printf("error has occured");
		return 0;
	}
	




	//printf("here_preevent\n");

	// SDL_BlitSurface(player->surface, NULL, screenSurface, NULL);

	SDL_Event e;
	bool quit = false;
	//printf("here_prewhile\n");
	while (quit == false)
	{
		//printf("here_pretry\n");
		try {
			//printf("here_dt\n");
			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();
			//printf("dt: %f\n", (double)SDL_GetPerformanceFrequency());
			deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
			while (SDL_PollEvent(&e))
			{
				printf("Event Located: %i\n", e.type);
				if (e.type == SDL_QUIT) {
					// printf("quitting due to request\n");
					quit = true;
				}
			}
			//printf("here_windowsize\n");
			SDL_GetWindowSize(window, &WIDTH, &HEIGHT);

			SDL_Surface *surface=SDL_GetWindowSurface(window);
			Uint32 skyblue=SDL_MapRGB(surface->format, 255,255,255);
			SDL_FillRect(surface, NULL, skyblue);
			// printf("here_preframe\n");
			frame();
			// printf("here_postframe\n");
			SDL_UpdateWindowSurface(window);
			//printf("here_windowupdated\n");
		}catch(...) {
			//printf("error has occured, quitting\n");
			quit = true;
		}
		
	}
	//printf("quitted out of while loop\n");
	close();

	return 0;
}

bool init()
{
	//printf("began initialization\n");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//printf("Sdl failed to initalize L + Ratio");
		return false;
	}

	window = SDL_CreateWindow(
		//"Sevor: Survival Evolded II Mod Dedicated Server World Game With Bennett Foddy 4 Dead 2 The Skywalker Saga GOTY 2023 Edition Community Edition | Nicholas Edition",
		"Survivor Community Edition",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		//printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);

	//printf("passed initialization\n");
	return true;
}

void frame() {
    // auto keyboard = SDL_GetKeyboardState(NULL);
	// player->blit(screenSurface);
	for(auto go : activeGameObjects) {
		__try {
			go->Update();
		}
		__catch(...) {
			printf("error has occured in update");
			// //printf(err.what());
		}
	}
	printDebug();
	
	// playerObject->Update();
	// referenceObject->Update();
	// textTest->Update();
	// //printf("%f", deltaTime);
	// vec.print();
	// cameraPosition += vec;
} 

bool loadMedia()
{
	//printf("began loading media\n");
	registerImages();
	for (int i = 0; i < IMAGE_REGISTRY.size(); i++)
	{
		if (!IMAGE_REGISTRY[i]->loadImage())
		{
			printf("Unable to load image %s! SDL Error: %s\n", IMAGE_REGISTRY[i]->path.c_str(), SDL_GetError());
			return false;
		}
	}
	printf("finished image loading\n");
	return true;
}

void registerImages()
{
	player->registerImage();
	star->registerImage();
	spritesheet->registerImage();
}

void close()
{
	for (int i = 0; i < IMAGE_REGISTRY.size(); i++)
	{
		IMAGE_REGISTRY[i]->~RubyImage();
		delete &IMAGE_REGISTRY[i];
	}
	IMAGE_REGISTRY.clear();

	delete playerObject;
	delete referenceObject;

	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}