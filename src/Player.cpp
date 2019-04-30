#include <Player.h>
#include <Map.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const float g = 0.20f;

Player::Player() {
	m_speed = 1;
	m_runningTexturePath = "data/img/player.png";
	m_numImagesRunning = 6;
}

Player::~Player() {

}

float Player::getSpeed() const {
	return m_speed;
}

int Player::getLife() const {
	return m_life;
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

int Player::getDirection() const {
	return m_direction;
}

std::string Player::getRunningTexturePath() const {
	return m_runningTexturePath;
}

int Player::getNumImagesRunning() const {
	return m_numImagesRunning;
}

