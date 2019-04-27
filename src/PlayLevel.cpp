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
#include <StateReturnValue.h>
#include <PauseState.h>

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
	m_map = nullptr;
	m_map = new Map(path);
	m_pauseState = new PauseState(m_renderer);
	m_pause = false;
	m_player = player;
	m_return = RETURN_NOTHING;
}

PlayLevel::~PlayLevel() {
	if(m_map != nullptr) {
		delete m_map;
	}
	if(m_pauseState != nullptr) {
		delete m_pauseState;
	}
}

StateReturnValue PlayLevel::run() {
	while(m_return == RETURN_NOTHING) {
		render();
		input();
		update();
	}


	return m_return;
}

Player *PlayLevel::getPlayer() const {
	return m_player;
}

Map *PlayLevel::getMap() const {
	return m_map;
}

void PlayLevel::render() {
	if(m_pause) {
		m_pauseState->render();
	}
	else {
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderClear(m_renderer);		
		int width;
		int height;
		SDL_GetRendererOutputSize(m_renderer, &width, &height);
		
		SDL_RenderPresent(m_renderer);

	}
}

void PlayLevel::input() {
	if(m_pause) {
		m_pauseState->handleInput();
	}
	else {
		SDL_Event event;

		while(SDL_PollEvent(&event) > 0)
		{ 
			if(event.type == SDL_QUIT) {
				m_return = RETURN_QUIT;
			}
			else if(event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						m_pause = true;
						break;
					default:
						break;

				}
			}
		}
	}
}

StateReturnValue PlayLevel::update() {
	if(m_pause) {
		m_return = m_pauseState->update();	
		if(m_return == RETURN_BACK) {
			m_pause = false;
			m_return = RETURN_NOTHING;
		}
		else if(m_return != RETURN_NOTHING) {
			m_pause = false;
			delete m_pauseState;
			m_pauseState = nullptr;
		}
	} 
	else {
		// Game code here
		return m_return;
	}
	return m_return; 
}
