#ifndef Enemy_h
#define Enemy_h

#include <Rectangle.h>
#include <Map.h>
#include <iostream>
#include <string>
#include <Bloc.h>

#define ENEMY_SPEED 1.5

/**
*detailed description Sets up an ennemy: Is is alive? Where does it stands? Where is it going? etc...)*/
class Enemy {
private:
	/**
	@brief bool true if enemy is alive
	*/
	bool  m_alive;
	/**
	@brief Rectangle for dimention of enemy
	*/
	Rectangle m_rectangle;
	/**
	@brief 1 if direction forward or -1 if direction back
	*/
	int m_direction;
	/**
	@brief pointer of bloc of enemy
	*/
	Bloc *m_bloc;

public:
	/**
	@brief Constructor
	@param x m_x
	@param y m_y
	*/
	Enemy(float x, float y);
	/**
	@brief Is the enemy alive ?
	@return bool true if enemy is alive
	*/
	bool isAlive() const;
	/**
	@brief Set alive of enemy
	@param alive bool true if enemy is alive
	*/
	void setAlive(bool alive);
	/**
	@brief Get Rectangle(position and dimension) of enemy
	@return Rectangle
	*/
	Rectangle getRectangle() const;
	/**
	@brief Set Rectangle of enemy
	@param rect Rectangle : position and dimension
	*/
	void setRectangle(Rectangle rect);
	/**
	@brief Get Bloc of enemy
	@return Bloc pointer
	*/
	Bloc *getBloc() const;
	/**
	@brief Set Bloc of enemy
	@param bloc pointer
	*/
	void setBloc(Bloc *bloc);
	/**
	@brief Get Direction of enemy
	@return int 1 if direction forward or -1 if direction back
	*/
	int getDirection() const;
	/**
	@brief Set Direction of enemy
	@param direction int 1 if direction forward or -1 if direction back
	*/
	void setDirection(const int direction);
	/**
	@brief Set position X of enemy
	@param x float 
	*/
	void setX(float x);
	/**
	@brief Set position Y of enemy
	@param y float
	*/
	void setY(float y);
	/**
	@brief Get position X of enemy
	@return float x
	*/
	float GetX() const;
	/**
	@brief Get position Y of enemy
	@return float y
	*/
	float GetY() const;
	/**
	@brief Get width of enemy
	@return float:Width
	*/
	float GetWidth() const;
	/**
	@brief Get height of enemy
	@return float Height
	*/
	float GetHeight() const;
	/**
	@brief Compares 2 enemy and return true if they are equal
	@param e Enemy
	@return bool
	*/
	bool operator==(const Enemy &e) const;
	/**
	@brief Destructor
	*/
	~Enemy(); 
};

#endif
