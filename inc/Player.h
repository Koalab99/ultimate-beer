#ifndef PLAYER_H
#define PLAYER_H

#include <Map.h>
#include <SDL2/SDL.h>

class Player {
private:
	float m_x;
	float m_y;
	float m_w;
	float m_h;
	float m_speed;
	Map *m_map;
	bool m_floor;
	int m_life;
	int m_direction;
	SDL_Texture *m_texture;
	int nb_img;
	
	
public:
	Player();
	~Player();
	float getX() const;
	float getY() const;
	float getW() const;
	float getH() const;
	bool getFloor() const;
	int getLife() const;
	float getSpeed() const;

	void setX(float x);
	void setY(float y);
	void setW(float w);
	void setH(float h);
	void setLife(int life);
	void setMap(Map *map);
	void setDirection(int x);
	void jump();

	void update();

	void load_img(SDL_Renderer*);
	SDL_Texture* getTexture();
	
};

#endif
