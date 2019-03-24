#ifndef GAME_H
#define GAME_H

#include <Player.h>
#include <PlayState.h>
#include <Map.h>

class Game {
private:
	Map *m_map;
	Player *m_player;
	PlayState *m_playstate;
	bool m_quit;

public:
	Game();
	~Game();
	int init();
	int loop();
	Map *getMap() const;
	Player *getPlayer() const;
	PlayState *getPlayState() const;

};

#endif
