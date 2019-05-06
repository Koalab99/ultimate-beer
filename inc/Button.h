#ifndef BUTTON_H
#define BUTTON_H

#include <Rectangle.h>
#include <string>
#include <SDL2/SDL.h>

//Sets up the buttons for the menu (Play, Credits, Quit, Go back, etc...)

class Button {
private:
	/**
	@brief width of button
	*/
	int m_width;
	/**
	@brief height of button
	*/
	int m_height;
	/**
	@brief message in button
	*/
	std::string m_message;
	/**
	@brief texture of button
	*/
	SDL_Texture *m_texture;
	/**
	@brief pionter renderer
	*/
	SDL_Renderer *m_renderer;
public:
	/**
	@brief Constructor
	@param renderer pointer
	@param message string
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
