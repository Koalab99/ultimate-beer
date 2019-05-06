#ifndef Bloc_h
#define Bloc_h

#include <Position.h>

/*Defines a "bloc"  width, height and postion which we will use to define all kind of stuff (player, ennemy and plateform) before adding textures*/
class Bloc {
private:
	/**
	@brief Width of Bloc
	*/
	float m_width;
	/**
	@brief Height of Bloc
	*/
	float m_height;
	/**
	@brief Position left lower corner X of bloc
	*/ 
	float m_x;
	/**
	@brief Position left lower corner X of bloc
	*/
	float m_y;
	/**
	@brief type of bloc
	*/
	int m_type;

public:
	/**
	@brief Get position X of bloc
	@return float m_x
	*/
	float GetX() const;
	/**
	@brief Get position Y of bloc
	@return float m_y
	*/
	float GetY() const;
	/**
	@brief Set position X of bloc
	@param x float m_x
	*/
	void SetX(float x);
	/**
	@brief Set position Y of bloc
	@param y float m_y
	*/
	void SetY(float y);
	/**
	@brief Get width of bloc
	@return float m_width
	*/
	float GetWidth() const;
	/**
	@brief Get height of bloc
	@return float height
	*/
	float GetHeight() const;
	/**
	@brief Get type
	@return int m_type
	*/
	int GetType();
	/**
	@brief Player is in bloc?
	@param p
	@return Position
	*/
	Position isInside(Position &p);
	/**
	@brief Constructor
	*/
	Bloc();
	/**
	@brief Constructeur
	@param w m_width
	@param h m_height
	@param x m_x
	@param y m_y 
	*/
	Bloc(float w, float h, float x, float y);
	/**
	@brief Destructor
	*/
	~Bloc();
	/**
	@brief Compares 2 bolcs and return true if they are equal
	@return bool true if they are equal
	*/
	bool operator==(const Bloc &other);
	/**
	@brief Compares 2 bolcs and return true if they are not equal
	@return bool true if they are not equal
	*/
	bool operator!=(const Bloc &other);
};

#endif
