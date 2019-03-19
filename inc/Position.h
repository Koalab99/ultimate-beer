#ifndef POSITION_H
#define POSITION_H

class Position {
private:
	float m_x;
	int m_y;
public:
	float getX() const;
	float getY() const;

	void setX(float x);
	void setY(float y);

	Position operator+(Position &b);
	Position operator-(Position &b);

	bool isNull() const;
};

#endif
