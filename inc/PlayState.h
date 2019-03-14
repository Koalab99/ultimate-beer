#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <Map.h>
#include <Player.h>

class PlayState {
private:
	Map *m_map;
	Player *m_player;

public:
	PlayState(Map *map, Player *player);
	~PlayState();

	void render() = 0;
	void update();
	void input() = 0;
	
	Player *getPlayer() const;
	Map *getMap() const;
}

#endif
