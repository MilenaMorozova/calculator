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

void createWorkspace(SDL_Texture* background, SDL_Texture* arrayOfNumbers[10], SDL_Texture* arrayOfOperations[8], SDL_Texture* buttonPoint, int BUTTON_WIDTH, int BUTTON_HEIGHT, int gapBetweenButtonW, int gapBetweenButtonH, int indentSize, int indentFromAbove) {
	
	//Load background
	SDL_RenderCopy(gRenderer, background, NULL, NULL);

	//-----------------FIRST COLUMN---------------------------
	//button "SQRT"
	loadFromFile(indentSize, indentFromAbove, arrayOfOperations[7],  BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "SEVEN"
	loadFromFile(indentSize, indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, arrayOfNumbers[7],  BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "FOUR"
	loadFromFile(indentSize, indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[4], BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "ONE"
	loadFromFile(indentSize, indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[1],  BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "POINT"
	loadFromFile(indentSize, indentFromAbove + 4 * (BUTTON_HEIGHT + gapBetweenButtonH), buttonPoint,  BUTTON_WIDTH, BUTTON_HEIGHT);

	//-----------------SECOND COLUMN---------------------------
	//button "EXPONINTIATION"
	loadFromFile(indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove, arrayOfOperations[6],  BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "EIGHT"
	loadFromFile(indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, arrayOfNumbers[8],  BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "FIVE"
	loadFromFile(indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[5],  BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "TWO"
	loadFromFile(indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[2],  BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "ZERO"
	loadFromFile(indentSize + BUTTON_WIDTH + gapBetweenButtonW, indentFromAbove + 4 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[0], BUTTON_WIDTH, BUTTON_HEIGHT);

	//-----------------THIRD COLUMN---------------------------
	//button "DIVISION"
	loadFromFile(indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove, arrayOfOperations[5], BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "NINE"
	loadFromFile(indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, arrayOfNumbers[9], BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "SIX"
	loadFromFile(indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[6], BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "THREE"
	loadFromFile(indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfNumbers[3], BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "EQUALLY"
	loadFromFile(indentSize + 2 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 4 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfOperations[4], BUTTON_WIDTH, BUTTON_HEIGHT);

	//-----------------FOUR COLUMN---------------------------
	//button "BACKSPACE"
	loadFromFile(indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove, arrayOfOperations[3], BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "MULTIPLICATION"
	loadFromFile(indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + BUTTON_HEIGHT + gapBetweenButtonH, arrayOfOperations[2], BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "DIFFERENCE"
	loadFromFile(indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 2 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfOperations[1], BUTTON_WIDTH, BUTTON_HEIGHT);
	//button "SUMMA"
	loadFromFile(indentSize + 3 * (BUTTON_WIDTH + gapBetweenButtonW), indentFromAbove + 3 * (BUTTON_HEIGHT + gapBetweenButtonH), arrayOfOperations[0], BUTTON_WIDTH, 2 * BUTTON_HEIGHT + gapBetweenButtonH);

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
int SymbolsAfterPoint(double number)
{
	number = abs(number);
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
	return col;
}
int SymbolsBeforePoint(double number)
{
	number = abs(number);
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
void UpdateDisplay(double AllNumber, int point,int col0, SDL_Texture** numbers)
{
	//variable calculation
	int nullposx = (int)(SCREEN_WIDTH * 0.83);
	int nullposy = (int)(SCREEN_HEIGHT * 0.105);
	int numbsizex = (int)(SCREEN_WIDTH * 0.05);
	int numbsizey = (int)(numbsizex * 3 / 2);
	int afcom = SymbolsAfterPoint(AllNumber);
	int befcom = SymbolsBeforePoint(AllNumber);
	int colvivod = 0;
	double Allnumb = AllNumber - (int)AllNumber;

	//Clean display
	for (int i = 0; i < 15; i++)
	{
		loadFromFile(nullposx - (i * numbsizex), nullposy, numbers[11], numbsizex, numbsizey);
	}
	//output on display 0
	for (int i = 0; i < col0; i++)
	{
		loadFromFile(nullposx - (colvivod * numbsizex), nullposy, numbers[0], numbsizex, numbsizey);
		colvivod++;
	}
	//output on display symbols after point
	for (; afcom > 0; afcom--)
	{
		int numb = ((int)(Allnumb * pow(10, afcom))) % 10;
		numb = abs(numb);
		loadFromFile(nullposx - (colvivod * numbsizex), nullposy, numbers[numb], numbsizex, numbsizey);
		colvivod++;
	}

	//output on display point
	if(point)
		loadFromFile(nullposx - (colvivod * numbsizex)+ (numbsizex / 2), nullposy, numbers[10], numbsizex/2, numbsizey);
	//output on display symbols before point
	if (befcom != 0)
	{
		int allnum = floor(abs(AllNumber));
		while(allnum)
		{
			int numb = allnum % 10;
			numb = abs(numb);
			loadFromFile(nullposx - (colvivod * numbsizex)-((numbsizex / 2)*point), nullposy, numbers[numb], numbsizex, numbsizey);
			allnum /= 10;
			colvivod++;
		}
	}
	else
	{
		loadFromFile(nullposx - (colvivod * numbsizex) - ((numbsizex / 2) * point), nullposy, numbers[0], numbsizex, numbsizey);
	}
	if (AllNumber < 0)
	{
		loadFromFile(nullposx - (colvivod * numbsizex) - ((numbsizex / 2) * point)+ (numbsizex / 2), nullposy, numbers[12], numbsizex/2, numbsizey);
	}

	SDL_RenderPresent(gRenderer);
}
void ClickToNumber(int input, double* AllNumber)
{
	if (input < -2 || input>12)
		return;
	static int point;
	static int col0;
	static SDL_Texture* numbers[13];
	int AfCom = SymbolsAfterPoint(*AllNumber);
	
	//update variables
	if (input == -1)
	{
		point = 0;
		col0 = 0;
		numbers[0] = loadTexture("null.jpg");
		numbers[1] = loadTexture("one.jpg");
		numbers[2] = loadTexture("two.jpg"); 
		numbers[3] = loadTexture("three.jpg");
		numbers[4] = loadTexture("four.jpg"); 
		numbers[5] = loadTexture("five.jpg");
		numbers[6] = loadTexture("six.jpg");
		numbers[7] = loadTexture("seven.jpg");
		numbers[8] = loadTexture("eight.jpg");
		numbers[9] = loadTexture("nine.jpg");
		numbers[10] = loadTexture("comma.jpg");
		numbers[11] = loadTexture("empty.jpg");
		numbers[12] = loadTexture("minus.jpg");
	}
	//update variables to number
	else if (input == -2)
	{
		if (SymbolsAfterPoint > 0)
			point = 1;
		else
			point = 0;
			
		col0 = 0;
	}
	//input swap sign
	else if (input == 12)
	{ 
		*AllNumber *= -1;
	}
	//input Backspace
	else if (input == 11)
	{
		if (AfCom == 0)
		{
			if (point)
				point = 0;
			else
			*AllNumber = (*AllNumber - (((int)(*AllNumber))% 10)) / 10;
		}
		else
		{
			if (col0 > 0)
				col0--;
			else
			*AllNumber = *AllNumber - ((((int)(*AllNumber * pow(10, AfCom))) % 10) * pow(10, -AfCom));
		}
		
	}
	//input comma
	else if(input == 10)
	{
		if(AfCom == 0)
		point = !point;
		else
		{
			return;
		}
	}
	//input number
	else 
	{
		if (point == 0)
		{
			*AllNumber = *AllNumber * 10 + ((*AllNumber>=0)?input:-input);
		}
		else
		{
			if (AfCom == maxAfterPoint)
				return;
			if (input == 0)
				col0++;
			else
			{
				*AllNumber = *AllNumber + (((*AllNumber >= 0) ? input : -input) * pow(10, -AfCom - 1));
				col0 = 0;
			}
		}
	}   
	UpdateDisplay(*AllNumber, point,col0, numbers);
}
void DoOperation(int input, double* AllNumber, double* MemNumber,int* sign)
{
	if (input < -2 || input>18)
		return;

	if (input == 11)
	{
		if (*sign == 12)
		{
			*AllNumber = (*MemNumber) + (*AllNumber);
		}
		else if (*sign == 13)
		{
			*AllNumber = (*MemNumber) - (*AllNumber);
		}
		else if (*sign == 14)
		{
			*AllNumber = (*MemNumber) * (*AllNumber);
		}
		else if (*sign == 16)
		{
			*AllNumber = (*MemNumber) / (*AllNumber);
		}
		*MemNumber = DBL_MIN;
		ClickToNumber(-2, AllNumber);
		return;
	}

	if (*MemNumber != DBL_MIN)
		return;
	if (input == 18)
	{
		*sign = 0;
		*AllNumber = sqrt(*AllNumber);
		ClickToNumber(-2, AllNumber);
		return;
	}
	*MemNumber = *AllNumber;
	*AllNumber = 0;
	ClickToNumber(-1, AllNumber);
	*sign = input;


}
void ClickToButton(int input, double* AllNumber, double* MemNumber,int* sign)
{
	
	if (input < 11)
	{
		ClickToNumber(input, AllNumber);
	}
	else if (input == 15)
	{
		ClickToNumber(11, AllNumber);
	}
	else if (input == 17)
	{
		ClickToNumber(12, AllNumber);
	}
	else
	{
		DoOperation(input, AllNumber, MemNumber,sign);
	}
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
		double memNumber = DBL_MIN;
		int sign = 0;
			//background of calculator

		//numbers for display
		
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
		int vvod = -1;
		while (vvod!= -3)
		{
			ClickToButton(vvod, &AllNumber, &memNumber,&sign);
			scanf_s("%i", &vvod);
		}
		

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

