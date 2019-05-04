#include <Enemy.h>
#include <Rectangle.h>
#include <Map.h>
#include <Rectangle.h>

using namespace std;

Enemy::Enemy(float x, float y): m_alive(true),  m_rectangle(x,y,2,3), m_direction(1)
{
}

Enemy::~Enemy()
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

int Enemy::getDirection() const { 
	return m_direction;
}

void Enemy::setDirection(const int direction) {
	if(direction != -1 && direction != 1) {
		m_direction = 1;
	}
	else {
		m_direction = direction;
	}
}

Bloc *Enemy::getBloc() const {
	return m_bloc;
}

void Enemy::setBloc(Bloc *bloc) {
	m_bloc = bloc;
}

void Enemy::setX(float x) {
	m_rectangle.setX(x);
}

void Enemy::setY(float y) {
	m_rectangle.setY(y);
}

float Enemy::GetX() const {
	return m_rectangle.getX();
}

float Enemy::GetY() const {
	return m_rectangle.getY();
}

float Enemy::GetWidth() const {
	return m_rectangle.getW();
}

float Enemy::GetHeight() const {
	return m_rectangle.getH();
}

bool Enemy::operator==(const Enemy &e) const {
	return m_rectangle == e.getRectangle();
}
