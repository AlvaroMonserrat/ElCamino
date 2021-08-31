#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
#include "Point2D.h"

class Input
{
    public:
        static Input* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
        }

        void Listen();
        bool GetKeyDown(SDL_Scancode key);

        bool GetMousePressLeft();
        Point2D GetPoint();

    private:
        Input();
        static Input* s_Instance;

        void KeyUP();
        void KeyDown();

        void MotionMouse(int x, int y);

        Point2D m_MouseXY;
        const Uint8* m_KeyStates;
        Uint32 m_MouseStates;
};

#endif // INPUT_H
