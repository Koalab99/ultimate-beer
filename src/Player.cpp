#include <Player.h>
#include <Map.h>

const float g = 0.001f;

Player::Player(Map *map) {
	m_x = 2;
	m_y = 20;
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

void Player::setMap(Map *map) {
	m_map = map;
}

void Player::jump() {
	if(floor) {
		floor = false;
		m_speed = .05f;
	}
}

void Player::update() {
	if(!floor) {
		m_speed -= g;
		if(m_map->collide(m_x, m_y)) {
			m_floor = true;
			m_acc = 0;
		}
		else {
			m_y += m_speed;
		}
	}
}
