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
  @param w SDL_Window pointer
	*/
  Menu(SDL_Window* w);
  /**
	@brief true if player play
	*/
  bool play();
  /**
	@brief true if character exist
	*/
  bool character();
  /**
	@brief after update
	*/
  bool language();
  /**
	@brief if true go to rules
	*/
  bool rules();
  /**
	@brief if true quit game
	*/
  bool quit();
  /**
	@brief entree
	*/
  void input();
  /**
	@brief StateReturnValue
	*/
  StateReturnValue update();
  /**
	@brief boucle
	*/
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
