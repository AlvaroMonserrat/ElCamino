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
}

void Ball::Draw()
{

    TextureManager::GetInstance()->Draw(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height);

    SDL_Rect box = {(int)m_Transform->X + m_Width / 2, (int)m_Transform->Y + m_Height / 2, 2, 2};

    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 255);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

}

void Ball::Update(float dt)
{
    //MoveBall(dt);
    m_IsMoving = false;

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP))
    {
        m_IsMoving = true;
        m_BodyObject->ApplyForceY(-10);
        m_BodyObject->Update(dt);
        m_Transform->Y += m_BodyObject->Position().Y;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN))
    {
        m_IsMoving = true;
        m_BodyObject->ApplyForceY(10);
        m_BodyObject->Update(dt);
        m_Transform->Y += m_BodyObject->Position().Y;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT))
    {
        m_IsMoving = true;
        m_BodyObject->ApplyForceX(-10);
        m_BodyObject->Update(dt);
        m_Transform->X += m_BodyObject->Position().X;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_IsMoving = true;
        m_BodyObject->ApplyForceX(10);
        m_BodyObject->Update(dt);
        m_Transform->X += m_BodyObject->Position().X;
    }

    if(m_IsMoving == true)
    {
        //Revisar si estoy sobre superficie o no.
        SDL_Rect box = {(int)m_Transform->X + m_Width / 2, (int)m_Transform->Y + m_Height / 2, 2, 2};

        if(CollisionHandler::GetInstance()->MapCollision(box))
        {
           std::cout << "Colisión" << std::endl;
        }
        else
        {
            std::cout << "No Colisión" << std::endl;
            SDL_Rect startZone = StateGame::GetInstance()->getStartZone();
            m_Transform->X = startZone.x;
            m_Transform->Y = startZone.y;
        }

    }
}

void Ball::Clean()
{
    //Clear Point2D, Transform
    delete m_Origin;
    delete m_Transform;
    delete m_BodyObject;

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
