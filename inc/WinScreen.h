#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include <SDL2/SDL.h>

//handles whatever gets drawn on the screen
class WinScreen {
private:
	SDL_Renderer *m_renderer;	
	SDL_Texture *m_background;
	SDL_Texture *m_beer;
	SDL_Texture *m_text;
public:
	WinScreen(SDL_Renderer *renderer);
	~WinScreen();

	void show();
};

#endif
