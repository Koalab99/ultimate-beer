#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <PlayLevel.h>
#include <LevelInfo.h>
#include <Button.h>
#include <StateReturnValue.h>

class PlayState : public GameState {
private:
	bool m_playing;
	bool m_quit;
	int m_mouseX;
	int m_mouseY;
	std::string m_order;
	SDL_Texture *m_background;
	Mix_Music *m_music;
	std::vector<LevelInfo*> m_levels;
	Player *m_player;
	PlayLevel *m_currentLevel;
	Button *m_menuButton;

public:
	/**
	@brief Constructor
	@param pointer SDL_Window, pointer Player, pointer Mix_Music
	*/
	PlayState(SDL_Window *, Player *, Mix_Music *);
	/**
	@brief Destructor
	*/
	~PlayState();
	/**
	@brief Boucle render
	*/
	void render();
	/**
	@brief Boucle input
	*/
	void input();
	StateReturnValue update();
};

#endif
