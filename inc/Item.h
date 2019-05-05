#ifndef ITEM_H
#define ITEM_H

#include <Rectangle.h>
#include <iostream>

class Item {
private:
	float m_x;
	float m_y;
	Rectangle m_rectangle;
	bool m_eaten;
	int m_id;

public:
	Item(float, float, int);
	~Item();

	float GetX() const;
	float GetY() const;
	float GetWidth() const;
	float GetHeight() const;
	Rectangle getRectangle() const;

	void SetX(float);
	void SetY(float);

	int getId() const;
	void setEaten(bool);
	bool isEaten() const;

	bool operator==(const Item &a);
};

#endif

