#ifndef GAME_H
#define GAME_H

#include <Player.h>
#include <PlayState.h>
#include <Map.h>
#include <Enemy.h>
#include <GameState.h>

class Game {
private:
	Player *m_player;
	GameState *m_state;
	bool m_quit;
	SDL_Window *m_window;

public:
	Game();
	~Game();
	int init();
	int loop();
	Player *getPlayer() const;
	GameState *getState();

};

#endif
