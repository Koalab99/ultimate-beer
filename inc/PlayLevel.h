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
	SDL_Texture *m_playerRunningTexture;
	SDL_Texture *m_blocTexture;
	StateReturnValue m_return;
	PauseState *m_pauseState;
	float m_playerX;
	float m_playerY;
	float m_playerW;
	float m_playerH;
	bool m_moving;
	Uint32 m_movingTicks;
	Uint32 m_animationTime;
	Uint32 m_lastUpdate;
	int m_BGW;
	int m_BGH;
	int m_width;
	int m_height;
	int m_movingFrame;
	int m_totalMovingFrame;
	bool m_pause;
	void updateEnemies();
	void drawOnMap(SDL_Texture *texture, SDL_Rect *src, float x, float y, float w, float h, SDL_RendererFlip flip = SDL_FLIP_NONE);
	SDL_Texture *m_background;
	SDL_Rect m_positionFond;
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
