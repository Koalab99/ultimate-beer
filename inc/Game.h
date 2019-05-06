#ifndef GAME_H
#define GAME_H

#include <Player.h>
#include <PlayLevel.h>
#include <Map.h>
#include <Enemy.h>
#include <GameState.h>
#include <SDL2/SDL_mixer.h>

/*Defines the basics for the game: sets up the window's size and open it,
sets up the musics, check whether you're playing or not, etc... */
class Game {
private:
	Player *m_player;
	GameState *m_state;
	bool m_quit;
	SDL_Window *m_window;
	Mix_Music *m_menuMusic;

public:
	/**
	@brief Constructor
	*/
	Game();
	/**
	@brief Destructor
	*/
	~Game();
	/**
	@brief Initiation of game(Sdl,IMG with,Mix_Init,font, musique)
	@return 0 if there are no problemes
	*/
	int init();
	/**
	@brief Selection for menu
	@return 0 if there are no problemes
	*/
	bool loop();
	/**
	@brief Get Player
	@return Pointer Player
	*/
	Player *getPlayer() const;
	/**
	@brief Get State
	@return Pointer GameState
	*/
	GameState *getState();

};

#endif
