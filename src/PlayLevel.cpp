#include <PlayLevel.h>
#include <Map.h>
#include <Player.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <Enemy.h>
#include <Position.h>
#include <Rectangle.h>
#include <Bloc.h>
#include <GameState.h>
#include <iostream>
#include <StateReturnValue.h>
#include <PauseState.h>
#include <assert.h>

const int FRAME_RATE = 1000/40; // 40 fps
const float GRAVITY = 2.0f;

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
	m_player = player;
	m_playerRunningTexture = IMG_LoadTexture(m_renderer, m_player->getRunningTexturePath().c_str());
	if(m_playerRunningTexture == nullptr) {
		std::cerr << "Couldn't load texture." << std::endl;
		std::cerr << "IMG_Error : " << IMG_GetError() << std::endl;
		assert(m_playerRunningTexture != nullptr);
	}
	m_playerX = m_map->getSpawnX();
	m_playerY = m_map->getSpawnY();
	m_playerW = 2;
	m_playerH = 2;
	m_movingFrame = 0;
	m_totalMovingFrame = m_player->getNumImagesRunning();
	m_animationTime = 500; // Animation on 1 sec
	m_moving = false;
	m_movingTicks = 0;
	m_pause = false;
	m_return = RETURN_NOTHING;
	m_background = IMG_LoadTexture(m_renderer, "data/img/lacity.png");
	m_positionFond.x=0;
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
	Uint32 time;
	while(m_return == RETURN_NOTHING) {
		time = SDL_GetTicks();
		render();
		input();
		update();
		if(SDL_GetTicks() - time < FRAME_RATE) {
			SDL_Delay(FRAME_RATE - (SDL_GetTicks() - time));
		}
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
		SDL_GetRendererOutputSize(m_renderer, &m_width, &m_height);
		SDL_Rect src;
		SDL_Rect dest;
		if(m_map->getH() == 0) {
			std::cout << "Division with zero error" << std::endl;
			assert(m_map->getH() != 0);
		}
		int scale = m_height / m_map->getH();
		SDL_QueryTexture(m_background, NULL, NULL, &m_BGW, &m_BGH);

				SDL_Rect backgroundRect = { m_positionFond.x, -200, (m_BGH*m_width/m_height)/3, (m_BGH/3)*3 };
				SDL_RenderCopy(m_renderer, m_background, &backgroundRect, NULL);
				if(m_positionFond.x-6>m_BGW-(m_BGH*m_width/m_height)/3){
				m_positionFond.x= m_positionFond.x-6;
				}

		if(m_moving) {
			dest = { (int)(scale * m_playerX), m_height - (int)(scale * m_playerY), (int)(scale * m_playerW), (int)(scale * m_playerH) };
			int textureWidth, textureHeight;
			SDL_QueryTexture(m_playerRunningTexture, NULL, NULL, &textureWidth, &textureHeight);
			src = { textureWidth / m_totalMovingFrame * m_movingFrame, 0, textureWidth / m_totalMovingFrame, textureHeight };
			if(m_player->getDirection() == 1) {
				drawOnMap(m_playerRunningTexture, &src, m_playerX, m_playerY, m_playerW, m_playerH);
			}
			else if(m_player->getDirection() == -1) {
				drawOnMap(m_playerRunningTexture, &src, m_playerX, m_playerY, m_playerW, m_playerH, SDL_FLIP_HORIZONTAL);
			}
		}
	SDL_RenderPresent(m_renderer);
	}

}

void PlayLevel::drawOnMap(SDL_Texture *texture, SDL_Rect *srcRect, float x, float y, float w, float h, SDL_RendererFlip flip) {
	// Get render information;
	int renderWidth, renderHeight;
	SDL_GetRendererOutputSize(m_renderer, &renderWidth, &renderHeight);

	float mapWidth = m_map->getW();
	float mapHeight = m_map->getH();

	float scale = renderHeight/mapHeight;

	float mapVisibleWidth = renderWidth/scale;
	int newW, newH, newX, newY;
	newW = w * scale;
	newH = h * scale;
	newY = renderHeight - ((y + h) * scale);	
	if(m_playerX < mapVisibleWidth/2) {
		// Beggining of the level
		newX = x * scale;
	}
	else if(m_playerX > mapWidth - mapVisibleWidth/2) {
		// End of a level
		newX = (x - mapWidth + mapVisibleWidth) * scale;
	}
	else {
		// Middle of a level
		newX = (x - m_playerX + mapVisibleWidth/2) * scale;
	}

	SDL_Rect destRect = {newX, newY, newW, newH};
	SDL_RenderCopyEx(m_renderer, texture, srcRect, &destRect, 0, NULL, flip); 
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
				case SDLK_LEFT:
					m_moving = true;
					m_player->setDirection(-1);
					if(m_positionFond.x>3){
						m_positionFond.x = m_positionFond.x-4;
					}
					break;
				
				case SDLK_RIGHT:
					
					m_moving = true;
					m_player->setDirection(1);
					if(m_positionFond.x<m_BGW-(m_BGH*m_width/m_height)/3){
						m_positionFond.x = m_positionFond.x+6;
					}
					break;
				default:
					break;
				}
			}
			else if(event.type == SDL_KEYUP) {
				switch(event.key.keysym.sym) {
					case SDLK_RIGHT:
						// If D is released
						if(m_player->getDirection() != -1) {
							m_player->setDirection(0);
							m_moving = false;
						}
						break;
					case SDLK_LEFT:
						if(m_player->getDirection() != 1) {
							m_player->setDirection(0);
							m_moving = false;
						}
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
		if(m_moving) {
			if(m_movingTicks == 0) {
				m_movingTicks = SDL_GetTicks();
			}
			m_movingFrame = (int)(m_totalMovingFrame*(SDL_GetTicks() - m_movingTicks) / m_animationTime) % m_totalMovingFrame;	

		}
		else {
			m_movingTicks = 0;
		}
		
		return m_return;
	}
	return m_return; 
}
