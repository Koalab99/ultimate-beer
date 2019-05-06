#ifndef ITEM_H
#define ITEM_H

#include <Rectangle.h>
#include <iostream>

/**
*detailed description Defines the general position of an item, it's general shape (width and height)
*Determines if it has been eaten by the player, and what happens if so*/
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
	/**
	@brief identifiant of item 
	*/
	int m_id;

public:
	/**
	@brief Constructor
	@param x float m_x 
	@param y float m_y
	@param id int m_id 
	*/
	Item(float x, float y, int id);
	/**
	@brief Destructor
	*/
	~Item();
	/**
	@brief Get position X of item
	@return float m_x positionX
	*/
	float GetX() const;
	/**
	@brief Get position Y of item
	@return float m_y positionY
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
	@return Rectangle m_rectangle
	*/
	Rectangle getRectangle() const;
	/**
	@brief Set position X of item
	@param x float m_x
	*/
	void SetX(float x);
	/**
	@brief Set position Y of item
	@param y float m_y
	*/
	void SetY(float y);
	/**
	@brief Get login of item
	@return int m_id
	*/
	int getId() const;
	/**
	@brief Set if it has been eaten  
	@param eat bool true if item are eaten and false if item are not eaten
	*/
	void setEaten(bool eat);
	/**
	@brief Determines if it has been eaten  
	@return bool m_eaten
	*/
	bool isEaten() const;
	/**
	@brief Compares 2 item and return true if they are equal
	@param a Item
	@return bool 
	*/
	bool operator==(const Item &a);
};

#endif

