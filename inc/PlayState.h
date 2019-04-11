#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <Map.h>
#include <Player.h>
#include <SDL2/SDL.h>
#include <Enemy.h>
#include <GameState.h>

enum PlayStatesState {
	HIT,
	DEAD
};

class PlayState : public GameState {
protected:
	Map *m_map;
	std::vector<Enemy> m_enemies;
	Player *m_player;
	bool m_quit;
	void updateEnemies();
	SDL_Renderer *m_renderer;
public:
	PlayState(SDL_Window *window, std::string path, Player *player);

	~PlayState();

	void render();
	int update();
	void input();
	
	Player *getPlayer() const;
	Map *getMap() const;
};

#endif
