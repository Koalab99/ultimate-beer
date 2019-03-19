#include <Bloc.h>

float Bloc::GetX() const
{
    return m_x;
}

float Bloc::GetY() const
{
    return m_y;
}

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

float Bloc::GetWidth()
{
    return width;
}

float Bloc::GetHeight()
{
    return heigth;
}

Bloc::Bloc()
{

}

Bloc::Bloc(float, float, float, float)
{

}

Bloc::~Bloc()
{
    
}
