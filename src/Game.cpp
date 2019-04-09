#include <iostream>
#include <Game.h>
#include <Map.h>
#include <Player.h>
#include <PlayState.h>
#include <string>
#include <PlayState.h>
#include <SDL2/SDL.h>

Game::Game() {

}

Game::~Game() {
	if(m_player != nullptr) 
		delete m_player;
	if(m_state != nullptr) 
		delete m_state;
	if(m_enemies != nullptr)
		delete m_enemies;
}

int Game::init() {
	SDL_Window
	std::vector<Enemy> *m_enemies = new std::vector<Enemy>();
	m_map = nullptr; 
	m_player = new Player(nullptr);
	m_state = new PlayState("data/map/level1.map", m_player);
	if(m_map == nullptr || m_player == nullptr || m_state == nullptr) {
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

PlayState *Game::getState() const {
	return m_state;
}
