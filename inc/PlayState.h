#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include <SDL2/SDL.h>
#include <PlayLevel.h>
#include <LevelInfo.h>
#include <Button.h>

class PlayState : public GameState {
private:
	bool m_playing;
	bool m_quit;
	int m_mouseX;
	int m_mouseY;
	std::string m_order;
	SDL_Texture *m_background;
	std::vector<LevelInfo*> m_levels;
	Player *m_player;
	PlayLevel *m_currentLevel;
	Button *m_menuButton;

public:
	PlayState(SDL_Window *, Player *);
	~PlayState();

	void render();
	void input();
	int update();
};

#endif
