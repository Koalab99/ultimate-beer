#include <iostream>
#include <Game.h>
#include <Map.h>
#include <Player.h>
#include <PlayState.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <Menu.h>
#include <StateReturnValue.h>

extern TTF_Font *gFont;

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
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
		exit(EXIT_FAILURE);	
	}
	if(TTF_Init() == -1) {
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	int flags = IMG_INIT_JPG;
	if((IMG_Init(flags)&flags) != flags) {
		SDL_Quit();
		TTF_Quit();
		exit(EXIT_FAILURE);
	}

	m_window = SDL_CreateWindow("Ultimate Beer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(m_window == NULL) {
		return -1;
	}
//	SDL_SetWindowMinimumSize(m_window, 360, 240); // Doesnt work idk why
	m_player = new Player();
	gFont = TTF_OpenFont("data/font/Action_Man.ttf", 128);
	if(gFont == NULL) {
		std::cerr << "Could not load font" << std::endl;
		std::cerr << TTF_GetError() << std::endl;
	}
	m_state = new Menu(m_window);
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
		case RETURN_QUIT:
			return false;
			break;
		case RETURN_PLAY:
			delete m_state;
			m_state = new PlayState(m_window, m_player);
			break;
		case RETURN_MENU:
			delete m_state;
			m_state = new Menu(m_window);
			break;
		default:
			break;
	}
	return true;
}

Player *Game::getPlayer() const {
	return m_player;
}

GameState *Game::getState() {
	return m_state;
}
