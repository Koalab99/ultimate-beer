#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <Map.h>
#include <Player.h>

enum PlayStatesState {
	HIT,
	DEAD
};

class PlayState {
protected:
	Map *m_map;
	Player *m_player;

public:
	PlayState(Map *map, Player *player);
	~PlayState();

	virtual void render() = 0;
	virtual int update() = 0;
	virtual void input() = 0;
	
	Player *getPlayer() const;
	Map *getMap() const;
};

#endif
