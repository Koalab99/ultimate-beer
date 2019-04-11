#include <Button.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Button::Button(SDL_Renderer *renderer, std::string &message) {
	m_renderer = renderer;
	TTF_Font* action = TTF_OpenFont("data/font/Action_Man.ttf", 256);
	SDL_Color black = {0, 0, 0};
//	SDL_Color white = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Blended(action, message.c_str(), black);
	if(surface == NULL) {
		std::cerr << "Impossible loading TTF" << std::endl;
		std::cerr << TTF_GetError() << std::endl;
	}
	SDL_Texture *tmp = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("data/img/button.png");
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_SetRenderTarget(m_renderer, m_texture);
	SDL_RenderCopy(m_renderer, tmp, NULL, NULL);
	SDL_SetRenderTarget(m_renderer, NULL);
	TTF_CloseFont(action);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(tmp);
}

Button::~Button() {
	if(m_texture != NULL) {
		SDL_DestroyTexture(m_texture);
	}
}

int Button::getW() {
	return m_width;
}

int Button::getH() {
	return m_height;
}

SDL_Texture *Button::getTexture() {
	return m_texture;
}
