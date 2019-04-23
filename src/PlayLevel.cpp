#include <PlayLevel.h>
#include <Map.h>
#include <Player.h>
#include <SDL2/SDL.h>
#include <string>
#include <Enemy.h>
#include <Position.h>
#include <Rectangle.h>
#include <Bloc.h>
#include <GameState.h>
#include <iostream>

void PlayLevel::updateEnemies() {
	for(std::vector<Enemy>::iterator i = m_enemies.begin(); i != m_enemies.end(); i++) {
		Rectangle rect = i->getRectangle();
		Bloc *b = i->getBloc();
		if(i->getDirection() == 1 && rect.getX() + rect.getW() >= b->GetX() + b->GetWidth()) {
			i->setDirection(-1);
		}
		else if(i->getDirection() == -1 && rect.getX() <= b->GetX()) {
			i->setDirection(1);
		}
		i->setX(rect.getX() + i->getDirection() * ENEMY_SPEED);
	}
}

PlayLevel::PlayLevel(SDL_Renderer *renderer, std::string path, Player *player) {
	m_renderer = renderer;
//	m_map = new Map(path, &m_enemies);
	m_player = player;
	m_quit = false;
}

PlayLevel::~PlayLevel() {
	if(m_map != nullptr) {
		delete m_map;
	}
}

int PlayLevel::run() {
	int updateState;
	while(!m_quit) {
		render();
		input();
		updateState = update();
	}

	return updateState;
}

Player *PlayLevel::getPlayer() const {
	return m_player;
}

Map *PlayLevel::getMap() const {
	return m_map;
}

void PlayLevel::render() {
	
}

void PlayLevel::input() {
  SDL_Event event;

  while(SDL_PollEvent(&event) > 0)
    { 
      if(event.type == SDL_QUIT)
	{
	  m_quit = true;
	  
	}
    }
}

int PlayLevel::update() {
  if(m_quit == true)
    {
	return 1;
    }
  return 0; 
}
