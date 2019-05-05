#include <Player.h>
#include <Map.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const float g = 0.20f;

Player::Player() {
	m_life = 3;
	m_speed = 1;
	m_runningTexturePath = "data/img/player.png";
	m_waitingTexturePath = "data/img/StaticPlayer.png";
	m_numImagesRunning = 6;
	m_direction = 1;
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
	if(x < 0) {
		m_direction = -1;
	}
	else {
		m_direction = 1;
	}
}

int Player::getDirection() const {
	return m_direction;
}

std::string Player::getRunningTexturePath() const {
	return m_runningTexturePath;
}

std::string Player::getWaitingTexturePath() const {
	return m_waitingTexturePath;
}

int Player::getNumImagesRunning() const {
	return m_numImagesRunning;
}

void Player::setLife(int life) {
	if(life >= 0) {
		m_life = life;
	}
}
