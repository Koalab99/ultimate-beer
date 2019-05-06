#include <iostream>
#include <assert.h>
#include <Credit.h>
#include <GameState.h>
#include <string>
#include <vector>
#include <StateReturnValue.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

extern TTF_Font *gFont;

Credit::Credit(SDL_Window *window) : GameState(window), m_offset(0) {
	m_maxWidth = 0;	
	m_totalHeight = 0;
	m_return = RETURN_NOTHING;
	m_text.push_back("   The quest for the ultimate beer   ");
	m_text.push_back(" ");
	m_text.push_back(" ");
	m_text.push_back("~~Drawing~~");
	m_text.push_back("Ibrahim Ucar");
	m_text.push_back(" ");
	m_text.push_back("~~Music~~");
	m_text.push_back("Arthur Meesschaert");
	m_text.push_back(" ");
	m_text.push_back("~~Developpers~~");
	m_text.push_back("Corentin Arnould");
	m_text.push_back("Claire Beguin");
	m_text.push_back("Claire Couturier-Petrasson");

	for(std::vector<std::string>::iterator line = m_text.begin(); line != m_text.end(); line++) {
		SDL_Texture *texture = getTextTexture(*line);
		m_textures.push_back(texture);
	}
	m_uptime = SDL_GetTicks();
	int width, height;
	for(auto line : m_textures) {
		SDL_QueryTexture(line, NULL, NULL, &width, &height);
		if(width > m_maxWidth) {
			m_maxWidth = width;
		}
		m_totalHeight += height;
	}

}

Credit::~Credit() {
	for(auto i : m_textures) {
		SDL_DestroyTexture(i);
	}
}

void Credit::render() {
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	int scWidth, scHeight;
	SDL_GetRendererOutputSize(m_renderer, &scWidth, &scHeight);
	SDL_Rect rect;
	int count = 0;
	int width, height;
	int x, y, w, h; 
	float scale = (float)scWidth / (float)m_maxWidth;
	for(auto i = m_textures.begin(); i != m_textures.end(); i++, count++) {
		SDL_QueryTexture(*i, NULL, NULL, &width, &height);
		w = width * scale;
		h = height * scale;
		x = (scWidth - w)/2;
		y = scHeight + h * count - m_offset;
		rect = { x, y, w, h};
		SDL_RenderCopy(m_renderer, *i, NULL, &rect);
	}
	if(scWidth - m_offset + m_totalHeight*scale < 0) {
		m_return = RETURN_MENU;
	}
	SDL_RenderPresent(m_renderer);
}

StateReturnValue Credit::update() {
	m_offset = (float)(SDL_GetTicks() - m_uptime)/20;
	return m_return;
}

void Credit::input() {
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		if(e.type == SDL_QUIT) {
			m_return = RETURN_QUIT;
		}
	}
}

SDL_Texture *Credit::getTextTexture(const std::string &a) {
	SDL_Surface *surf = TTF_RenderText_Shaded(gFont, a.c_str(), {255, 255, 255}, {0, 0, 0});
	if(surf == NULL) {
		std::cerr << "Could not load surface" << std::endl;
		std::cerr << "TTF Error : " << TTF_GetError() << std::endl;
		assert(surf != NULL);
	}
	SDL_Texture *ret = SDL_CreateTextureFromSurface(this->m_renderer, surf);
	if(ret == NULL) {
		std::cerr << "Could not create texture" << std::endl;
		std::cerr << "SDL Error : " << SDL_GetError() << std::endl;
		assert(ret != NULL);
	}
	SDL_FreeSurface(surf);
	return ret;
}
