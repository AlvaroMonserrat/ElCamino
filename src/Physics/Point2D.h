#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>

class Point2D
{
    public:
        float X, Y;

    public:
        Point2D(float X=0, float Y=0) : X(X), Y(Y){}

        //Addition +
        inline Point2D operator+(const Point2D &p2) const {
            return Point2D(X + p2.X, Y + p2.Y);
        }

        //Addition +=
        inline friend Point2D operator+=(Point2D &p1, const Point2D &p2)
        {
            p1.X += p2.X;
            p1.Y += p2.Y;
            return p1;
        }

        //Subtraction -
        inline Point2D operator-(const Point2D &p2) const {
            return Point2D(X - p2.X, Y - p2.Y);
        }

        //Subtraction -=
        inline friend Point2D operator-=(Point2D &p1, const Point2D &p2)
        {
            p1.X -= p2.X;
            p1.Y -= p2.Y;
            return p1;
        }

        //Multiplication *
        inline Point2D operator*(const float scalar) const {
            return Point2D(X * scalar, Y * scalar);
        }

        void Log(std::string msg= "")
        {
            std::cout << msg << "(X Y) = (" << X << " " << Y << ")" << std::endl;
        }
};

#endif // POINT2D_H
