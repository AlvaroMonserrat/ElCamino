#ifndef BODYOBJECT_H
#define BODYOBJECT_H

#include "Vector2D.h"
#include <iostream>
#define UNI_MASS 1.0f

#define FORWARD 1
#define BACKWARD -1

#define UPWARD -1
#define DOWNWARD 1

class BodyObject
{
    public:
        BodyObject()
        {
            m_Mass = UNI_MASS;
        }

        //Setter Mass
        inline void SetMass(float mass){ m_Mass = mass; }

        // Force
        inline void ApplyForce(Vector2D F){ m_Force = F; }
        inline void ApplyForceX(float Fx){ m_Force.X = Fx;}
        inline void ApplyForceY(float Fy){ m_Force.Y = Fy;}
        inline void UnSetForce(){ m_Force = Vector2D(0, 0);}

        //Friction
        inline void ApplyFriction(Vector2D Fr){ m_Friction = Fr; }
        inline void UnSetFriction(){ m_Friction = Vector2D(0, 0); }

        //Getters
        inline float GetMass(){ return m_Mass; }
        inline Vector2D Position(){ return m_Position; }
        inline Vector2D Velocity(){ return m_Velocity; }
        inline Vector2D Accelaration(){ return m_Acceleration; }
        inline Vector2D Force(){ return m_Force; };


        //Update
        void Update(float dt)
        {
            //F + Fr = m * a
            m_Acceleration.X = ((m_Force.X + m_Friction.X) / m_Mass);
            m_Acceleration.Y = (m_Force.Y + m_Friction.Y) / m_Mass;
            m_Velocity = m_Acceleration;
            m_Position = m_Velocity;
            //std::cout << m_Velocity.X << std::endl;


        }


    private:
        float m_Mass;

        Vector2D m_Force;
        Vector2D m_Friction;

        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Acceleration;

};

#endif // BODYOBJECT_H
