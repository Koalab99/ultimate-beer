#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>

/**
*detailed description Defines a basic font that we can reuse here and there instead of defining a new one each we need it
*Developper's comment: "I hate to load 50000000 times the same font, so there it was."*/
 
  /**
	@brief definition of constant White
	*/
const SDL_Color WHITE = { 255, 255, 255, 255 };
/**
	@brief definition of constant Black
	*/
const SDL_Color BLACK = { 0, 0, 0, 255 };


#endif
