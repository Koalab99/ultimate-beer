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

// Setting framerate so that we don't calculate too much frames (in case your computer is so powerful
const int FPS = 40;
const int FRAME_TIME = 1000/FPS;
const float DEFAULT_SPEED = 5;

// Making a constant gravity, might be changed later and added to the map... See future updates
const float GRAVITY = 2.0f;

// Update every enemies on the map
void PlayLevel::updateEnemies() {
	// For each enemies
	for(std::vector<Enemy>::iterator i = m_enemies.begin(); i != m_enemies.end(); i++) {
		// Get the enemy hitbox
		Rectangle rect = i->getRectangle();
		// Get the bloc it is sitting on
		Bloc *b = i->getBloc();
		// If enemy can't go to the right, it goes to the left
		if(i->getDirection() == 1 && rect.getX() + rect.getW() >= b->GetX() + b->GetWidth()) {
			i->setDirection(-1);
		}
		// If enemy can't go to the left, it goes to the right
		else if(i->getDirection() == -1 && rect.getX() <= b->GetX()) {
			i->setDirection(1);
		}
		// Set new enemy position
		i->setX(rect.getX() + i->getDirection() * ENEMY_SPEED);
	}
}

// Constructor of the level
PlayLevel::PlayLevel(SDL_Renderer *renderer, std::string path, Player *player) {
	m_renderer = renderer;
	m_map = new Map(path);
	// Preparing the pause state
	m_pauseState = new PauseState(m_renderer);
	m_player = player;
	// Load running player texture into VRAM
	m_playerRunningTexture = IMG_LoadTexture(m_renderer, m_player->getRunningTexturePath().c_str());
	// Handling the case the texture failed to load
	if(m_playerRunningTexture == nullptr) {
		std::cerr << "Couldn't load texture." << std::endl;
		std::cerr << "IMG_Error : " << IMG_GetError() << std::endl;
		assert(m_playerRunningTexture != nullptr);
	}
	// Defining player position thanks to the map
	m_playerX = m_map->getSpawnX();
	m_playerY = m_map->getSpawnY();
	// Set default player height and width
	m_playerW = 2;
	m_playerH = 2;
	// Initializing the moving frame counter, will increase when running and go back to zero when stopping
	m_movingFrame = 0;
	// Get the number of frames the sprite is made of
	m_totalMovingFrame = m_player->getNumImagesRunning();
	// Time for the animation to complete, in ms
	m_animationTime = 500; 
	// Player not moving at the beggining of the game
	m_moving = false;
	// Helps slowing the sprite animation
	m_movingTicks = 0;
	// Don't pause the game now
	m_pause = false;
	// Set the return value that will be sent to the PlayState if different than RETURN_NOTHING
	m_return = RETURN_NOTHING;
	// Loading the background texture
	m_background = IMG_LoadTexture(m_renderer, "data/img/lacity.png");
	if(m_background == nullptr) {
		std::cerr << "Couldn't load texture." << std::endl;
		std::cerr << "IMG_Error : " << IMG_GetError() << std::endl;
		assert(m_background != nullptr);
	}
	// Loading bloc texture
	m_blocTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 10, 10);
	// Should be changed by Kler
	SDL_SetRenderTarget(m_renderer, m_blocTexture);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
	SDL_SetRenderTarget(m_renderer, NULL);
	// Initialize the last update
	m_lastUpdate = SDL_GetTicks();
	// Claire can explain this
	m_positionFond.x=0;
}

// PlayLevel Destructor, should free all memory allocated by us or by SDL
PlayLevel::~PlayLevel() {
	// Deleting map if existing
	if(m_map != nullptr) {
		delete m_map;
	}
	// Deleting pause state if existing
	if(m_pauseState != nullptr) {
		delete m_pauseState;
	}
}

StateReturnValue PlayLevel::run() {
	// time helps regulating the frame rate
	Uint32 time;
	while(m_return == RETURN_NOTHING) {
		// Set time to the current clock
		time = SDL_GetTicks();
		// Show things on screen
		render();
		// Get input
		input();
		// Treat input, update lot of things
		update();
		// Regulate the frame rate
		if(SDL_GetTicks() - time < FRAME_TIME) {
			SDL_Delay(FRAME_TIME - (SDL_GetTicks() - time));
		}
	}
	return m_return;
}

// Lot of getters
Player *PlayLevel::getPlayer() const {
	return m_player;
}

Map *PlayLevel::getMap() const {
	return m_map;
}

void PlayLevel::render() {
	// if the game is paused, render the pause state (seems legit)
	if(m_pause) {
		m_pauseState->render();
	}
	// if the game is not paused
	else {
		// Clearing screen
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderClear(m_renderer);
		// Won't get into trouble with a division by 0
		SDL_GetRendererOutputSize(m_renderer, &m_width, &m_height);
		if(m_map->getH() == 0) {
			std::cout << "Division with zero error" << std::endl;
			assert(m_map->getH() != 0);
		}
		// Getting the size of the background
		// Claire should explain this
		SDL_QueryTexture(m_background, NULL, NULL, &m_BGW, &m_BGH);

		SDL_Rect backgroundRect = { m_positionFond.x, -200, (m_BGH*m_width/m_height)/3, (m_BGH/3)*3 };
		SDL_RenderCopy(m_renderer, m_background, &backgroundRect, NULL);
		if(m_positionFond.x-6>m_BGW-(m_BGH*m_width/m_height)/3){
			m_positionFond.x= m_positionFond.x-6;
		}
		// Display the blocs
		// For each blocs
		for(auto i = m_map->getBlocs()->begin(); i < m_map->getBlocs()->end(); i++) {
			drawOnMap(m_blocTexture, NULL, i->GetX(), i->GetY(), i->GetWidth(), i->GetHeight());
		}
		// Player display
		SDL_Rect src;
		// Player moving
		if(m_moving) {
			int textureWidth, textureHeight;
			SDL_QueryTexture(m_playerRunningTexture, NULL, NULL, &textureWidth, &textureHeight);
			// Chosing the right part of the sprite we're going to use
			src = { textureWidth / m_totalMovingFrame * m_movingFrame, 0, textureWidth / m_totalMovingFrame, textureHeight };
			// Player moving to the right
			if(m_player->getDirection() == 1) {
				// Showing the sprite as is
				drawOnMap(m_playerRunningTexture, &src, m_playerX, m_playerY, m_playerW, m_playerH);
			}
			// Player moving to the left
			else if(m_player->getDirection() == -1) {
				// Showing the sprite flipped
				drawOnMap(m_playerRunningTexture, &src, m_playerX, m_playerY, m_playerW, m_playerH, SDL_FLIP_HORIZONTAL);
			}
		}
	// Show what we did to the people
	SDL_RenderPresent(m_renderer);
	}
}

void PlayLevel::drawOnMap(SDL_Texture *texture, SDL_Rect *srcRect, float x, float y, float w, float h, SDL_RendererFlip flip) {
	// Get render information;
	int renderWidth, renderHeight;
	SDL_GetRendererOutputSize(m_renderer, &renderWidth, &renderHeight);
	// Create variables to store map width and height
	float mapWidth = m_map->getW();
	float mapHeight = m_map->getH();
	// Simple scale
	float scale = renderHeight/mapHeight;
	// Calculating the virtual width of the visible map
	float mapVisibleWidth = renderWidth/scale;
	// Applying the scale to non-special variables
	int newW, newH, newX, newY;
	newW = w * scale;
	newH = h * scale;
	// More complex calculus because we want (0, 0) to be the bottom left corner
	// HELP : SDL treat (0, 0) as the top left corner
	newY = renderHeight - ((y + h) * scale);	
	if(m_playerX < mapVisibleWidth/2) {
		// Beggining of the map
		newX = x * scale;
	}
	else if(m_playerX > mapWidth - mapVisibleWidth/2) {
		// End of the map
		newX = (x - mapWidth + mapVisibleWidth) * scale;
	}
	else {
		// Middle of a map
		newX = (x - m_playerX + mapVisibleWidth/2) * scale;
	}
	// Creating the destination rectangle
	SDL_Rect destRect = {newX, newY, newW, newH};
	// Copy the texture to the screen
	SDL_RenderCopyEx(m_renderer, texture, srcRect, &destRect, 0, NULL, flip); 
}

void PlayLevel::input() {
	// if the game is paused, leave pause state handle input
	if(m_pause) {
		m_pauseState->handleInput();
	}
	// if game not paused
	else {
		SDL_Event event;
		// For each event
		while(SDL_PollEvent(&event) > 0)
		{ 
			if(event.type == SDL_QUIT) {
			// User clicked the cross button to quit, so we leave
				m_return = RETURN_QUIT;
			}
			else if(event.type == SDL_KEYDOWN) {
			// User pressed a key
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						// User pressed escape, want to pause
						m_pause = true;
						break;
					case SDLK_LEFT:
						// User pressed left arrow, want to go to the left
						m_moving = true;
						m_player->setDirection(-1);
						// Claire can explain that
						if(m_positionFond.x>3){
							m_positionFond.x = m_positionFond.x-4;
						}
						break;
					
					case SDLK_RIGHT:
						// User pressed right arrow, want to go to the right
						m_moving = true;
						m_player->setDirection(1);
						// Claire can explain that
						if(m_positionFond.x<m_BGW-(m_BGH*m_width/m_height)/3){
							m_positionFond.x = m_positionFond.x+6;
						}
						break;
					default:
						break;
				}
			}

			else if(event.type == SDL_KEYUP) {
			// User released a key
				switch(event.key.keysym.sym) {
					case SDLK_RIGHT:
						// If right arrow is released, stop going to the right
						if(m_player->getDirection() != -1) {
							m_player->setDirection(0);
							m_moving = false;
						}
						break;
					case SDLK_LEFT:
						// If left arrow is released, stop going to the left
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

// Update everything
StateReturnValue PlayLevel::update() {
	// If game is paused
	if(m_pause) {
		// Get the return value
		m_return = m_pauseState->update();	
		if(m_return == RETURN_BACK) {
			// User want to play, leave pause
			m_pause = false;
			m_return = RETURN_NOTHING;
		}
		else if(m_return != RETURN_NOTHING) {
			// User don't want to play anymore
			m_pause = false;
		}
		else {
			// User don't want to play for now.. Maybe later
		}
	} 
	// Game not paused, we can play !
	else {
		// If player want to move
		if(m_moving) {
			// If it didn't move before initialize the moving ticks
			if(m_movingTicks == 0) {
				m_movingTicks = SDL_GetTicks();
			}
			// Guess the frame number
			m_movingFrame = (int)(m_totalMovingFrame*(SDL_GetTicks() - m_movingTicks) / m_animationTime) % m_totalMovingFrame;	
			m_playerX += m_player->getSpeed() * DEFAULT_SPEED * m_player->getDirection() * (SDL_GetTicks() - m_lastUpdate) / 1000;
		}
		else {
			// Player don't want to move, reset the tick counter
			m_movingTicks = 0;
		}

	}
	m_lastUpdate = SDL_GetTicks();
	return m_return; 
}
