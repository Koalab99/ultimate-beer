#ifndef DEAD_SCREEN_H
#define DEAD_SCREEN_H
#include <SDL2/SDL.h>

//Sets up the screen that shows up if the player is killed by an ennemy
class DeadScreen {
private:
	SDL_Renderer *m_renderer;
	SDL_Texture *m_background;
	SDL_Texture *m_pizza;
	void run();
public:
	/**
	@brief Constructor
	@param pointer renderer
	*/
	DeadScreen(SDL_Renderer *renderer);
	/**
	@brief Destructor
	*/
	~DeadScreen();
};

#endif
