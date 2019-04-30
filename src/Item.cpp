#include <Item.h>

Item::Item(float x, float y, int id): m_x(x), m_y(y), m_rectangle(m_x,m_y,1,1), m_eaten(false), m_id(id) {
}

Item::~Item() {

}

int Item::getId() const {
	return m_id;
}

float Item::GetWidth() const
{
	return m_x;
}

float Item::GetHeight() const
{
	return m_y;
}

float Item::GetX() const
{
	return m_x;
}

float Item::GetY() const
{
	return m_y;
}


void Item::SetX(float x)
{
	if(x >= 0) {
		m_x = x;
	}
}

void Item::SetY(float y)
{
	if(y >= 0) {
		m_y = y;
	}
}

void Item::setEaten(bool eaten)
{
	m_eaten = eaten;
}

bool Item::isEaten() const
{
	return m_eaten;
}
