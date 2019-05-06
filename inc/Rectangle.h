#ifndef RECTANGLE_H
#define RECTANGLE_H

//Defines a rectangle (as the name indicates it)
class Rectangle {
private:
	 /**
	@brief position x left bottom corner of rectangle
	*/
	float m_x;
	/**
	@brief position y left bottom corner of rectangle
	*/
	float m_y;
	/**
	@brief wight of rectangle
	*/
	float m_w;
	/**
	@brief height of rectangle
	*/
	float m_h;

public:
	/**
	@brief Constructor
	@param x float m_x
	@param y float m_y
	@param w float m_w
	@param h float m_h
	*/
	Rectangle(float x = 0, float y = 0, float w = 0, float h = 0);
	/**
	@brief Destructor
	*/
	~Rectangle();
	/**
	@brief Get position X of rectangle
	@return float m_x
	*/
	float getX() const;
	/**
	@brief Get position Y of map
	@return float m_y
	*/
	float getY() const;
	/**
	@brief Get position height of map
	@return float m_h
	*/
	float getH() const;
	/**
	@brief Get position width of map
	@return float m_w
	*/
	float getW() const;
	/**
	@brief Set position X of map
	@param x float m_x
	*/
	void setX(float x);
	/**
	@brief Set position Y of map
	@param y float m_y
	*/
	void setY(float y);
	/**
	@brief Set position width of map
	@param w float m_w
	*/
	void setW(float w);
	/**
	@brief Set position height of map
	@param h float m_h
	*/
	void setH(float h);
	/**
	@brief Compares 2 rectangles and return true if they are equal
	@param r Rectangle
	@return bool true if they are equal
	*/
	bool operator==(const Rectangle &r) const;
};

#endif
