#include <Player.h>
#include <Map.h>
#include <iostream>

const float g = 0.20f;

Player::Player(Map *map) {
	m_x = 2;
	m_y = 20;
	m_w = 1;
	m_h = 1.5;
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
	Bloc *r = m_map->collide(m_x + m_w + 1, m_y - 1);
	Bloc *l = m_map->collide(m_x - 1, m_y - 1);
	Bloc *tr = m_map->collide(m_x + m_w + 1, m_y + m_h + 1);
	Bloc *tl = m_map->collide(m_x - 1, m_y + m_h + 1);
	// If the player is supposed to not be touching the ground
	if(!m_floor) { 
		// Apply gravity
		m_speed -= g;
		// Making sure speed is not too big
		if(m_speed > 2) {
			m_speed = 2;
		}
		else if(m_speed < -2) {
			m_speed = -2;
		}
		// To slow down the jump
		m_y += m_speed*0.4;
		if(m_map == nullptr) {
			std::cerr << "Null map" << std::endl;
			return;
		}
		if((m_map->blocExists(r) || m_map->blocExists(l)) && !m_map->blocExists(m_map->collide(m_x, m_y + m_h)) && !m_map->blocExists(m_map->collide(m_x + m_h, m_y + m_h))) {
			if(m_map->blocExists(r)) {
				m_y = r->GetY() + r->GetHeight()+1;
			}
			else {
				m_y = l->GetY() + l->GetHeight() + 1;
			}
			m_speed = 0;
			m_floor = true;
		}
		if(m_map->blocExists(r) && m_map->blocExists(l) && m_map->blocExists(tr) && m_map->blocExists(tl)) {
			m_x -= m_direction;
		}
	}
	else {
		if(m_map == nullptr) {
			return ;
		}
		if(!m_map->blocExists(m_map->collide(m_x + m_w, m_y - 2)) && !m_map->blocExists(m_map->collide(m_x, m_y - 2))) {
			m_floor = false;
		}
	}
	m_x += m_direction;
 	if(m_map->blocExists(m_map->collide(m_x + m_w + 1, m_y)) && m_map->blocExists(m_map->collide(m_x + m_w + 1, m_y + m_h)) && !m_map->blocExists(m_map->collide(m_x -1, (m_y + m_y + m_h)/2))) {
		m_x--;
	}
	else if(m_map->blocExists(m_map->collide(m_x - 1, m_y)) && m_map->blocExists(m_map->collide(m_x - 1, m_y + m_h)) && !m_map->blocExists(m_map->collide(m_x + m_w + 1, (m_y + m_y + m_h)/2))) {
		m_x++;
	}

	if(m_x < 1) {
		m_x = 1;
	}
	else if(m_x >= m_map->getW()-1) {
		m_x = m_map->getW()-2;
	}
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
