#include <Bloc.h>
#include <Position.h>
#include <iostream>

//returns the vertical position of the bloc
float Bloc::GetX() const
{
	return m_x;
}

//returns the horizontal position of the bloc
float Bloc::GetY() const
{
	return m_y;
}

//sets the bloc position
void Bloc::SetX(float x)
{
	if(x >= 0) {
		m_x = x;
	}
}

void Bloc::SetY(float y)
{
	if(y >= 0) {
		m_y = y;
	}
}

//return the Width of the bloc
float Bloc::GetWidth() const
{
	return m_width;
}

//return the Height of the bloc
float Bloc::GetHeight() const
{
	return m_height;
}

//return the type of the bloc
int Bloc::GetType()
{
	return m_type;
}

Bloc::Bloc()
{

}

//sets the bloc on its width, height and vertical & horizontal positions
Bloc::Bloc(float w, float h, float x, float y){
	m_width = w;
	m_height = h;
	m_x = x;
	m_y = y;
}

//destructor
Bloc::~Bloc()
{

}

//Calculates where the bloc is
Position Bloc::isInside(Position &p) {
	Position ret;
	if(m_x <= p.getX() && m_x + m_width >= p.getX()) {
		ret.setX((p.getX() - m_x > m_x + m_width - p.getX()) ? p.getX() - (m_x + m_width) : p.getX() - m_x);
		if(m_y <= p.getY() && m_y + m_height >= p.getY()) {
			ret.setY((p.getY() - m_y > m_y + m_height - p.getY()) ? p.getY() - (m_y + m_height) : p.getY() - m_y);
			return ret;
		}
	}
	ret.setX(0);
	return ret;
}

bool Bloc::operator==(const Bloc &other) {
	return (other.GetX() == m_x && other.GetY() == m_y && other.GetWidth() == m_width && other.GetHeight() == m_height);
}

bool Bloc::operator!=(const Bloc &other) {
	return !(*this == other);
}
