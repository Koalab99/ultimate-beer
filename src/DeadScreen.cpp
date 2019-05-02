#include <DeadScreen.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

extern TTF_Font *gFont;

DeadScreen::DeadScreen(SDL_Renderer *renderer) {
	m_pizza = nullptr;
	m_pizza = IMG_LoadTexture(renderer, "data/img/ZombiePizza.png");
	if(m_pizza == nullptr) {
		std::cerr << "Couldn't load image" << std::endl;
		std::cerr << "IMG_Error :" << IMG_GetError() << std::endl;
		assert(m_pizza != nullptr);
	}
	SDL_Surface *surf = TTF_RenderText_Blended(gFont, "You dead !", {0, 0, 0});
	if(surf == nullptr) {
		std::cerr << "Couldn't render text" << std::endl;
		std::cerr << "TTF_Error :" << TTF_GetError() << std::endl;
		assert(surf != nullptr);
	}
	SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, text, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(m_pizza);
	SDL_DestroyTexture(text);
	SDL_Delay(3000);
}

DeadScreen::~DeadScreen() {
	if(m_pizza != nullptr) {
		SDL_DestroyTexture(m_pizza);
		m_pizza = nullptr;
	}
	if(m_background != nullptr) {
		SDL_DestroyTexture(m_background);
		m_background = nullptr;
	}
}