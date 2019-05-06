#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <string>

/* Defines the player's avatar: how fast and where is it going, how much life it has, what it looks like...*/
class Player {
private:
	/**
	@brief Speed of player
	*/
	float m_speed;
	/**
	@brief Number of life of player
	*/
	int m_life;
	/**
	@brief 1 if direction forward or -1 if direction back
	*/
	int m_direction;
	/**
	@brief Name of Texture for run 
	*/
	std::string m_runningTexturePath;
	/**
	@brief Name of Texture for wait
	*/
	std::string m_waitingTexturePath;
	/**
	@brief Number of image needed to make the player run
	*/
	int m_numImagesRunning;	
	
public:
	/**
	@brief Constructor
	*/
	Player();
	/**
	@brief Destructor
	*/
	~Player();
	/**
	@brief Get number of life of player. Life of beiginig is 3.
	@return int m_life
	*/
	int getLife() const;
	/**
	@brief Get speed of player. Speed of beigining is 1.
	@return float m_speed
	*/
	float getSpeed() const;
	/**
	@brief Set number of life of player.
	@param m_life int
	*/
	void setLife(int life);
	/**
	@brief Set direction of player. 1 if direction forward or -1 if direction back
	@param life int m_direction
	*/
	void setDirection(int x);
	/**
	@brief Get direction of player. 1 if direction forward or -1 if direction back
	@return x int m_direction
	*/
	int getDirection() const;
	/**
	@brief Get the number of image needed to make the player run 
	@return int m_numImagesRunning
	*/
	int getNumImagesRunning() const;
	/**
	@brief Get texture to make the player run
	@return string m_runningTexturePath
	*/
	std::string getRunningTexturePath() const;
	/**
	@brief Get texture to make the player wait
	@return string m_waitingTexturePath
	*/
	std::string getWaitingTexturePath() const;
	/**
	@brief boucle update
	*/
	void update();
};

#endif
