#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private:
	float m_x;
	float m_y;
	float m_w;
	float m_h;

public:
	Rectangle(float x = 0, float y = 0, float w = 0, float h = 0);
	~Rectangle();


	float getX() const;
	float getY() const;
	float getH() const;
	float getW() const;

	void setX(float x);
	void setY(float y);
	void setW(float w);
	void setH(float h);
};

#endif
