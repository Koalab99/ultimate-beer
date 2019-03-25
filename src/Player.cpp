#include <Player.h>
#include <Map.h>
#include <iostream>

const float g = 0.015f;

Player::Player(Map *map) {
	m_x = 2;
	m_y = 20;
	m_w = 1;
	m_h = 2;
	m_speed = 0;
	m_floor = false;
	m_map = map;
}

Player::~Player() {
	
}

float Player::getX() const {
	return m_x;
}

float Player::getY() const {
	return m_y;
}

float Player::getW() const {
	return m_w;
}

float Player::getH() const {
	return m_w;
}

float Player::getSpeed() const {
	return m_speed;
}

bool Player::getFloor() const {
	return m_floor;
}

int Player::getLife() const {
	return m_life;
}

void Player::setX(float x) {
	if(x >= 0) {
		m_x = x;
	}
}

void Player::setY(float y) {
	if(y >= 0) {
		m_y = y;
	}
}

void Player::setW(float w) {
	if(w > 0) {
		m_w = w;
	}
}

void Player::setH(float h) {
	if(h > 0) {
		m_h = h;
	}
}

void Player::setMap(Map *map) {
	m_map = map;
}

void Player::jump() {
	if(m_floor) {
		m_floor = false;
		m_speed = 2.f;
	}
}

void Player::update() {
	if(!m_floor) {
		m_speed -= g;
		if(m_speed > 2) {
			m_speed = 2;
		}
		else if(m_speed < -2) {
			m_speed = -2;
		}
		m_y += m_speed*0.03;
		if(m_map == nullptr) {
			std::cerr << "Null map" << std::endl;
			return;
		}
		Bloc *b = m_map->collide(m_x, m_y);
		Bloc *c = m_map->collide(m_x + m_w, m_y);
		if(m_map->blocExists(b) && m_map->blocExists(c) ) {
			m_y = b->GetY() + b->GetHeight() + 1;
			m_speed = 0;
			m_floor = true;
		}
	}
	else {
		if(m_map == nullptr) {
			return ;
		}
		if(!m_map->blocExists(m_map->collide(m_x, m_y-1.01)) && 
				!m_map->blocExists(m_map->collide(m_x+m_w, m_y-1.01))) {
			m_floor = !m_floor;
		}
	}
	m_x += m_direction;
}

void Player::setDirection(int x) {
	if(x > 0) {
		m_direction = 1;
	}
	else if(x < 0) {
		m_direction = -1;
	}
	else {
		m_direction = 0;
	}
}
