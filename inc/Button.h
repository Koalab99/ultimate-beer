#ifndef BUTTON_H
#define BUTTON_H

#include <Rectangle.h>
#include <string>
#include <SDL2/SDL.h>
#include <EnumMenuChoice.h>

class Button {
private:
	int m_width;
	int m_height;
	std::string m_message;
	SDL_Texture *m_texture;
	SDL_Renderer *m_renderer;
	EnumMenuChoice m_choice;
public:
	Button(SDL_Renderer *renderer, std::string message);
	~Button();

	int getW();
	int getH();
	EnumMenuChoice getChoice() const;

	SDL_Texture *getTexture();
	std::string getMessage();
};

#endif
