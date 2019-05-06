#ifndef DEAD_SCREEN_H
#define DEAD_SCREEN_H
#include <SDL2/SDL.h>

//Sets up the screen that shows up if the player is killed by an ennemy
class DeadScreen {
private:
	/**
	@brief pointer SDL_Renderer
	*/
	SDL_Renderer *m_renderer;
	/**
	@brief pointer SDL_Texture
	*/
	SDL_Texture *m_background;
	/**
	@brief pointer SDL_Texture
	*/
	SDL_Texture *m_pizza;
	/**
	@brief affichage Dead Screen
	*/
	void run();
public:
	/**
	@brief Constructor
	@param renderer pointer
	*/
	DeadScreen(SDL_Renderer *renderer);
	/**
	@brief Destructor
	*/
	~DeadScreen();
};

#endif
