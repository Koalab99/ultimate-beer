#include <iostream>
#include <Game.h>
#include <Map.h>
#include <Player.h>
#include <PlayState.h>
#include <string>
#include <TextPlay.h>

Game::Game() {

}

Game::~Game() {
	if(m_player != nullptr) 
		delete m_player;
	if(m_playstate != nullptr) 
		delete m_playstate;


}

int Game::init() {
	m_map = new Map("data/map/level1.map");
	m_player = new Player(m_map);
	m_playstate = new TextPlay(m_map, m_player);
	if(m_map == nullptr || m_player == nullptr || m_playstate == nullptr) {
		return -1;
	}
	m_quit = false;
	return 0;
	
}

int Game::loop() {
	m_playstate->render();
	m_playstate->input();
	int type = m_playstate->update();
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

PlayState *Game::getPlayState() const {
	return m_playstate;
}
