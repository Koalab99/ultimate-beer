#include <WinScreen.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

extern TTF_Font *gFont;
	SDL_Texture *m_text;

WinScreen::WinScreen(SDL_Renderer *renderer) {
	m_renderer = renderer;
	int width, height;
	SDL_GetRendererOutputSize(m_renderer, &width, &height);
	m_background = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	if(m_background == NULL) {
		std::cerr << "Couldn't create texture." << std::endl;
		std::cerr << "SDL error : " << SDL_GetError() << std::endl;
		assert(m_background != NULL);
	}
	SDL_SetRenderTarget(m_renderer, m_background);
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);
	SDL_SetRenderTarget(m_renderer, NULL);

	m_beer = IMG_LoadTexture(m_renderer, "data/img/BEER.png");
	if(m_beer == NULL) {
		std::cerr << "Couldn't load image." << std::endl;
		std::cerr << "IMG error : " << IMG_GetError() << std::endl;
		assert(m_beer != NULL);
	}
	SDL_Surface *textSurface = TTF_RenderText_Blended(gFont, "You Won !", {0, 0, 0});
	if(textSurface == NULL) {
		std::cerr << "Couldn't render font." << std::endl;
		std::cerr << "TTF error : " << TTF_GetError() << std::endl;
		assert(textSurface != NULL);
		
	}
	m_text = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	if(m_text == NULL) {
		std::cerr << "Couldn't create texture from surface." << std::endl;
		std::cerr << "SDL error : " << SDL_GetError() << std::endl;
		assert(m_text != NULL);
	}
	SDL_FreeSurface(textSurface);
}

WinScreen::~WinScreen() {
	if(m_background != NULL) {
		SDL_DestroyTexture(m_background);
	}
	if(m_text != NULL) {
		SDL_DestroyTexture(m_text);
	}
	if(m_text != NULL) {
		SDL_DestroyTexture(m_beer);
	}
}

void WinScreen::show() {
	int width, height;
	SDL_GetRendererOutputSize(m_renderer, &width, &height);
	SDL_RenderCopy(m_renderer, m_background, NULL, NULL);
	SDL_Rect rect = {0, 0, width, height/4 };
	SDL_RenderCopy(m_renderer, m_text, NULL, &rect);
	rect = {width/4, height/4, width/2, height * 3 / 4 };
	SDL_RenderCopy(m_renderer, m_beer, NULL, &rect);
	SDL_RenderPresent(m_renderer);
}

