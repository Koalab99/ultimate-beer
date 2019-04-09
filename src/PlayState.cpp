#include <PlayState.h>
#include <Map.h>
#include <Player.h>
#include <SDL2/SDL.h>
#include <string>
#include <Enemy.h>
#include <Position.h>
#include <Rectangle.h>
#include <Bloc.h>

void PlayState::updateEnemies() {
	for(std::vector<Enemy>::iterator i = m_enemies.begin(); i != m_enemies.end(); i++) {
		Rectangle rect = i.getRectangle();
		Bloc b = i.getBloc();
		if(i.getDirection() == 1 && rect.getX() + rect.getW() >= b.getX() + b.getW()) {
			i.getDirection = -1;
		}
		else if(i.getDirection() == -1 && rect.getX <= b.getX()) {
			i.getDirection = 1;
		}
		i.setX(i.getX() + i.getDirection * ENEMY_SPEED);
	}
}

PlayState::PlayState(SDL_Window *window, std::string &path, Player *player) {
	m_map = new Map(path, &m_enemies);
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

