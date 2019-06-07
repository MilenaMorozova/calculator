// calculator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include<conio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 580;
const int SCREEN_HEIGHT = 700;

//--------GLOBAL VARIABLES------
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Starts up SDL and creates window
int init();

//---------FUNCTION THAT ARE RESPONSIBLE FOR ALL WITH MEDIA-------------
//create texture
SDL_Texture* loadTexture(std::string path);

//draw image from file to screen
void loadFromFile(int x, int y, SDL_Texture* tex, SDL_Renderer* renderer, int w, int h);

//------FREES MEDIA AND SHUTS DOWN SDL------------------
void close();
void freeTexture(SDL_Texture* texture);

int init()
{
	//Initialization flag
	int success = 1;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = 0;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Calculator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = 0;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = 0;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;

				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = 0;
				}
			}
		}
	}
	return success;
}

SDL_Texture* loadTexture(std::string path) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

void loadFromFile(int x, int y, SDL_Texture* tex, SDL_Renderer* renderer, int w, int h) {
	SDL_Rect renderQuad = { x, y,w, h };
	SDL_RenderCopy(gRenderer, tex, NULL, &renderQuad);
}

void freeTexture(SDL_Texture* texture) {
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void close()
{
	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Initialize SDL
	if (!init())
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}	else {

		//background of calculator
		SDL_Texture* background = loadTexture("base.png");
		//Load background
		SDL_RenderCopy(gRenderer, background, NULL, NULL);
		SDL_RenderPresent(gRenderer);
		
		//Quit SDL subsystems
		freeTexture(background);
		//close();
		_getch();
	}
	return 0;
}

