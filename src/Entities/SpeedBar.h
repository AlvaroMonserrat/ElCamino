#ifndef SPEEDBAR_H
#define SPEEDBAR_H

#include "Transform2D.h"
#include <SDL2/SDL.h>

class SpeedBar
{
    public:
        SpeedBar(float x, float y, int width, int height);
        void Draw();
        void Update(float x, float y);
        void Clean();

        inline void SetVisivility(bool visivility){m_IsActived = visivility;};
        inline int GetForceSpeed(){return (m_SpeedBox.h - 93)*1.5*-1;};

    private:

        Transform2D* m_Transform;
        SDL_Rect m_SpeedBox;

        bool m_IsActived;
        int m_Width;
        int m_Height;
        int m_Speed;
        int m_StrokeRect = 3;
};

#endif // SPEEDBAR_H
