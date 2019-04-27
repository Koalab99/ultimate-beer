#include <Player.h>
#include <Map.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const float g = 0.20f;

Player::Player() {
	m_speed = 0;
	m_floor = false;
}

Player::~Player() {

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

void Player::loadImage(SDL_Renderer *load)
{
	SDL_DestroyTexture(m_texture);
	m_texture = IMG_LoadTexture(load, "data/img/player.png");
}

SDL_Texture* Player::getTexture(){
	return m_texture; 
}

