#include "Ball.h"
#include "TextureManager.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "StateGame.h"
#include "Engine.h"


Ball::Ball(Properties* props) : Entity(props)
{
    m_IsMoving = false;
    m_BodyObject = new BodyObject();
    m_BodyObject->SetMass(3);
    m_BodyObject->ApplyFriction(Vector2D(0,0));

    m_MoveTime = MOVE_TIME;
    m_MoveForceX = MOVE_FORCE;
    m_MoveForceY = MOVE_FORCE;

    m_IsFalling = false;

    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(m_TextureID, 0, 1, 50);

    Properties* propsArrow = new Properties("arrow", props->X + (props->Width / 2), props->Y + (props->Width / 2) - (13/2), 48, 13);

    m_Arrow = new Arrow(propsArrow);

    m_SpeedBar = new SpeedBar(props->X, props->Y, 24, 96);

}

void Ball::Draw()
{
    m_SpeedBar->Draw();
    m_Arrow->Draw();
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, 1, 1, m_Flip);
}

void Ball::Update(float dt)
{

    m_IsClicked = false;

    m_Arrow->SetVisivility(false);
    m_SpeedBar->SetVisivility(false);

    if(Input::GetInstance()->GetMousePressLeft())
    {
        //Actualizar angulo
        m_IsClicked = true;
        m_SpeedBar->SetVisivility(true);
        m_Arrow->SetVisivility(true);
        m_Arrow->UpdateAngle(m_Transform->X, m_Transform->Y, m_Width, m_Height);
    }

    if(Input::GetInstance()->IsButtonLeftReleased())
    {
        Input::GetInstance()->ResetButtonLeftReleased();
        //std::cout << "X:"<< m_Arrow->ProjectionX()*500 << " Y:" << m_Arrow->ProjectionY()*500<< std::endl;
        m_IsMoving = true;
        m_MoveForceX = m_SpeedBar->GetForceSpeed();
        m_MoveForceY = m_SpeedBar->GetForceSpeed();
        //std::cout << m_SpeedBar->GetForceSpeed() << std::endl;
    }

    if(m_IsMoving)
        MoveBall(dt);


    if(m_IsMoving == true)
    {
        //Revisar si estoy sobre superficie o no.
        SDL_Rect box = {(int)m_Transform->X + (m_Width / 2) - 2, (int)m_Transform->Y + (m_Height / 2) - 2, 4, 4};
        if(!CollisionHandler::GetInstance()->MapCollision(box))
        {
           m_IsFalling = true;
           //m_IsMoving = false;
           //m_MoveTime = 0;
           m_Animation->SetProps("ball_fall_down", 0, 6, 133);
           std::cout << "No Colisión" << std::endl;
        }
    }

    if(m_IsFalling && m_FallDownTime > 0)
    {
        //std::cout << m_FallDownTime << std::endl;
        m_FallDownTime -= dt;

    }

    if(m_FallDownTime <= 0)
    {
        m_Animation->SetProps(m_TextureID, 0, 1, 50);
        m_IsFalling = false;
        m_FallDownTime = FALL_DOWN_TIME;
        SDL_Rect startZone = StateGame::GetInstance()->getStartZone();
        m_Transform->X = startZone.x;
        m_Transform->Y = startZone.y;
    }

    m_Arrow->Update(m_Transform->X, m_Transform->Y);
    m_SpeedBar->Update(m_Transform->X, m_Transform->Y);
    m_Animation->Update(dt);

}

void Ball::Clean()
{
    //Clear Point2D, Transform
    delete m_Origin;
    delete m_Transform;
    delete m_BodyObject;
    //delete m_Arrow;
}

void Ball::MoveBall(float dt)
{

    if(m_IsMoving && m_MoveTime > 0)
    {
        m_MoveTime -= dt;

        m_BodyObject->ApplyForceY(m_Arrow->ProjectionY() * m_MoveForceX);
        m_BodyObject->ApplyForceX(m_Arrow->ProjectionX() * m_MoveForceY);

        m_BodyObject->Update(dt);
        m_Transform->Y += m_BodyObject->Position().Y;
        m_Transform->X += m_BodyObject->Position().X;

    }
    else
    {
        m_IsMoving = false;
        m_MoveTime = MOVE_TIME;
    }

}
