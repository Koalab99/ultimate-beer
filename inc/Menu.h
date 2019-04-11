#ifndef Menu_H
#define Menu_H
#include <SDL2/SDL.h>
#include <GameState.h>


class Menu: public GameState {

  Menu(SDL_Window*);

  bool play();
  bool character();
  bool language();
  bool rules();
  bool quit();

  ~Menu(); 
};

#endif
