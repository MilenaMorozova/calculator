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
const int maxAfterPoint = 8;
int col0 = 0;
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

void createWorkspace(SDL_Texture* background, SDL_Texture* arrayOfNumbers[10], SDL_Texture* arrayOfOperations[8], SDL_Texture* buttonPoint, int BUTTON_WIDTH, int BUTTON_HEIGHT, int gapBetweenButtonW, int gapBetweenButtonH, int indentSize, int indentFromAbove) {
	
	//Load background
	SDL_RenderCopy(gRenderer, background, NULL, NULL);

	//-----------------FIRST COLUMN---------------------------
	//button "SQRT"
	loadFromFile(indentSize, indentFromAbove, arrayOfOperations[7], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "SEVEN"
	loadFromFile(indentSize, indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, arrayOfNumbers[7], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "FOUR"
	loadFromFile(indentSize, indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[4], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "ONE"
	loadFromFile(indentSize, indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[1], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "POINT"
	loadFromFile(indentSize, indentFromAbove + 4 * (BUTTON_HEIGHT + gapBetweenButtonH), buttonPoint, gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);

	//-----------------SECOND COLUMN---------------------------
	//button "EXPONINTIATION"
	loadFromFile(indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove, arrayOfOperations[6], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "EIGHT"
	loadFromFile(indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, arrayOfNumbers[8], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "FIVE"
	loadFromFile(indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[5], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "TWO"
	loadFromFile(indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[2], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "ZERO"
	loadFromFile(indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + 4 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[0], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);

	//-----------------THIRD COLUMN---------------------------
	//button "DIVISION"
	loadFromFile(indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove, arrayOfOperations[5], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "NINE"
	loadFromFile(indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, arrayOfNumbers[9], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "SIX"
	loadFromFile(indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[6], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "THREE"
	loadFromFile(indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[3], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "EQUALLY"
	loadFromFile(indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 4 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfOperations[4], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);

	//-----------------FOUR COLUMN---------------------------
	//button "BACKSPACE"
	loadFromFile(indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove, arrayOfOperations[3], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "MULTIPLICATION"
	loadFromFile(indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, arrayOfOperations[2], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "DIFFERENCE"
	loadFromFile(indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfOperations[1], gRenderer, BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "SUMMA"
	loadFromFile(indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfOperations[0], gRenderer, BUTTON_WIDTH, 2 * BUTTON_HEIGHT + gapBetweenButtonH);

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
int SymbolsAfterComma(double number)
{
	//counts the symbols after comma
	number += pow(10,-maxAfterPoint-2);
	int col = 0;
	for (int i = 1; i < maxAfterPoint+1; i++)
	{
		number -= (int)(number);
		number *= 10;
		if (((int)number % 10) != 0)
			col = i;
	}
	return col+col0;
}
int SymbolsBeforeComma(double number)
{
	//counts the symbols before comma
	int i = 0;
	int N = (int)(number);
	while (N)
	{
		N /= 10;
		i++;
	}
	return i;
}
void UpdateDisplay(double AllNumber, int comma, SDL_Texture** numbers)
{
	//variable calculation
	int nullposx = (int)(SCREEN_WIDTH * 0.815);
	int nullposy = (int)(SCREEN_HEIGHT * 0.067);
	int numbsizex = (int)(SCREEN_WIDTH * 0.1);
	int numbsizey = (int)(numbsizex * 3 / 2);
	int afcom = SymbolsAfterComma(AllNumber);
	int befcom = SymbolsBeforeComma(AllNumber);
	int colvivod = 0;
	double Allnumb = AllNumber - (int)AllNumber;

	//Clean display
	for (int i = 0; i < 8; i++)
	{
		loadFromFile(nullposx - (i * numbsizex), nullposy, numbers[11], gRenderer, numbsizex, numbsizey);
	}
	//output on display 0
	for (int i = 0; i < col0; i++)
	{
		loadFromFile(nullposx - (colvivod * numbsizex), nullposy, numbers[0], gRenderer, numbsizex, numbsizey);
		colvivod++;
	}
	//output on display symbols after comma
	for (; afcom-col0 > 0; afcom--)
	{
		int numb = ((int)(Allnumb * pow(10, afcom))) % 10;
		loadFromFile(nullposx - (colvivod * numbsizex), nullposy, numbers[numb], gRenderer, numbsizex, numbsizey);
		colvivod++;
	}
	

	//output on display comma
	if(comma)
		loadFromFile(nullposx - (colvivod * numbsizex)+ (numbsizex / 2), nullposy, numbers[10], gRenderer, numbsizex/2, numbsizey);
	//output on display symbols before comma
	if (befcom != 0)
	{
		int allnum = floor(AllNumber);
		while(allnum)
		{
			int numb = allnum % 10;
			loadFromFile(nullposx - (colvivod * numbsizex)-((numbsizex / 2)*comma), nullposy, numbers[numb], gRenderer, numbsizex, numbsizey);
			allnum /= 10;
			colvivod++;
		}
	}
	else
	{
		loadFromFile(nullposx - (colvivod * numbsizex) - ((numbsizex / 2) * comma), nullposy, numbers[0], gRenderer, numbsizex, numbsizey);
	}


	SDL_RenderPresent(gRenderer);
}
void ClickToNumber(int input,int* comma,double* AllNumber, SDL_Texture** numbers)
{
	if (input < 0 || input>11)
		return;
	int AfCom = SymbolsAfterComma(*AllNumber);
	if (input == 11)
	{//input Backspace
		if (AfCom == 0)
		{
			if (*comma)
				* comma = 0;
			else
			*AllNumber = (*AllNumber - (((int)(*AllNumber))% 10)) / 10;
		}
		else
		{
			*AllNumber = *AllNumber - ((((int)(*AllNumber * pow(10, AfCom))) % 10) * pow(10, -AfCom));
		}
		
	}
	else if(input == 10)
	{//input comma
		if(AfCom == 0)
		*comma = !*comma;
		else
		{
			return;
		}
	}
	else
	{//input number
		if (*comma == 0)
		{
			*AllNumber = *AllNumber * 10 + input;
		}
		else
		{
			if (AfCom == maxAfterPoint)
				return;
			if (input == 0)
				col0++;
			else
			{
				*AllNumber = *AllNumber + (input * pow(10, -AfCom - 1));
				col0 = 0;
			}
		}
	}
	UpdateDisplay(*AllNumber, *comma, numbers);
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

		double AllNumber = 0;
		int comma = 0;
		
		//background of calculator

		//numbers for display
		SDL_Texture* numbers[12] = { loadTexture("null.jpg"),loadTexture("one.jpg"),loadTexture("two.jpg"),loadTexture("three.jpg"),loadTexture("four.jpg"),loadTexture("five.jpg"),loadTexture("six.jpg"),loadTexture("seven.jpg"),loadTexture("eight.jpg"),loadTexture("nine.jpg"),loadTexture("comma.jpg"),loadTexture("empty.jpg") };

		SDL_Texture* background = loadTexture("base2.png");

//-------------------BUTTONS-----------------------------
		//array of number textures
		SDL_Texture* arrayOfNumbers[10] = {		loadTexture("button zero.png"),
												loadTexture("button one.png"),
												loadTexture("button two.png"),
												loadTexture("button three.png"),
												loadTexture("button four.png"),
												loadTexture("button five.png"),
												loadTexture("button six.png"),
												loadTexture("button seven.png"),
												loadTexture("button eight.png"),
												loadTexture("button nine.png")	};
		//array of texture operations
		SDL_Texture* arrayOfOperations[8] = { loadTexture("button summa.png"),
											loadTexture("button difference.png"),
											loadTexture("button multiplication.png"),
											loadTexture("button backspace.png"),
											loadTexture("button equally.png"),
											loadTexture("button division.png"),
											loadTexture("button exponentiation.png"),
											loadTexture("button sqrt.png")
		};

		//button "POINT"
		SDL_Texture* buttonPoint = loadTexture("button point.png");

		//size of buttons
		int BUTTON_WIDTH = 122, BUTTON_HEIGHT = 82;

		//size of gaps between buttons
		int gapBetweenButtonW = 20, gapBetweenButtonH = 15;

		//indent from edge
		int indentSize = 16, indentFromAbove = 210;

		//create workspace of application
		createWorkspace(background, arrayOfNumbers,arrayOfOperations, buttonPoint, BUTTON_WIDTH, BUTTON_HEIGHT, gapBetweenButtonW, gapBetweenButtonH, indentSize,indentFromAbove);

	//While application is running
		while (!quit) {
			//Load background
			//SDL_RenderCopy(gRenderer, background, NULL, NULL);
			
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
		freeTexture(buttonPoint);
		for (int i = 0, j = 0; i < 10, j < 8; i++, j++) {
			freeTexture(arrayOfNumbers[i]);
			freeTexture(arrayOfOperations[j]);
		}
		close();
	}
	return 0;
}

