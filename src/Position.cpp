#include <Position.h>

float Position::getX() const {
	return m_x;
}

float Position::getY() const {
	return m_y;
}

void Position::setX(float x) {
	m_x = x;
}

void Position::setY(float y) {
	m_y = y;
}

Position Position::operator+(Position &b) {
	Position c;
	c.setX(m_x + b.getX());
	c.setY(m_y + b.getY());
	return c;
}

Position Position::operator-(Position &b) {
	Position c;
	c.setX(m_x - b.getX());
	c.setY(m_y - b.getY());
	return c;
}

bool Position::isNull() const {
	return m_x == 0 && m_y == 0;
}
