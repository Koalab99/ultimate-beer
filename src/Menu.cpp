#include <Menu.h>
#include <GameState.h>
#include <SDL2/SDL.h>

using namespace std;

Menu::Menu(SDL_Window* window): GameState(window){
}

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

Menu::~Menu(){}
