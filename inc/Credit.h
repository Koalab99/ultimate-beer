#ifndef CREDIT_H
#define CREDIT_H

#include <string>
#include <vector>
#include <GameState.h>
#include <StateReturnValue.h>
#include <SDL2/SDL.h>

class Credit: public GameState {
public:
	Credit(SDL_Window *window);
	~Credit();
	void render();
	StateReturnValue update();
	void input();
private:
	std::vector<std::string> m_text;
	std::vector<SDL_Texture *> m_textures;
	int m_totalHeight;
	StateReturnValue m_return;
	int m_maxWidth;
	Uint32 m_uptime;
	int m_offset;
	SDL_Texture *getTextTexture(const std::string &a);
};

#endif
