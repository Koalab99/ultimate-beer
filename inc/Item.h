#ifndef ITEM_H
#define ITEM_H

#include <Rectangle.h>
#include <iostream>

class Item {
private:
	
	float m_x;
    float m_y;
	bool m_eaten;
	int m_id;
	Rectangle m_rectangle;
	
public:
	Item();
	Item(float, float);
	Item(int id);
	~Item();
	
	float GetX() const;
    float GetY() const;
    
    void SetX(float);
    void SetY(float);
	
	int getId() const;
	void SetEaten(bool);
	bool isEaten() const;
};

#endif

