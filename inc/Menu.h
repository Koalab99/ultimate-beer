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
  /**
	@brief Constructor
	*/
  Menu(SDL_Window*);

  bool play();
  bool character();
  bool language();
  bool rules();
  bool quit();

  void input();
  StateReturnValue update();
  void render();
  /**
	@brief Destructor
	*/
  ~Menu(); 
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
	@brief true if player quit menu
	*/
  bool m_quit;
  /**
	@brief Choice of option of player 
	*/
  std::string m_choice;
  /**
	@brief Differents buttons
	*/
  std::vector<Button*> m_buttons;
  /**
	@brief Texture of background of menu
	*/
  SDL_Texture *m_background;
  /**
	@brief Texture of title 
	*/
  SDL_Texture *m_title;
};

#endif
