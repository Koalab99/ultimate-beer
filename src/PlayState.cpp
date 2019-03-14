#include <Map.h>
#include <Player.h>

PlayState::PlayState(Map *map, Player *player) {
	m_map = map;
	m_player = player;
}

PlayState::~PlayState() {

}

void PlayState::update() {
	m_map->update();
	m_player->update();
}

Player *PlayState::getPlayer() const {
	return m_player;
}

Map *PlayState::getMap() const {
	return m_map;
}

