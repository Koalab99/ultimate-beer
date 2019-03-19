#ifndef Bloc_h
#define Bloc_h

class Bloc {
    private:
    float width;
    float heigth; 
    float m_x;
    float m_y;

    public:
    float GetX() const;
    float GetY() const;
    
    void SetX(float);
    void SetY(float);

    float GetWidth();
    float GetHeight();

    Bloc();
    Bloc(float, float, float, float);
    ~Bloc();
};

#endif