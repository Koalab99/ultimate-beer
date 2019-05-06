#ifndef Bloc_h
#define Bloc_h

#include <Position.h>

/*Defines a "bloc"  width, height and postion which we will use to define all kind of stuff (player, ennemy and plateform) before adding textures*/
class Bloc {
private:
	float m_width;
	float m_height; 
	float m_x;
	float m_y;
	int m_type;

public:
	/**
	@brief Get position Y of bloc
	@return float
	*/
	float GetX() const;
	/**
	@brief Get position Y of bloc
	@return float
	*/
	float GetY() const;
	/**
	@brief Set position X of bloc
	@param float
	*/
	void SetX(float);
	/**
	@brief Set position Y of bloc
	@param float
	*/
	void SetY(float);
	/**
	@brief Get width of bloc
	@return float
	*/
	float GetWidth() const;
	/**
	@brief Get height of bloc
	@return float
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
	@param w:width, h:height
	@param x:positionX, y:positionY 
	*/
	Bloc(float w, float h, float x, float y);
	/**
	@brief Destructor
	*/
	~Bloc();
	/**
	@brief Compares 2 bolcs and return true if they are equal
	@return bool
	*/
	bool operator==(const Bloc &other);
	/**
	@brief Compares 2 bolcs and return true if they are not equal
	@return bool
	*/
	bool operator!=(const Bloc &other);
};

#endif
