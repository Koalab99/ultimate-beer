#ifndef DEAD_SCREEN_H
#define DEAD_SCREEN_H
#include <SDL2/SDL.h>

class DeadScreen {
private:
	SDL_Renderer *m_renderer;
	SDL_Texture *m_background;
	SDL_Texture *m_pizza;
	void run();
public:
	DeadScreen(SDL_Renderer *renderer);
	~DeadScreen();
};

#endif
