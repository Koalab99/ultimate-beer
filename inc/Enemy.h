#ifndef Enemy_h
#define Enemy_h

#include <Rectangle.h>
#include <Map.h>
#include <iostream>
#include <string>
#include <Bloc.h>

#define ENEMY_SPEED 0.01

class Map;
class Enemy {
 private:
  bool  m_alive;
  Rectangle m_rectangle;
  int m_direction;
  Map *m_map;
  Bloc *m_bloc;

 public:
  Enemy(float x, float y); 
  bool isAlive() const;
  void setAlive(bool alive);

  Rectangle getRectangle() const;
  void setRectangle(Rectangle rect);

  Bloc *getBloc() const;
  void setBloc(Bloc *bloc);

  int getDirection() const;
  void setDirection(const int direction);

  void setX(float x);

  ~Enemy(); 
};

#endif
