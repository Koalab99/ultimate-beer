#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <string>

class Player {
private:
	float m_speed;
	int m_life;
	int m_direction;
	std::string m_runningTexturePath;
	std::string m_waitingTexturePath;
	int m_numImagesRunning;	
	
public:
	Player();
	~Player();
	int getLife() const;
	float getSpeed() const;

	void setLife(int life);
	void setDirection(int x);
	int getDirection() const;
	int getNumImagesRunning() const;
	std::string getRunningTexturePath() const;
	std::string getWaitingTexturePath() const;

	void update();
};

#endif
