#include "SpeedBar.h"
#include "Engine.h"

SpeedBar::SpeedBar(float ball_x, float ball_y, int width, int height)
{
    m_IsActived = false;
    m_Width = width;
    m_Height = height;
    m_Speed = 3;

    m_Transform = new Transform2D(ball_x - m_Width * 3, ball_y - (height/3) );

    m_SpeedBox = {ball_x, ball_y, width, 0};
    m_SpeedBox.w -= m_StrokeRect*2;
}

void SpeedBar::Draw()
{
    if(m_IsActived)
    {
        SDL_Rect box = {(int)m_Transform->X, (int)m_Transform->Y, m_Width, m_Height};

        //Borde
        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 35, 35, 35, 255);
        SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &box);
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

        //Bordes
        box.x += m_StrokeRect;
        box.y += m_StrokeRect;
        box.w -= m_StrokeRect*2;
        box.h -= m_StrokeRect*2;

        //Interior
        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, 255);
        SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &box);
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

        //Speed
        m_SpeedBox.x = m_Transform->X + m_StrokeRect;
        m_SpeedBox.y = m_Transform->Y + m_StrokeRect;

        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 255, 255, 255);
        SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &m_SpeedBox);
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &m_SpeedBox);

    }

}

void SpeedBar::Update(float x, float y)
{
    m_Transform->X = x - m_Width * 3;
    m_Transform->Y = y - (m_Height / 3);

    m_SpeedBox.h += m_Speed;

    if(m_SpeedBox.h > m_Height - m_StrokeRect * 3 || m_SpeedBox.h == 0)
        m_Speed = m_Speed * -1;
}

void SpeedBar::Clean()
{
    delete m_Transform;
}
