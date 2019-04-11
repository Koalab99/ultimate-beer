#include <Enemy.h>
#include <Rectangle.h>
#include <Map.h>
using namespace std;

Enemy::Enemy(float x, float y): m_alive(true),  m_rectangle(x,y,1,2), m_direction(1), m_map(map)
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

int getDirection() const { 
	return m_direction;
}

void setDirection(const int direction) {
	if(direction != -1 && direction != 1) {
		m_direction = 1;
	}
	else {
		m_direction = direction;
	}
}

Enemy::~Enemy()
{
}
