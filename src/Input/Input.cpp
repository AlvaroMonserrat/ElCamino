#include "Input.h"
#include "Engine.h"

Input* Input::s_Instance = nullptr;

Input::Input()
{
    //ctor
}
void Input::Listen()
{
        SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                Engine::GetInstance()->Quit();
                break;

            case SDL_KEYDOWN:
                //KeyDown();
                break;

            case SDL_KEYUP:
                //KeyUP();
                break;

            case SDL_MOUSEMOTION:
                MotionMouse(event.motion.x, event.motion.y);
                break;


        }
    }
}

bool Input::GetMousePressLeft()
{
    SDL_PumpEvents();
    m_MouseStates = SDL_GetMouseState(nullptr, nullptr);
    return SDL_BUTTON_LEFT && m_MouseStates;
}


void Input::MotionMouse(int x, int y)
{
    m_MouseXY = {x, y};

}

Point2D Input::GetPoint()
{
    return m_MouseXY;
}
