#include <Item.h>

Item::Item(float x, float y, int id): m_x(x), m_y(y), m_rectangle(m_x,m_y,1.5,2), m_eaten(false), m_id(id) {
}

Item::~Item() {

}

int Item::getId() const {
	return m_id;
}

float Item::GetWidth() const
{
	return m_rectangle.getW();
}

float Item::GetHeight() const
{
	return m_rectangle.getH();
}

float Item::GetX() const
{
	return m_rectangle.getX();
}

float Item::GetY() const
{
	return m_rectangle.getY();
}

Rectangle Item::getRectangle() const {
	return m_rectangle;
}


void Item::SetX(float x)
{
	if(x >= 0) {
		m_rectangle.setX(x);
	}
}

void Item::SetY(float y)
{
	if(y >= 0) {
		m_rectangle.setY(y);
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

bool Item::operator==(const Item &a) {
	return m_rectangle == a.getRectangle() && m_id == a.getId();
}
