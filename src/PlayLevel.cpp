#include <PlayLevel.h>
#include <Map.h>
#include <Player.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>
#include <algorithm>
#include <Enemy.h>
#include <Item.h>
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
// Setting default speed for player movement
const float DEFAULT_SPEED = 10;
// Making a constant gravity, might be changed later and added to the map... See future updates
const float GRAVITY = 2;
// Jump acceleration toward positive Y
const float DEFAULT_VERT_ACC = 4;
// Used to make the jump faster, slow when it becomes bigger
const float ACC_FACTOR = 200;

// Constructor of the level
PlayLevel::PlayLevel(SDL_Renderer *renderer, std::string path, Player *player) {
	// Initializing the renderer with the parameter
	m_renderer = renderer;
	// Generating the map object
	m_map = new Map(path);
	if(m_map == nullptr) {
		std::cerr << "Couldn't allocate map" << std::endl;
		assert(m_map != nullptr);
	}
	// Preparing the pause state
	m_pauseState = new PauseState(m_renderer);
	m_player = player;
	// We load enemies
	m_enemies = m_map->getEnemies();
	// Load running player texture into memory
	m_playerRunningTexture = IMG_LoadTexture(m_renderer, m_player->getRunningTexturePath().c_str());
	// Handling the case the texture failed to load
	if(m_playerRunningTexture == nullptr) {
		std::cerr << "Couldn't load texture." << std::endl;
		std::cerr << "IMG_Error : " << IMG_GetError() << std::endl;
		assert(m_playerRunningTexture != nullptr);
	}
	// Load standing player texture
	m_playerStandingTexture = IMG_LoadTexture(m_renderer, m_player->getWaitingTexturePath().c_str());
	if(m_playerStandingTexture == NULL) {
		std::cerr << "Couldn't load texture." << std::endl;
		std::cerr << "IMG_Error : " << IMG_GetError() << std::endl;
		assert(m_playerStandingTexture != NULL);
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
	// Player not jumping at the beggining of the game
	m_jumping = false;
	// Set to true if player touched an enemy
	m_playerTouched = false;
	// Not invincible for now
	m_invincibleRemainingTime = 0;
	// Helps slowing the sprite animation
	m_movingTicks = 0;
	// Don't pause the game now
	m_pause = false;
	m_nearEnemies = new std::vector<Enemy>();
	m_nearItems = new std::vector<Item>();
	m_nearBlocs = new std::vector<Bloc>();
	// Set the return value that will be sent to the PlayState if different than RETURN_NOTHING
	m_return = RETURN_NOTHING;
	// Set the return value that will be sent to the PlayState if different than RETURN_NOTHING
	m_return = RETURN_NOTHING;
	// Loading bloc texture
	m_blocTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 10, 10);
	// Should be changed by Kler
	SDL_SetRenderTarget(m_renderer, m_blocTexture);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
	SDL_SetRenderTarget(m_renderer, NULL);
	// Loading beer texture
	m_beerTexture = IMG_LoadTexture(m_renderer, "data/img/BEER.png");
	if(m_beerTexture == NULL) {
		std::cerr << "Couldn't load BEER.png" << std::endl;
		std::cerr << "IMG Error:" << IMG_GetError() << std::endl;
		assert(m_beerTexture != NULL);
	}
	// Loading enemy texture
	m_enemyTexture = IMG_LoadTexture(m_renderer, "data/img/ZombiePizza.png");
	if(m_enemyTexture == NULL) {
		std::cerr << "Couldn't load ZombiePizza.png" << std::endl;
		std::cerr << "IMG Error:" << IMG_GetError() << std::endl;
		assert(m_enemyTexture != NULL);
	}
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
	// Deleting enemies
	if(m_nearEnemies != nullptr) {
		delete m_nearEnemies;
	}
	// Deleting blocs
	if(m_nearBlocs != nullptr) {
		delete m_nearBlocs;
	}
	// Deleting items
	if(m_nearItems != nullptr) {
		delete m_nearItems;
	}
	if(m_enemyTexture != NULL) {
		SDL_DestroyTexture(m_enemyTexture);
	}
}

StateReturnValue PlayLevel::run() {
	Mix_Music *music = Mix_LoadMUS("data/music/playingMusic.wav");
	Mix_PlayMusic(music, -1);
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
	Mix_FreeMusic(music);
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
			std::cerr << "Division with zero error" << std::endl;
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
		float mapWidth = m_map->getW();
		if((m_oldPosition<m_playerX)&&(m_playerX < mapWidth))
		{
			m_positionFond.x= m_positionFond.x+4;
		}
		if((m_oldPosition>m_playerX)&&(m_positionFond.x>3))
		{
			m_positionFond.x= m_positionFond.x-4;
		}
		m_oldPosition=m_playerX;
		// Display the blocs
		// For each blocs appearing on the screen
		// Kler should have a look at what happens here, she might be interested by how I render theses black boxes...
		for(auto i = m_nearBlocs->begin(); i != m_nearBlocs->end(); i++) {
			drawOnMap(m_blocTexture, NULL, i->GetX(), i->GetY(), i->GetWidth(), i->GetHeight());
		}
		// Drawing beers
		for(auto i = m_nearItems->begin(); i != m_nearItems->end(); i++) {
			if(i->isEaten()) {
				continue;
			}
			drawOnMap(m_beerTexture, NULL, i->GetX(), i->GetY(), i->GetWidth(), i->GetHeight());
		}
		// Drawing pizza 
		for(auto i = m_nearEnemies->begin(); i != m_nearEnemies->end(); i++) {
			// It's dead, don't show it
			if(!i->isAlive()) {
				continue;
			}
			// It's going to the left
			if(i->getDirection() == -1) {
				drawOnMap(m_enemyTexture, NULL, i->GetX(), i->GetY(), i->GetWidth(), i->GetHeight(), SDL_FLIP_HORIZONTAL);
			}
			// It's going to the right
			else {
				drawOnMap(m_enemyTexture, NULL, i->GetX(), i->GetY(), i->GetWidth(), i->GetHeight());
			}
		}

		// Leave this part at the bottom so the player's texture won't be hidden by other texture
		// Player display
		if(!m_playerTouched || (m_invincibleRemainingTime/100)%2 == 1) {
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
			else {
				if(m_player->getDirection() == -1) {
					drawOnMap(m_playerStandingTexture, NULL, m_playerX, m_playerY, m_playerW, m_playerH, SDL_FLIP_HORIZONTAL);
				}
				else {
					drawOnMap(m_playerStandingTexture, NULL, m_playerX, m_playerY, m_playerW, m_playerH);
				}

			}
		}
	}

	// Show what we did to the people
	SDL_RenderPresent(m_renderer);
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
	// Applying the scale to non-special variables
	int newW, newH, newX, newY;
	newW = w * scale;
	newH = h * scale;
	// More complex calculus because we want (0, 0) to be the bottom left corner
	// HELP : SDL treat (0, 0) as the top left corner
	newY = renderHeight - ((y + h) * scale);	
	if(m_playerX < m_mapVisibleWidth/2) {
		// Beggining of the map
		newX = x * scale;
	}
	else if(m_playerX > mapWidth - m_mapVisibleWidth/2) {
		// End of the map
		newX = (x - mapWidth + m_mapVisibleWidth) * scale;
	}
	else {
		// Middle of a map
		newX = (x - m_playerX + m_mapVisibleWidth/2) * scale;
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
						break;

					case SDLK_RIGHT:
						// User pressed right arrow, want to go to the right
						m_moving = true;
						m_player->setDirection(1);
						// User pressed right arrow, want to go to the right
						m_moving = true;
						m_player->setDirection(1);
						break;
					case SDLK_SPACE:
						m_jumping = true;
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
							m_moving = false;
						}
						break;
					case SDLK_LEFT:
						// If left arrow is released, stop going to the left
						if(m_player->getDirection() != 1) {
							m_moving = false;
						}
						break;
					case SDLK_SPACE:
						// If space is released, stop jumping
						m_jumping = false;
					default:
						break;
				}
			}
		}
	}
}

// Update everything
StateReturnValue PlayLevel::update() {
	// Setting the current time for the entire function
	Uint32 currentTicks = SDL_GetTicks();
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
		// Calcul it anyway.
		m_invincibleRemainingTime += currentTicks - m_lastUpdate;
		// Check the invicibility of the player
		if(m_playerTouched && m_invincibleRemainingTime > 3000) {
			m_playerTouched = false;
		}
		m_mapVisibleWidth = m_width *  m_map->getH() / m_height;

		// Player too much at the left, we'll use the beggining of the map
		if(m_playerX < m_mapVisibleWidth/2) 
			m_mapVisibleOffset = 0;
		// Player too much at the right, we'll use the end of the map minus the width we already calculated
		else if(m_playerX > m_map->getW() - m_mapVisibleWidth/2) 
			m_mapVisibleOffset = m_map->getW() - m_mapVisibleWidth;
		// Player somewhere between the start and the end
		else 
			m_mapVisibleOffset = m_playerX - m_mapVisibleWidth/2;
		// Free some memory before reallocation
		if(m_nearEnemies != nullptr) {
			delete m_nearEnemies;
			m_nearEnemies = nullptr;
		}
		if(m_nearBlocs != nullptr) {
			delete m_nearBlocs;
			m_nearBlocs = nullptr;
		}
		if(m_nearItems != nullptr) {
			delete m_nearItems;
			m_nearItems = nullptr;
		}
		// Load the closest elements we're going to interract with
		m_nearEnemies = m_map->getEnemiesInRange(m_mapVisibleOffset, m_mapVisibleWidth);
		m_nearBlocs = m_map->getBlocsInRange(m_mapVisibleOffset, m_mapVisibleWidth);
		m_nearItems = m_map->getItemsInRange(m_mapVisibleOffset, m_mapVisibleWidth);

		// If player want to move
		if(m_moving) {
			// If it didn't move before initialize the moving ticks
			if(m_movingTicks == 0) {
				m_movingTicks = SDL_GetTicks();
			}
			// Guess the frame number
			m_movingFrame = (int)(m_totalMovingFrame*(SDL_GetTicks() - m_movingTicks) / m_animationTime) % m_totalMovingFrame;	
			m_playerX += m_player->getSpeed() * DEFAULT_SPEED * m_player->getDirection() * (SDL_GetTicks() - m_lastUpdate) / 1000;
			if(m_playerX < 0) {
				m_playerX = 0;
			}
		}
		else {
			// Player don't want to move, reset the tick counter
			m_movingTicks = 0;
		}
		// Bloc collisions
		updateBlocCollision(currentTicks);
		updateEnemyCollision(currentTicks);
		updateItemCollision(currentTicks);
		// Make enemies move
		updateEnemies(currentTicks);
		// Calculate the player's position
		m_playerY += m_accelerationY * (currentTicks - m_lastUpdate)/ ACC_FACTOR; 
		// No longer need jumping to be set
	}
	// Set current tick as last tick for next loop
	m_lastUpdate = currentTicks;
	if(m_player->getLife() < 1) {
		SDL_Delay(200);
		m_return = RETURN_DEAD;
	}
	else if(m_playerX > m_map->getW()) {
		SDL_Delay(200);
		m_return = RETURN_WIN;
	}
	return m_return; 
}

void PlayLevel::updateItemCollision(Uint32 currentTicks) {
	const Item *n  = m_map->collide(m_nearItems, m_playerX + m_playerW/2, m_playerY + m_playerH); // North
	const Item *e  = m_map->collide(m_nearItems, m_playerX + m_playerW, m_playerY + m_playerH/2); // East
	const Item *s  = m_map->collide(m_nearItems, m_playerX + m_playerW/2, m_playerY); // South
	const Item *w  = m_map->collide(m_nearItems, m_playerX, m_playerY + m_playerH/2); // West

	bool gotIt = false;
	if(n != nullptr && !n->isEaten()) {
		auto eaten = std::find(m_map->getItems()->begin(), m_map->getItems()->end(), *n);
		if(eaten != m_map->getItems()->end()) {
			eaten->setEaten(true);
			gotIt = true;
		}
	}
	if(e != nullptr && !e->isEaten()) {
		auto eaten = std::find(m_map->getItems()->begin(), m_map->getItems()->end(), *e);
		if(eaten != m_map->getItems()->end()) {
			eaten->setEaten(true);
			gotIt = true;
		}
	}
	if(w != nullptr && !w->isEaten()) {
		auto eaten = std::find(m_map->getItems()->begin(), m_map->getItems()->end(), *w);
		if(eaten != m_map->getItems()->end()) {
			eaten->setEaten(true);
			gotIt = true;
		}
	}
	if(s != nullptr && !s->isEaten()) {
		auto eaten = std::find(m_map->getItems()->begin(), m_map->getItems()->end(), *s);
		if(eaten != m_map->getItems()->end()) {
			eaten->setEaten(true);
			gotIt = true;
		}
	}
	if(gotIt) {
		// Do something to the player
	}
}

void PlayLevel::updateEnemyCollision(Uint32 currentTicks) {
	const Enemy *w  = m_map->collide(m_nearEnemies, m_playerX, m_playerY + m_playerH/2); // West
	const Enemy *nw = m_map->collide(m_nearEnemies, m_playerX, m_playerY + m_playerH);
	const Enemy *n  = m_map->collide(m_nearEnemies, m_playerX + m_playerW/2, m_playerY + m_playerH); // North
	const Enemy *ne = m_map->collide(m_nearEnemies, m_playerX + m_playerW, m_playerY + m_playerH); 
	const Enemy *e  = m_map->collide(m_nearEnemies, m_playerX + m_playerW, m_playerY + m_playerH/2); // East
	const Enemy *se = m_map->collide(m_nearEnemies, m_playerX + m_playerW, m_playerY);
	const Enemy *s  = m_map->collide(m_nearEnemies, m_playerX + m_playerW/2, m_playerY); // South
	const Enemy *sw = m_map->collide(m_nearEnemies, m_playerX, m_playerY);

	// Calculing collision
	if(n != nullptr || ne != nullptr || e != nullptr || w != nullptr || nw != nullptr) {
		// Player die !
		int life = m_player->getLife();
		if(life > 0 && !m_playerTouched) {
			m_player->setLife(life-1);
			m_playerTouched = true;
			m_invincibleRemainingTime = 0;
		}
	}
	else if(s != nullptr) {
		// Player touch the enemy and kill
		auto dead = std::find(m_enemies->begin(), m_enemies->end(), *s);
		if(dead != m_enemies->end()) 
			dead->setAlive(false);
	}
	else if(se != nullptr && e == nullptr) {
		// There is a collision in the bottom right corner
		// We don't know who will die for now
		if(m_playerX + m_playerW - se->GetX() < (se->GetX() + se->GetHeight()) - m_playerY) {
			// Player dies !
			int life = m_player->getLife();
			if(life > 0 && !m_playerTouched) {
				m_player->setLife(life-1);
				m_playerTouched = true;
				m_invincibleRemainingTime = 0;
			}
		}
		else {
			// Enemy dies
			auto dead = std::find(m_enemies->begin(), m_enemies->end(), *se);
			if(dead != m_enemies->end()) 
				dead->setAlive(false);
		}
	}
	else if(sw != nullptr && s == nullptr && w == nullptr) {
		if((sw->GetX() + sw->GetWidth()) - m_playerX < (sw->GetY() + sw->GetHeight()) - m_playerY) {
			// Player dies
			int life = m_player->getLife();
			if(life > 0 && !m_playerTouched) {
				m_player->setLife(life-1);
				m_playerTouched = true;
				m_invincibleRemainingTime = 0;
			}
		}
		else {
			// Enemy dies
			auto dead = std::find(m_enemies->begin(), m_enemies->end(), *sw);
			if(dead != m_enemies->end()) 
				dead->setAlive(false);

		}
	}
}

void PlayLevel::updateBlocCollision(Uint32 currentTicks) {
	const Bloc *n  = m_map->collide(m_nearBlocs, m_playerX + m_playerW/2, m_playerY + m_playerH); // North
	const Bloc *ne = m_map->collide(m_nearBlocs, m_playerX + m_playerW, m_playerY + m_playerH); 
	const Bloc *e  = m_map->collide(m_nearBlocs, m_playerX + m_playerW, m_playerY + m_playerH/2); // East
	const Bloc *se = m_map->collide(m_nearBlocs, m_playerX + m_playerW, m_playerY);
	const Bloc *s  = m_map->collide(m_nearBlocs, m_playerX + m_playerW/2, m_playerY); // South
	const Bloc *sw = m_map->collide(m_nearBlocs, m_playerX, m_playerY);
	const Bloc *w  = m_map->collide(m_nearBlocs, m_playerX, m_playerY + m_playerH/2); // West
	const Bloc *nw = m_map->collide(m_nearBlocs, m_playerX, m_playerY + m_playerH);

	// Calculing collision
	if(s != nullptr) {
		// Player touch the ground
		m_playerY = s->GetY() + s->GetHeight();
		if(m_jumping) {
			m_accelerationY = DEFAULT_VERT_ACC;
		}
		else {
			m_accelerationY = 0;
		}
	}
	else if(n != nullptr) {
		// Player's head touch a bloc
		if(m_accelerationY > 0) {
			m_accelerationY *= -0.25;
		}
	}
	else {
		// Player in the void, apply gravity
		m_accelerationY -= GRAVITY*(currentTicks - m_lastUpdate)/ACC_FACTOR;
	}
	// By default, the player can move horizontally
	if(e != nullptr && m_player->getDirection() == 1) {
		// Cannot go to the right
		m_playerX = e->GetX() - m_playerW;
	}
	else if(w != nullptr && m_player->getDirection() == -1) {
		// Cannot go to the left
		m_playerX = w->GetX() + w->GetWidth();
	}

	if(se != nullptr && s == nullptr && e == nullptr) {
		// There is a collision in the bottom right corner
		if(m_playerX + m_playerW - se->GetX() < (se->GetY() + se->GetHeight()) - m_playerY) {
			m_playerX = se->GetX() - m_playerW;
		}
		else {
			// In case we are jumping, don't stop us during it
			if(m_accelerationY <= 0) {
				m_accelerationY = 0;
			}
			if(m_jumping) {
				m_accelerationY = DEFAULT_VERT_ACC;
			}
			m_playerY = se->GetY() + se->GetHeight();
		}
	}
	else if(sw != nullptr && s == nullptr && w == nullptr) {
		if((sw->GetX() + sw->GetWidth()) - m_playerX < (sw->GetY() + sw->GetHeight()) - m_playerY) {
			m_playerX = sw->GetX() + sw->GetWidth();
		}
		else {
			// In case we are jumping, don't stop us during it
			if(m_accelerationY <= 0) {
				m_accelerationY = 0;
			}
			if(m_jumping) {
				m_accelerationY = DEFAULT_VERT_ACC;
			}
			m_playerY = sw->GetY() + sw->GetHeight();
		}
	}
	else if(ne != nullptr && n == nullptr && e == nullptr) {
		if(m_playerX + m_playerW - ne->GetX() < (m_playerY + m_playerH) - ne->GetY()) {
			m_playerX = ne->GetX() - m_playerW;
		}
		else {
			if(m_accelerationY > 0) {
				m_accelerationY *= -0.25;
			}
			m_playerY = ne->GetY() - m_playerH;
		}
	}
	else if(nw != nullptr && n == nullptr && w == nullptr) {
		if((nw->GetX() + nw->GetWidth()) -  m_playerX < m_playerY + m_playerH - nw->GetY()) {
			m_playerX = nw->GetX() + nw->GetWidth();
		}
		else {
			if(m_accelerationY > 0) {
				m_accelerationY *= -0.25;
			}
			m_playerY = nw->GetY() - m_playerH;
		}
	}
}

// Update every enemies on the map
void PlayLevel::updateEnemies(Uint32 currentTicks) {
	// For each enemies
	for(std::vector<Enemy>::iterator i = m_enemies->begin(); i != m_enemies->end(); i++) {
		// Get the enemy hitbox
		Rectangle rect = i->getRectangle();
		// Get the bloc it is sitting on
		Bloc *b = i->getBloc();
		if(b == nullptr || !i->isAlive()) {
			continue;
		}
		// If enemy can't go to the right, it goes to the left
		if(i->getDirection() == 1 && (rect.getX() + rect.getW() >= b->GetX() + b->GetWidth() || m_map->collide(m_map->getBlocs(), i->GetX() + i->GetWidth(), i->GetY() + i->GetHeight()/2) != nullptr)) {
			i->setDirection(-1);
		}
		// If enemy can't go to the left, it goes to the right
		else if(i->getDirection() == -1 && (rect.getX() <= b->GetX() || m_map->collide(m_map->getBlocs(), i->GetX(), i->GetY() + i->GetHeight() / 2) != nullptr)) {
			i->setDirection(1);
		}
		// Set new enemy position
		i->setX(rect.getX() + i->getDirection() * ENEMY_SPEED * (currentTicks - m_lastUpdate)/1000);
	}
}

