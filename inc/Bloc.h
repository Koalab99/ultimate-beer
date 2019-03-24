#ifndef Bloc_h
#define Bloc_h

#include <Position.h>

class Bloc {
    private:
    float width;
    float height; 
    float m_x;
    float m_y;

    public:
    float GetX() const;
    float GetY() const;
    
    void SetX(float);
    void SetY(float);

    float GetWidth() const;
    float GetHeight() const;

    Position isInside(Position &p);

    Bloc();
    Bloc(float, float, float, float);
    ~Bloc();

    bool operator==(const Bloc &other);
    bool operator!=(const Bloc &other);
};

#endif
