#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H
#include <Button.h>
#include <StateReturnValue.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class PauseState {
private:
	int m_mouseX;
	int m_mouseY;
	SDL_Renderer *m_renderer;
	std::vector<Button*> m_buttons;
	std::string m_buttonPressedText;
	StateReturnValue m_returnValue;
public:
	PauseState(SDL_Renderer *renderer);
	~PauseState();
	void render();
	StateReturnValue update();
	void handleInput();
};

#endif
