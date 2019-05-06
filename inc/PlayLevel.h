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

/**
*detailed description Sets level up, especially frames and their movements, gravity, jumps, textures...
*Defines all that might happened during the game and what each function should do in each case */

class PlayLevel {
protected:
	/**
	@brief positionFond of background
	*/
	SDL_Rect m_positionFond;
	/**
	@brief pointer SDL_Renderer
	*/
	SDL_Renderer *m_renderer;
	/**
	@brief pointer class Map
	*/
	Map *m_map;
	/**
	@brief return value
	*/
	StateReturnValue m_return;
	/**
	@brief pointer class PauseState
	*/
	PauseState *m_pauseState;
	/**
	@brief pointer class Player
	*/
	Player *m_player;
	/**
	@brief pointer enemy
	*/
	std::vector<Enemy> *m_enemies;
	/**
	@brief pointer for near enemys
	*/
	std::vector<Enemy> *m_nearEnemies;
	/**
	@brief pointer for near blocs
	*/
	std::vector<Bloc> *m_nearBlocs;
	/**
	@brief pointer for near items
	*/
	std::vector<Item> *m_nearItems;
	/**
	@brief pointer texture of player run
	*/
	SDL_Texture *m_playerRunningTexture;
	/**
	@brief pointer texture of player wait
	*/
	SDL_Texture *m_playerStandingTexture;
	/**
	@brief pointer texture of bloc
	*/
	SDL_Texture *m_blocTexture;
	/**
	@brief pointer texture enemy
	*/
	SDL_Texture *m_enemyTexture;
	/**
	@brief pointer texture beer
	*/
	SDL_Texture *m_beerTexture;
	/**
	@brief pointer texture heart
	*/
	SDL_Texture *m_heartTexture;
	/**
	@brief pointer song dead enemy
	*/
	Mix_Chunk *m_enemyDeadSong;
	/**
	@brief pointer item taken
	*/
	Mix_Chunk *m_itemTaken;
	/**
	@brief position x of player
	*/
	float m_playerX;
	/**
	@brief position y of player
	*/
	float m_playerY;
	/**
	@brief weight of player
	*/
	float m_playerW;
	/**
	@brief height y of player
	*/
	float m_playerH;
	/**
	@brief Offset of visible map
	*/
	float m_mapVisibleOffset;
	/**
	@brief width of visible map
	*/
	float m_mapVisibleWidth;
	/**
	@brief acceleration of player in Y
	*/
	float m_accelerationY;
	/**
	@brief moving ticks
	*/
	Uint32 m_movingTicks;
	/**
	@brief animation time
	*/
	Uint32 m_animationTime;
	/**
	@brief moving last update
	*/
	Uint32 m_lastUpdate;
	/**
	@brief invisible remaining time
	*/
	Uint32 m_invincibleRemainingTime;
	/**
	@brief width of window
	*/
	int m_BGW;
	/**
	@brief height of window
	*/
	int m_BGH;
	/**
	@brief xidth of map
	*/
	int m_width;
	/**
	@brief height of map
	*/
	int m_height;
	/**
	@brief old position of player
	*/
	float m_oldPosition;
	/**
	@brief frame image moving
	*/
	int m_movingFrame;
	/**
	@brief total frame image moving
	*/
	int m_totalMovingFrame;
	/**
	@brief true if moving
	*/
	bool m_moving;
	/**
	@brief true if the player jump 
	*/
	bool m_jumping;
	/**
	@brief true if time is pause
	*/
	bool m_pause;
	/**
	@brief true if player is touched or false if player is not touched
	*/
	bool m_playerTouched;
	/**
	@brief update enemy
	@param currentTicks Uint32
	*/
	void updateEnemies(Uint32 currentTicks);
	/**
	@brief update collision with bloc and player
	@param currentTicks Uint32
	*/
	void updateBlocCollision(Uint32 currentTicks);
	/**
	@brief update collision with item and player
	@param currentTicks Uint32
	*/
	void updateItemCollision(Uint32 currentTicks);
	/**
	@brief update collision with enemy and player
	@param currentTicks Uint32
	*/
	void updateEnemyCollision(Uint32 currentTicks);
	/**
	@brief for draw on the map 
	@param texture pointer SDL_Texture
	@param src pointer SDL_Rect
	@param x float
	@param y float
	@param w float
	@param h float
	@param flip pointer SDL_RendererFlip 
	*/
	void drawOnMap(SDL_Texture *texture, SDL_Rect *src, float x, float y, float w, float h, SDL_RendererFlip flip = SDL_FLIP_NONE);
	/**
	@brief draw background
	*/
	void drawBackground();
	
	
public:
	/**
	@brief Construtor
	@param renderer pointer 
	@param path string 
	@param player pointer class Player
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
	/**
	@brief Return Value
	@return StateReturnValue 
	*/
	StateReturnValue update();
	/**
	@brief Boucle continue des évenements entrée par utilisateur
	*/
	void input();
	/**
	@brief pointee textur background
	*/
	SDL_Texture *m_background;
	/**
	@brief Get Player
	@return Player pointer 
	*/
	Player *getPlayer() const;
	/**
	@brief Get Map
	@return Map pointer 
	*/
	Map *getMap() const;

};

#endif
