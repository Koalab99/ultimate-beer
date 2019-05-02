#include <Button.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <assert.h>

extern TTF_Font *gFont;

Button::Button(SDL_Renderer *renderer, std::string message) {
	m_message = message;
	m_renderer = renderer;
	m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 256);
	SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
	// Create font and text
	SDL_Color black = {0, 0, 0};
	SDL_Surface *surface = TTF_RenderText_Blended(gFont, message.c_str(), black);
	if(surface == NULL) {
		std::cerr << "Couldn't load TTF" << std::endl;
		std::cerr << TTF_GetError() << std::endl;
		assert(surface != NULL);
	}
	// Changing text surface to text texture
	SDL_Texture *tmp = SDL_CreateTextureFromSurface(m_renderer, surface);
//	SDL_SetTextureBlendMode(tmp, SDL_BLENDMODE_NONE);
	if(tmp == NULL) {
		std::cerr << "Could not create texture from surface" << std::endl;
	}
	// Free surface
	SDL_FreeSurface(surface);
	// Changing this surface into the button's texture
	SDL_Texture *texture2 = IMG_LoadTexture(m_renderer, "data/img/sexybutton.png");//SDL_CreateTextureFromSurface(m_renderer, surface2);
	SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_NONE);
	if(m_texture == NULL) {
		std::cerr << "Could not create texture from surface" << std::endl;
		std::cerr << SDL_GetError() << std::endl;
	}
	if(SDL_SetRenderTarget(m_renderer, m_texture) < 0) {
		std::cerr << SDL_GetError() << std::endl;	
	}

	SDL_RenderCopy(m_renderer, texture2, NULL, NULL);
	SDL_RenderCopy(m_renderer, tmp, NULL, NULL);
	if(SDL_SetRenderTarget(m_renderer, NULL) < 0) {
		std::cerr << SDL_GetError() << std::endl;	
	}
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

std::string Button::getMessage() {
	return m_message;
}
