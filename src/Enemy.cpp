#include <Enemy.h>
#include <Rectangle.h>
using namespace std;

Enemy::Enemy(): m_alive(true),  m_rectangle(0,0,1,2) 
{
}

bool Enemy::isAlive() const
{
  return m_alive;
}

void Enemy::setAlive(bool x)
{  
  m_alive = x;
}

Rectangle Enemy::getRectangle() const
{
  return m_rectangle;
}

void Enemy::setRectangle(Rectangle rect)
{
  m_rectangle = rect;
}

Enemy::~Enemy()
{
}
