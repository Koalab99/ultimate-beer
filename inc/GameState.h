#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <SDL2/SDL.h>
#include <StateReturnValue.h>
 
class GameState
{
 public:
  GameState(SDL_Window* window);
  virtual ~GameState();
  
  virtual void input() = 0;
  virtual void render() = 0;
  virtual StateReturnValue update() = 0;
  
protected:
  SDL_Window* m_window;
  SDL_Renderer *m_renderer;
};
#endif
