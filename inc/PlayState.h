#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <Map.h>
#include <Player.h>
#include <SDL2/SDL.h>
#include <Enemy.h>

enum PlayStatesState {
	HIT,
	DEAD
};

class PlayState {
protected:
	Map *m_map;
	std::vector<Enemy> m_enemies;
	Player *m_player;
	bool m_quit;
	void updateEnemies();
public:
	PlayState(SDL_Window *window, std::string &path, Player *player);

	virtual ~PlayState();

	virtual void render() = 0;
	virtual int update() = 0;
	virtual void input() = 0;
	
	Player *getPlayer() const;
	Map *getMap() const;
};

#endif
