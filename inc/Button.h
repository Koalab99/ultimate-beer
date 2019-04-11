#ifndef BUTTON_H
#define BUTTON_H

#include <Rectangle.h>
#include <string>
#include <SDL2/SDL.h>

class Button {
private:
	int m_width;
	int m_height;
	SDL_Texture *m_texture;
	SDL_Renderer *m_renderer;
public:
	Button(SDL_Renderer *renderer,std::string &message);
	~Button();

	int getW();
	int getH();

	SDL_Texture *getTexture();
};

#endif
