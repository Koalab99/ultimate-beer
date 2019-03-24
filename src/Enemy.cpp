#include <Enemy.h>
#include <Rectangle.h>
#include <Map.h>
using namespace std;

Enemy::Enemy(Map *map, float x, float y): m_alive(true),  m_rectangle(x,y,1,2), m_direction(1), m_map(map)
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

void Enemy::update() {
	Rectangle r(m_rectangle.getX() + m_direction, m_rectangle.getY(), m_rectangle.getW(), m_rectangle.getH());
	if(m_map->fall(r.getX(), r.getY(), r.getW())) {
		m_direction *= -1;
	}
	else {
		m_rectangle = r;
	}
}
