#include <Menu.h>
#include <GameState.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Button.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;


void Menu::input() {
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		if(e.type == SDL_QUIT) {
			m_quit = true;
			return;
		}
		else if(e.type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(&m_mouseX, &m_mouseY);	
		}

	}
}

void Menu::render() {
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);
	int w, h;
	SDL_GetRendererOutputSize(m_renderer, &w, &h);
	int BGW, BGH;
	SDL_QueryTexture(m_background, NULL, NULL, &BGW, &BGH);
	SDL_Rect backgroundRect = { (BGW - BGH*w/h)/2, 0, BGH*w/h, BGH };
	SDL_RenderCopy(m_renderer, m_background, &backgroundRect, NULL);
	std::vector<Button*>::iterator i;
	int count;
	for(count = 0, i = m_buttons.begin(); i != m_buttons.end(); ++i, count++) {
		SDL_Texture *texture = (*i)->getTexture();
		int x, y, bw, bh;
		x = w / 5;
		y = (2 + count) * h/(2+(int)m_buttons.size());
		bw = 3 * w / 5;
		bh = h / (2 + (int)m_buttons.size());
		SDL_Rect rect = { x, y, bw, bh };
		SDL_RenderCopy(m_renderer, texture, NULL, &rect);
		if(m_mouseX > x && m_mouseX < (x + bw) && m_mouseY > y && m_mouseY < (y + bh)) {
			m_mouseX = -1;
			m_mouseY = -1;
		}
		
	}
	SDL_RenderPresent(m_renderer);
}

int Menu::update() {
	if(m_quit) {
		return 1;
	}
	return 0;
}

Menu::Menu(SDL_Window* window): GameState(window){
	std::string playText = "Play";
	Button *play = new Button(m_renderer, playText);
	m_buttons.push_back(play);
	m_mouseX = -1;
	m_mouseY = -1;
	m_quit = false;
	m_background = IMG_LoadTexture(m_renderer, "data/img/lacity.png");
}

bool Menu::play(){
  return true;
}

bool Menu::character(){
  return true;
}

bool Menu::language(){
  return true;
}

bool Menu::rules() {
  return true; 
}

bool Menu::quit(){
  return true;
}

Menu::~Menu(){}
