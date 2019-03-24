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


}

int Game::init() {
	m_map = new Map("testMap.map");
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
	return m_playstate->update();
}

Player *Game::getPlayer() const {
	return m_player;
}

PlayState *Game::getPlayState() const {
	return m_playstate;
}
