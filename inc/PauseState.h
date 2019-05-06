#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H
#include <Button.h>
#include <StateReturnValue.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

/*Defines what happens when the player puts the game on hold while he ain't done playing*/

class PauseState {
private:
	/**
	@brief Position X of the mouse
	*/
	int m_mouseX;
	/**
	@brief Position Y of the mouse
	*/
	int m_mouseY;
	/**
	@brief Pointer of renderer
	*/
	SDL_Renderer *m_renderer;
	std::vector<Button*> m_buttons;
	std::string m_buttonPressedText;
	StateReturnValue m_returnValue;
public:
	/**
	@brief Constructor 
	*/
	PauseState(SDL_Renderer *renderer);
	/**
	@brief Destructor
	*/
	~PauseState();
	void render();
	StateReturnValue update();
	void handleInput();
};

#endif
