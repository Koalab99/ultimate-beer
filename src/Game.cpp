#include <iostream>
#include <Game.h>
#include <Map.h>
#include <Player.h>
#include <PlayState.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <Menu.h>
#include <Credit.h>
#include <StateReturnValue.h>
#include <assert.h>

extern TTF_Font *gFont;

Game::Game() {
	// We don't do anything here because we need a return value for the init, which is what init does!
}

// Destructor, free memory
Game::~Game() {
	// Delete font
	TTF_CloseFont(gFont);
	// Delete player if exists
	if(m_player != nullptr) 
		delete m_player;
	// Delete current state if exists
	if(m_state != nullptr) 
		delete m_state;
	// Delete window if exists
	if(m_window != NULL)
		SDL_DestroyWindow(m_window);
	// Delete music if exists
	if(m_menuMusic != NULL) {
		Mix_FreeMusic(m_menuMusic);
	}
	// Stop all musicsw
	Mix_CloseAudio();
	// Quit SDL, TTF, IMG and Mix
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
}

int Game::init() {
	// Initializing SDL
	assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0);
	// Initializing TTF
	assert(TTF_Init() != -1);
	// Initializing IMG with flags for more images support (JPG)
	int flags = IMG_INIT_JPG;
	assert((IMG_Init(flags)&flags) == flags);
	// Initializing Mix_Init with no flags, always true 
	assert(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) != -1);
	m_window = SDL_CreateWindow("Ultimate Beer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	assert(m_window != NULL);
//	SDL_SetWindowMinimumSize(m_window, 360, 240); // Doesnt work idk why
	m_player = new Player();
	assert(m_player != nullptr);
	// Set the global font
	gFont = TTF_OpenFont("data/font/Action_Man.ttf", 128);
	if(gFont == NULL) {
		// Couldn't load global font
		std::cerr << "Could not load font" << std::endl;
		std::cerr << TTF_GetError() << std::endl;
		assert(gFont != NULL);
	}
	// Create a new menu as the current state
	m_state = new Menu(m_window);
	assert(m_state != nullptr);
	// Load the menu music
	m_menuMusic = Mix_LoadMUS("data/music/menu.wav");
	if(!m_menuMusic) {
		// The menu music couldn't load
		std::cerr << "Couldn't load menu music" << std::endl;
		std::cerr << "Mixer error : " << Mix_GetError() << std::endl;
		assert(m_menuMusic != NULL);
	}

	Mix_FadeInMusic(m_menuMusic, -1, 2000);
	m_quit = false;
	return 0;
}

bool Game::loop() {
	// Everything happens here
	// First: We draw on screen
	m_state->render();
	// Then : We get user input
	m_state->input();
	// Get the action asked by the user
	StateReturnValue type = m_state->update();
	switch(type) {
		case RETURN_QUIT:
			// User wants to quit
			// return false to end the loop
			return false;
			break;
		case RETURN_PLAY:
			// User wants the play screen
			delete m_state;
			m_state = new PlayState(m_window, m_player, m_menuMusic);
			break;
		case RETURN_MENU:
			// User wants the menu screen
			delete m_state;
			m_state = new Menu(m_window);
			break;
		case RETURN_CREDITS:
			delete m_state;
			m_state = new Credit(m_window);
			break;
		default:
			// User don't need us
			break;
	}
	return true;
}

// Getters
Player *Game::getPlayer() const {
	return m_player;
}

GameState *Game::getState() {
	return m_state;
}
