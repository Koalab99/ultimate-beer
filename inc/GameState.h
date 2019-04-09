#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <SDL2/SDL.h>
 
class GameState
{
 public:
  GameState(SDL_Window* window);
  ~GameState();
  
  virtual void input() = 0;
  virtual void render() = 0;
  virtual int update() = 0;
  
protected:
  SDL_Window* m_window;
};
#endif
