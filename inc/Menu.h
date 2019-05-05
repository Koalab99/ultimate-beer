#ifndef Menu_H
#define Menu_H
#include <SDL2/SDL.h>
#include <GameState.h>
#include <Button.h>
#include <vector>
#include <StateReturnValue.h>

/*Defines the menu and some of the game's possibilities, like playing or quiting, changing the langage, checking the rules...*/
class Menu: public GameState {
public:
  Menu(SDL_Window*);

  bool play();
  bool character();
  bool language();
  bool rules();
  bool quit();

  void input();
  StateReturnValue update();
  void render();

  ~Menu(); 
private:
  int m_mouseX;
  int m_mouseY;
  bool m_quit;
  std::string m_choice;
  std::vector<Button*> m_buttons;
  SDL_Texture *m_background;
};

#endif
