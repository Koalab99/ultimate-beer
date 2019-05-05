#ifndef Bloc_h
#define Bloc_h

#include <Position.h>

//Defines the plateforms width, height and postion as blocs
class Bloc {
private:
	float m_width;
	float m_height; 
	float m_x;
	float m_y;
	int m_type;

public:
	float GetX() const;
	float GetY() const;

	void SetX(float);
	void SetY(float);

	float GetWidth() const;
	float GetHeight() const;

	int GetType();

	Position isInside(Position &p);

	Bloc();
	Bloc(float w, float h, float x, float y);
	~Bloc();

	bool operator==(const Bloc &other);
	bool operator!=(const Bloc &other);
};

#endif
