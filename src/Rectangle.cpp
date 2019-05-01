#include <Rectangle.h>

Rectangle::Rectangle(float x, float y, float w, float h) {
	setX(x);
	setY(y);
	setW(w);
	setH(h);
}

Rectangle::~Rectangle() {

}

float Rectangle::getX() const {
	return m_x;
}

float Rectangle::getY() const {
	return m_y;
}

float Rectangle::getH() const {
	return m_h;
}

float Rectangle::getW() const {
	return m_w;
}

void Rectangle::setX(float x) {
	if(x >= 0) {
		m_x = x;
	}
	else {
		m_x = 0;
	}
}

void Rectangle::setY(float y) {
	if(y >= 0) {
		m_y = y;
	}
	else {
		m_y = 0;
	}

}

void Rectangle::setW(float w) {
	if(w >= 0) {
		m_w = w;
	}
	else {
		m_w = 0;
	}

}

void Rectangle::setH(float h) {
	if(h >= 0) {
		m_h = h;
	}
	else {
		m_h = 0;
	}
}
