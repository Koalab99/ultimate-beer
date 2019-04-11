#include <iostream>
#include <Game.h>
#include <Map.h>
#include <Player.h>
#include <PlayState.h>
#include <string>
#include <PlayState.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

Game::Game() {

}

Game::~Game() {
	if(m_player != nullptr) 
		delete m_player;
	if(m_state != nullptr) 
		delete m_state;
	if(m_window != NULL)
		SDL_DestroyWindow(m_window);
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
}

int Game::init() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		exit(EXIT_FAILURE);	
	}
	if(TTF_Init() == -1) {
		exit(EXIT_FAILURE);
	}
	int flags = IMG_INIT_JPG;
	if((IMG_Init(flags)&flags) != flags) {
		exit(EXIT_FAILURE);
	}

	m_window = SDL_CreateWindow("Ultimate Beer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(m_window == NULL) {
		return -1;
	}
	m_player = new Player();
	m_state = new PlayState(m_window, "data/map/level1.map", m_player);
	if(m_player == nullptr || m_state == nullptr) {
		return -1;
	}
	m_quit = false;
	return 0;
}

int Game::loop() {
	m_state->render();
	m_state->input();
	int type = m_state->update();
	switch(type) {
		case 0:
			return true;
			break;
		case 1:
			return false;
			break;

		default:
			std::cout << "wtf" << std::endl;
			return false;
	}
}

Player *Game::getPlayer() const {
	return m_player;
}

GameState *Game::getState() {
	return m_state;
}
