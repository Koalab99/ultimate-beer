#ifndef PLAYER_H
#define PLAYER_H

#include <Map.h>

class Player {
private:
	float m_x;
	float m_y;
	float m_speed;
	Map *m_map;
	bool m_floor;
	int m_life;
public:
	Player(Map *map);
	~Player();
	float getX() const;
	float getY() const;
	float getAcc() const;
	bool getFloor() const;
	int getLife() const;

	void setX(float x);
	void setY(float y);
	void setLife(int life);
	void jump();

	void update();
};

#endif
