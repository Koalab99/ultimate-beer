#ifndef PLAY_LEVEL_H
#define PLAY_LEVEL_H

#include <Map.h>
#include <Player.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <Enemy.h>
#include <GameState.h>
#include <StateReturnValue.h>
#include <PauseState.h>

/* Sets level up, especially frames and their movements, gravity, jumps, textures...
Defines all that might happened during the game and what each function should do in each case */

class PlayLevel {
protected:
	SDL_Rect m_positionFond;
	SDL_Renderer *m_renderer;
	Map *m_map;
	StateReturnValue m_return;
	PauseState *m_pauseState;
	Player *m_player;
	std::vector<Enemy> *m_enemies;
	std::vector<Enemy> *m_nearEnemies;
	std::vector<Bloc> *m_nearBlocs;
	std::vector<Item> *m_nearItems;
	SDL_Texture *m_playerRunningTexture;
	SDL_Texture *m_playerStandingTexture;
	SDL_Texture *m_blocTexture;
	SDL_Texture *m_enemyTexture;
	SDL_Texture *m_beerTexture;
	SDL_Texture *m_heartTexture;
	Mix_Chunk *m_enemyDeadSong;
	Mix_Chunk *m_itemTaken;
	float m_playerX;
	float m_playerY;
	float m_playerW;
	float m_playerH;
	float m_mapVisibleOffset;
	float m_mapVisibleWidth;
	float m_accelerationY;
	Uint32 m_movingTicks;
	Uint32 m_animationTime;
	Uint32 m_lastUpdate;
	Uint32 m_invincibleRemainingTime;
	int m_BGW;
	int m_BGH;
	int m_width;
	int m_height;
	float m_oldPosition;
	int m_movingFrame;
	int m_totalMovingFrame;
	bool m_moving;
	bool m_jumping;
	bool m_pause;
	bool m_playerTouched;
	void updateEnemies(Uint32 currentTicks);
	void updateBlocCollision(Uint32 currentTicks);
	void updateItemCollision(Uint32 currentTicks);
	void updateEnemyCollision(Uint32 currentTicks);
	void drawOnMap(SDL_Texture *texture, SDL_Rect *src, float x, float y, float w, float h, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawBackground();
	
	
public:
	/**
	@brief Construtor
	@param pointer renderer, string path, pointer Player
	*/
	PlayLevel(SDL_Renderer *renderer, std::string path, Player *player);
	/**
	@brief Destructor
	*/
	~PlayLevel();
	/**
	@brief Player run
	@return StateReturnValue m_return
	*/
	StateReturnValue run();
	/**
	@brief Boucle continue des évenements
	*/
	void render();
	StateReturnValue update();
	/**
	@brief Boucle continue des évenements entrée par utilisateur
	*/
	void input();
	SDL_Texture *m_background;
	/**
	@brief Get Player
	@return pointer Player
	*/
	Player *getPlayer() const;
	/**
	@brief Get Map
	@return pointer Map
	*/
	Map *getMap() const;

};

#endif
