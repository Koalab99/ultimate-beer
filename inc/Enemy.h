#ifndef Enemy_h
#define Enemy_h

#include <Rectangle.h>
#include <iostream>
#include <string>


class Enemy {
 private:
  bool  m_alive;
  Rectangle m_rectangle;

 public:
  Enemy(); 
  bool isAlive() const;
  void setAlive(bool alive);

  Rectangle getRectangle() const;
  void setRectangle(Rectangle rect);

  ~Enemy(); 
};

#endif
