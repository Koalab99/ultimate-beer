#ifndef POSITION_H
#define POSITION_H

/**
*detailed description Defines what a position on the map is determined by:
*it has a vertical point and a horizontal point
*you can soustract or add positions together
*you can check if it is null and what to do if so 
 */
class Position {
	float m_x;
	float m_y;
public:
	/**
	@brief Get position X of map
	@return m_x
	*/
	float getX() const;
	/**
	@brief Get position Y of map
	@return m_y
	*/
	float getY() const;
	/**
	@brief Set position X of map
	@return m_x
	*/
	void setX(float x);
	/**
	@brief Set position Y of map
	@return m_y
	*/
	void setY(float y);
	/**
	@brief Addition of 2 positions
	@param b
	@return Position result
	*/
	Position operator+(Position &b);
	/**
	@brief Soustraction of 2 positions
	@param b
	@return Position result
	*/
	Position operator-(Position &b);
	/**
	@brief Is Null? Return true if is null.
	@return bool
	*/
	bool isNull() const;
};

#endif
