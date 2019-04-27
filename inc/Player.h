#ifndef PLAYER_H
#define PLAYER_H

#include <Map.h>
#include <SDL2/SDL.h>

class Player {
private:
	float m_speed;
	Map *m_map;
	bool m_floor;
	int m_life;
	int m_direction;
	bool m_moving;

	SDL_Texture *m_texture;
	int nb_img;
	
	
public:
	Player();
	~Player();
	bool getFloor() const;
	int getLife() const;
	float getSpeed() const;

	void setLife(int life);
	void setMap(Map *map);
	void setDirection(int x);
	void jump();

	void update();

	void loadImage(SDL_Renderer*);
	SDL_Texture* getTexture();
	
};

#endif
