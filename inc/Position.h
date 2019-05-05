#ifndef POSITION_H
#define POSITION_H

/*Defines what a position on the map is determined by:
it has a vertical point and a horizontal point
you can soustract or add positions together
you can check if it is null and what to do if so  */
class Position {
private:
	float m_x;
	float m_y;
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
