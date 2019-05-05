#include <Menu.h>
#include <GameState.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Button.h>
#include <vector>
#include <string>
#include <iostream>
#include <StateReturnValue.h>
#include <assert.h>

using namespace std;

// Menu constructor, take a window parameter so that it can create a render for it thanks to the GameState class inheritance
Menu::Menu(SDL_Window* window): GameState(window){
	// Create the play button
	std::string playText = "Play";
	Button *play = new Button(m_renderer, playText);
	m_buttons.push_back(play);
	// Create the credits button
	std::string creditText = "Credits";
	Button *creds = new Button(m_renderer, creditText);
	m_buttons.push_back(creds);
	// Create the quit button
	std::string quitText = "Quit";
	Button *quit = new Button(m_renderer, quitText);
	m_buttons.push_back(quit);
	// Initialize clicked mouse position
	m_mouseX = -1;
	m_mouseY = -1;
	// Initialize quit to false
	m_quit = false;
	// Load the background image
	m_background = IMG_LoadTexture(m_renderer, "data/img/lacity.png");
	assert(m_background != NULL);
}

Menu::~Menu(){
	// Loop through each buttons and delete them
	std::vector<Button*>::iterator i;
	for(i = m_buttons.begin(); i != m_buttons.end(); i++) {
		delete (*i);
	}
	// Free texture memory
	SDL_DestroyTexture(m_background);
}

// Handle events
void Menu::input() {
	// Create an event
	SDL_Event e;
	// Load it with last event
	while(SDL_PollEvent(&e)) {
		// If it's the close button, leave
		if(e.type == SDL_QUIT) {
			m_quit = true;
			return;
		}
		// If the mouse is pressed, get it's coordinates
		else if(e.type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(&m_mouseX, &m_mouseY);	
		}

	}
}

// Draw things on screen
void Menu::render() {
	// Clear the renderer
	SDL_RenderClear(m_renderer);
	// Get the renderer's size
	int w, h;
	SDL_GetRendererOutputSize(m_renderer, &w, &h);
	// Get the background width and height
	int BGW, BGH;
	SDL_QueryTexture(m_background, NULL, NULL, &BGW, &BGH);
	// Calculate the src rectangle of the background
	SDL_Rect backgroundRect = { (BGW - BGH*w/h)/2, 0, BGH*w/h, BGH };
	// Copy the texture to the renderer
	SDL_RenderCopy(m_renderer, m_background, &backgroundRect, NULL);
	std::vector<Button*>::iterator i;
	int count;
	// Reset the choice
	m_choice = "";
	// For each buttons in the buttons vector
	for(count = 0, i = m_buttons.begin(); i != m_buttons.end(); i++, count++) {
		// Get the button texture
		SDL_Texture *texture = (*i)->getTexture();
		// Set its destination rectangle
		int x, y, bw, bh;
		x = w / 5;
		y = (2 + count) * h/(2+(int)m_buttons.size());
		bw = 3 * w / 5;
		bh = h / (2 + (int)m_buttons.size());
		SDL_Rect rect = { x, y, bw, bh };
		// Copy the texture to the renderer
		SDL_RenderCopy(m_renderer, texture, NULL, &rect);
		// Test if user clicked a button
		if(m_mouseX > x && m_mouseX < (x + bw) && m_mouseY > y && m_mouseY < (y + bh)) {
			// reset the mouse position to -1
			m_mouseX = -1;
			m_mouseY = -1;
			// set the choice variable
			m_choice = (*i)->getMessage();
		}
		
	}
	// Show renderer to the screen
	SDL_RenderPresent(m_renderer);
}

// Will calculate whatever it has to calculate and then send something to the game object
StateReturnValue Menu::update() {
	// Player buttons pressed or want to close window
	if(m_quit || m_choice == "Quit") 
		return RETURN_QUIT;
	else if(m_choice == "Play")
		return RETURN_PLAY;
	else if(m_choice == "Credits")
		return RETURN_CREDITS;
	else 
		return RETURN_NOTHING;
}

// ... Kler ?
bool Menu::play(){
  return true;
}

bool Menu::character(){
  return true;
}

bool Menu::language(){
  return true;
}

bool Menu::rules() {
  return true; 
}

bool Menu::quit(){
  return true;
}

