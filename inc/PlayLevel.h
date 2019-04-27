#ifndef PLAY_LEVEL_H
#define PLAY_LEVEL_H

#include <Map.h>
#include <Player.h>
#include <SDL2/SDL.h>
#include <Enemy.h>
#include <GameState.h>
#include <StateReturnValue.h>
#include <PauseState.h>

class PlayLevel {
protected:
	Map *m_map;
	std::vector<Enemy> m_enemies;
	Player *m_player;
	StateReturnValue m_return;
	PauseState *m_pauseState;
	bool m_pause;
	void updateEnemies();
	SDL_Renderer *m_renderer;
public:
	PlayLevel(SDL_Renderer *renderer, std::string path, Player *player);

	~PlayLevel();
	StateReturnValue run();
	void render();
	StateReturnValue update();
	void input();
	
	Player *getPlayer() const;
	Map *getMap() const;
};

#endif
