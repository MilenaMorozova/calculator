// calculator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "BUTTON.h"
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
void loadFromFile(int x, int y, SDL_Texture* tex, int w, int h);

//create workspace
void createWorkspace(SDL_Texture* background, button arrayOfNumAndOper[19]);

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

void loadFromFile(int x, int y, SDL_Texture* tex, int w, int h) {
	SDL_Rect renderQuad = { x, y,w, h };
	SDL_RenderCopy(gRenderer, tex, NULL, &renderQuad);
}

void createWorkspace(SDL_Texture* background, button arrayOfNumAndOper[19]) {
	//Load background
	SDL_RenderCopy(gRenderer, background, NULL, NULL);
	//load buttons
	for (int i = 0; i < 19; i++) {
		loadFromFile(arrayOfNumAndOper[i].coordX, arrayOfNumAndOper[i].coordY, arrayOfNumAndOper[i].base, arrayOfNumAndOper[i].button_width, arrayOfNumAndOper[i].button_height);
	}
	SDL_RenderPresent(gRenderer);
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
		//loop flag
		int quit = 0;

		//Event handler
		SDL_Event events;

		//background of calculator
		SDL_Texture* background = loadTexture("base2.png");

//------------------------------------------------------------------BUTTONS----------------------------------------------------------
		button arrayOfNumAndOper[19] = { loadTexture("button zero.png"), indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + 4 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button one.png"), indentSize, indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button two.png"), indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button three.png"), indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button four.png"), indentSize, indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button five.png"), indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button six.png"), indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button seven.png"), indentSize, indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button eight.png"), indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button nine.png"), indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button point2.png"), indentSize, indentFromAbove + 4 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button equally.png"), indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 4 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button summa.png"), indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, 2 * BUTTON_HEIGHT + gapBetweenButtonH,
										loadTexture("button difference.png"), indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button multiplication.png"), indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button backspace.png"), indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove, BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button division.png"), indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove, BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button change signe.png"), indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove, BUTTON_WIDTH, BUTTON_HEIGHT,
										loadTexture("button sqrt.png"), indentSize, indentFromAbove, BUTTON_WIDTH, BUTTON_HEIGHT };

		//create workspace of application
		createWorkspace(background, arrayOfNumAndOper);

	//While application is running
		while (!quit) {
			
			//Handle events on queue
			while (SDL_PollEvent(&events) != 0) {
				//User requests quit
				if (events.type == SDL_QUIT) {
					quit = 1;
				}
			}
		}
		//Quit SDL subsystems
		freeTexture(background);
		//freeTexture(buttonPoint);
		for (int i = 0; i < 19; i++) {
			freeTexture(arrayOfNumAndOper[i].base);			
		}
		close();
	}
	return 0;
}

