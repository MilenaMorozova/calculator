#ifndef BUTTON_H
#define BUTTON_H
#include <SDL.h>

//size of buttons
const int BUTTON_WIDTH = 122, BUTTON_HEIGHT = 82;

//size of gaps between buttons
const int gapBetweenButtonW = 20, gapBetweenButtonH = 15;

//indent from edge
const int indentSize = 16, indentFromAbove = 210;

typedef struct button {
	SDL_Texture* base;
	int coordX, coordY;
    int button_width, button_height;
};
#endif