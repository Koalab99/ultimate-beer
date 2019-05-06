#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <SDL2/SDL.h>
#include <StateReturnValue.h>
 
class GameState
{
 public:
  /**
	@brief Constructor
	*/
  GameState(SDL_Window* window);
  /**
	@brief Destructor of abstract class
	*/
  virtual ~GameState();
  /**
	@brief Creation of abstract class
	*/
  virtual void input() = 0;
  /**
	@brief Creation of abstract class
	*/
  virtual void render() = 0;
  /**
	@brief Creation of abstract class
	*/
  virtual StateReturnValue update() = 0;
  
protected:
  SDL_Window* m_window;
  SDL_Renderer *m_renderer;
};
#endif
