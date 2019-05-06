#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H
#include <Button.h>
#include <StateReturnValue.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

/**
*detailed description Defines what happens when the player puts the game on hold while he ain't done playing*/

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
	/**
	@brief Pointer vector button
	*/
	std::vector<Button*> m_buttons;
	/**
	@brief pressed text button
	*/
	std::string m_buttonPressedText;
	/**
	@brief return StateReturnValue
	*/
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
	/**
	@brief Boucle render
	*/
	void render();
	/**
	@brief return StateReturnValue
	*/
	StateReturnValue update();
	/**
	@brief input managing and gestioning
	*/
	void handleInput();
};

#endif
