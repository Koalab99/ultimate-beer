#ifndef Enemy_h
#define Enemy_h

class Enemy {
 private:
  bool  m_alive;
  Rectangle m_rectangle;

 public:
  bool isAlive();
  void setAlive(alive: bool);

  Rectangle: getRectangle();
  void setRectangle(rectangle: Rectangle);
};

#endif
