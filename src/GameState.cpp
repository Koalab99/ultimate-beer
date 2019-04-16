#include <GameState.h>
#include <SDL2/SDL.h>

GameState::GameState(SDL_Window* window): m_window(window){
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if(m_renderer == NULL) 
		exit(EXIT_FAILURE);
}


GameState::~GameState() {
}
			 

