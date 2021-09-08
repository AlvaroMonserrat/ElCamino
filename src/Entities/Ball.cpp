#include "Ball.h"
#include "TextureManager.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "StateGame.h"
#include "Engine.h"
#include <math.h>       /* atan */

#define PI 3.14159265

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

}

void Ball::Draw()
{

    //TextureManager::GetInstance()->Draw(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height);
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, 1, 1, m_Flip);

    m_Arrow->Draw();

    //SDL_Rect box = {(int)m_Transform->X + (m_Width / 2) - 2, (int)m_Transform->Y + (m_Height / 2) - 2, 4, 4};

    //SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 255);
    //SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

}

void Ball::Update(float dt)
{
    //MoveBall(dt);
    m_IsMoving = false;

    if(Input::GetInstance()->GetMousePressLeft())
    {
        //OBTENER ANGULO
        std::cout << "Angulo: " << AngleArrow() << std::endl;

    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP) && !m_IsFalling)
    {
        m_IsMoving = true;
        m_BodyObject->ApplyForceY(-20);
        m_BodyObject->Update(dt);
        m_Transform->Y += m_BodyObject->Position().Y;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN) && !m_IsFalling)
    {
        m_IsMoving = true;
        m_BodyObject->ApplyForceY(20);
        m_BodyObject->Update(dt);
        m_Transform->Y += m_BodyObject->Position().Y;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT) && !m_IsFalling)
    {
        m_IsMoving = true;
        m_BodyObject->ApplyForceX(-20);
        m_BodyObject->Update(dt);
        m_Transform->X += m_BodyObject->Position().X;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT) && !m_IsFalling)
    {
        m_IsMoving = true;
        m_BodyObject->ApplyForceX(20);
        m_BodyObject->Update(dt);
        m_Transform->X += m_BodyObject->Position().X;
    }

    if(m_IsMoving == true)
    {
        //Revisar si estoy sobre superficie o no.
        SDL_Rect box = {(int)m_Transform->X + (m_Width / 2) - 2, (int)m_Transform->Y + (m_Height / 2) - 2, 4, 4};
        if(!CollisionHandler::GetInstance()->MapCollision(box))
        {
           m_IsFalling = true;
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
    m_Animation->Update(dt);

}

void Ball::Clean()
{
    //Clear Point2D, Transform
    delete m_Origin;
    delete m_Transform;
    delete m_BodyObject;
    delete m_Arrow;

}

/*Mover con Click Mouse*/
void Ball::MoveBall(float dt)
{
    Point2D mouseXY = Input::GetInstance()->GetPoint();
    SDL_Rect box = {(int)m_Transform->X, (int)m_Transform->Y, m_Width, m_Height};


    //If the mouse is over the button
    //Click en la bola y comienza a moverse
    if(CollisionHandler::GetInstance()->CheckPointInsideBox(mouseXY, box))
    {
        if(Input::GetInstance()->GetMousePressLeft() && !m_IsMoving)
        {
            std::cout << "Click" << std::endl;
            m_IsMoving = true;
            m_MoveForceX = MOVE_FORCE;
        }
    }

    if( (m_Transform->Y + m_Height) >= SCREEN_HEIGHT && m_MoveForceY > 0)
    {
        m_MoveForceY = m_MoveForceY * -1;
    }

    if((m_Transform->Y) < 0 && m_MoveForceY < 0)
    {
        m_MoveForceY = m_MoveForceY * -1;
    }

    if( (m_Transform->X + m_Width) > SCREEN_WIDTH && m_MoveForceX > 0)
    {
        m_MoveForceX = m_MoveForceX * -1;
    }

    if((m_Transform->X) < 0  && m_MoveForceX < 0)
    {
        m_MoveForceX = m_MoveForceX * -1;
    }

    if(m_IsMoving && m_MoveTime > 0)
    {
        m_MoveTime -= dt;

        m_BodyObject->ApplyForceX(m_MoveForceX);
        m_BodyObject->ApplyForceY(m_MoveForceY);

        // move on X axis
        m_BodyObject->Update(dt);
        m_Transform->X += m_BodyObject->Position().X;

        // move on Y axis
        m_BodyObject->Update(dt);
        m_Transform->Y += m_BodyObject->Position().Y;
    }
    else
    {
        m_IsMoving = false;
        m_MoveTime = MOVE_TIME;
    }


}

float Ball::AngleArrow()
{
    float angleDegree = 0;

    Point2D mouseXY = Input::GetInstance()->GetPoint();

    float ballCenterX = m_Transform->X + (m_Width / 2);
    float ballCenterY = m_Transform->Y + (m_Height / 2);

    float dx = std::abs(ballCenterX - mouseXY.X);
    float dy = std::abs(ballCenterY - mouseXY.Y);


    angleDegree = atan(dy/dx) * 180 / PI;

    return angleDegree;
}
