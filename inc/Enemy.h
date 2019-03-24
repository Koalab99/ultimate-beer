#ifndef Enemy_h
#define Enemy_h

#include <Rectangle.h>
#include <Map.h>
#include <iostream>
#include <string>


class Enemy {
 private:
  bool  m_alive;
  Rectangle m_rectangle;
  int m_direction;
  Map *m_map;

 public:
  Enemy(Map *map, float x, float y); 
  bool isAlive() const;
  void setAlive(bool alive);

  Rectangle getRectangle() const;
  void setRectangle(Rectangle rect);

  void update();

  ~Enemy(); 

};

#endif
