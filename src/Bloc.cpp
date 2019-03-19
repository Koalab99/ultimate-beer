#include <Bloc.h>
#include <Position.h>

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
  return height;
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

Position Bloc::isInside(Position &p) {
  Position ret;
  if(m_x <= p.getX() && m_x + width >= p.getX()) {
    ret.setX((p.getX() - m_x > m_x + width - p.getX()) ? p.getX() - (m_x + width) : p.getX() - m_x);
    if(m_y <= p.getY() && m_y + height >= p.getY()) {
      ret.setY((p.getY() - m_y > m_y + height - p.getY()) ? p.getY() - (m_y + height) : p.getY() - m_y);
      return ret;
    }
  }
  ret.setX(0);
  return ret;
}
