#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include "Vector2D.h"

class Transform2D
{
public:
    float X, Y;

public:
    Transform2D(float x=0, float y=0) : X(x), Y(y) {}

    void Log(std::string mag = "")
    {
        std::cout << mag << "(X Y) = (" << X << " " << Y << ")" << std::endl;
    }

public:
    inline void TranslateX(float x)
    {
        X += x;
    }
    inline void TranslateY(float y)
    {
        Y += y;
    }
    inline void Translate(Vector2D v)
    {
        X+= v.X;
        Y+=v.Y;
    }
};

#endif // TRANSFORM2D_H
