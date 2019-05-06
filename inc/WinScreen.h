#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include <SDL2/SDL.h>

//handles whatever gets drawn on the screen
class WinScreen {
private:
	/**
	@brief pointer SDL_Renderer
	*/
	SDL_Renderer *m_renderer;	
	/**
	@brief pointer SDL_Texture for background of win screen
	*/
	SDL_Texture *m_background;
	/**
	@brief pointer SDL_Renderer for beer
	*/
	SDL_Texture *m_beer;
	/**
	@brief pointer SDL_Renderer for text of win screen
	*/
	SDL_Texture *m_text;
public:
/**
	@brief Constructor
	@param renderer pointer
	*/
	WinScreen(SDL_Renderer *renderer);
	/**
	@brief Destructor
	*/
	~WinScreen();
	/**
	@brief Affichage of win screen 
	*/
	void show();
};

#endif
