#ifndef RECTANGLE_H
#define RECTANGLE_H

//Defines a rectangle (as the name indicates it)
class Rectangle {
private:
	float m_x;
	float m_y;
	float m_w;
	float m_h;

public:
	Rectangle(float x = 0, float y = 0, float w = 0, float h = 0);
	~Rectangle();
	/**
	@brief Get position X of rectangle
	@return m_x
	*/
	float getX() const;
	/**
	@brief Get position Y of map
	@return m_y
	*/
	float getY() const;
	/**
	@brief Get position height of map
	@return m_h
	*/
	float getH() const;
	/**
	@brief Get position width of map
	@return m_w
	*/
	float getW() const;
	/**
	@brief Set position X of map
	@param m_x
	*/
	void setX(float x);
	/**
	@brief Set position Y of map
	@param m_y
	*/
	void setY(float y);
	/**
	@brief Set position width of map
	@return m_w
	*/
	void setW(float w);
	/**
	@brief Set position height of map
	@return m_h
	*/
	void setH(float h);
	/**
	@brief Compares 2 rectangles and return true if they are equal
	@return bool true if they are equal
	*/
	bool operator==(const Rectangle &r) const;
};

#endif
