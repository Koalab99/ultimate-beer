#ifndef BUTTON_H
#define BUTTON_H

#include <Rectangle.h>
#include <string>
#include <SDL2/SDL.h>

//Sets up the buttons for the menu (Play, Credits, Quit, Go back, etc...)

class Button {
private:
	int m_width;
	int m_height;
	std::string m_message;
	SDL_Texture *m_texture;
	SDL_Renderer *m_renderer;
public:
	/**
	@brief Constructor
	@param pointer renderer, string message
	*/
	Button(SDL_Renderer *renderer, std::string message);
	/**
	@brief Destructor
	*/
	~Button();
	/**
	@brief Get width of button
	@return int m_width
	*/
	int getW();
	/**
	@brief Get height of button
	@return int m_height
	*/
	int getH();
	/**
	@brief Get texture of button
	@return pointer Texture m_texture
	*/
	SDL_Texture *getTexture();
	/**
	@brief Get message of button
	@return string m_message
	*/
	std::string getMessage();
};

#endif
