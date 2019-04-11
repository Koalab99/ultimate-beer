#ifndef GAME_H
#define GAME_H

#include <Player.h>
#include <PlayState.h>
#include <Map.h>
#include <Enemy.h>

class Game {
private:
	Player *m_player;
	GameState *m_state;
	bool m_quit;

public:
	Game();
	~Game();
	int init();
	int loop();
	Player *getPlayer() const;
	PlayState *getState() const;

};

#endif
