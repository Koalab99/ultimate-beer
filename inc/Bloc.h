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
	@param float m_x
	*/
	void SetX(float);
	/**
	@brief Set position Y of bloc
	@param float m_y
	*/
	void SetY(float);
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
	int GetType();

	Position isInside(Position &p);
	/**
	@brief Constructor
	*/
	Bloc();
	/**
	@brief Constructeur
	@param w:m_width, h:m_height
	@param x:m_x, y:m_y 
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
