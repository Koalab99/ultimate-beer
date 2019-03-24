#ifndef PLAYER_H
#define PLAYER_H

#include <Map.h>

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
	float m_direction;
public:
	Player(Map *map = nullptr);
	~Player();
	float getX() const;
	float getY() const;
	float getW() const;
	float getH() const;
	float getAcc() const;
	bool getFloor() const;
	int getLife() const;
	float getSpeed() const;

	void setX(float x);
	void setY(float y);
	void setW(float w);
	void setH(float h);
	void setLife(int life);
	void setMap(Map *map);
	void jump();

	void update();
};

#endif
