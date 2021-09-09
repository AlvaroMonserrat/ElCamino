#ifndef BALL_H
#define BALL_H

#include "Entity.h"
#include "BodyObject.h"
#include "SpriteAnimation.h"
#include "Arrow.h"
#include "SpeedBar.h"

#define MOVE_TIME 10.0f;
#define MOVE_FORCE 50.0f;

#define FALL_DOWN_TIME 60.0f;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Ball : public Entity
{
    public:
        Ball(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

    private:
        bool m_IsMoving;
        bool m_IsClicked;

        float m_MoveTime;
        float m_MoveForceX;
        float m_MoveForceY;

        float m_IsFalling;
        float m_FallDownTime;

        BodyObject* m_BodyObject;
        SpriteAnimation* m_Animation;
        Arrow* m_Arrow;
        SpeedBar* m_SpeedBar;

        void MoveBall(float dt);

        float AngleArrow();

};

#endif // BALL_H
