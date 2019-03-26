#include <PlayState.h>
#include <Map.h>
#include <Player.h>

PlayState::PlayState(Map *map, Player *player) {
	m_map = map;
	m_player = player;
	m_quit = false;
}

PlayState::~PlayState() {
	if(m_map != nullptr) {
		delete m_map;
	}
}

Player *PlayState::getPlayer() const {
	return m_player;
}

Map *PlayState::getMap() const {
	return m_map;
}

