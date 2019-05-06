#ifndef ITEM_H
#define ITEM_H

#include <Rectangle.h>
#include <iostream>

/*Defines the general position of an item, it's general shape (width and height)
Determines if it has been eaten by the player, and what happens if so*/
class Item {
private:
	/**
	@brief position X Item 
	*/
	float m_x;
	/**
	@brief position Y Item 
	*/
	float m_y;
	/**
	@brief Rectangle of item give dimention and position 
	*/
	Rectangle m_rectangle;
	/**
	@brief true if item are eaten and false if item are not eaten 
	*/
	bool m_eaten;
	int m_id;

public:
	/**
	@brief Constructor
	@param float:m_x float:m_y
	@param int m_id 
	*/
	Item(float, float, int);
	/**
	@brief Destructor
	*/
	~Item();
	/**
	@brief Get position X of item
	@return m_x:positionX
	*/
	float GetX() const;
	/**
	@brief Get position Y of item
	@return m_y:positionY
	*/
	float GetY() const;
	/**
	@brief Get width of item
	@return float width
	*/
	float GetWidth() const;
	/**
	@brief Get height of item
	@return float height
	*/
	float GetHeight() const;
	/**
	@brief Get rectangle (dimension and position) of item
	@return m_rectangle
	*/
	Rectangle getRectangle() const;
	/**
	@brief Set position X of item
	@param float m_x
	*/
	void SetX(float);
	/**
	@brief Set position Y of item
	@param float m_y
	*/
	void SetY(float);
	/**
	@brief Get login of item
	@return int m_id
	*/
	int getId() const;
	/**
	@brief Set if it has been eaten  
	@param true if item are eaten and false if item are not eaten
	*/
	void setEaten(bool);
	/**
	@brief Determines if it has been eaten  
	@return m_eaten
	*/
	bool isEaten() const;
	/**
	@brief Compares 2 item and return true if they are equal
	@return bool 
	*/
	bool operator==(const Item &a);
};

#endif

