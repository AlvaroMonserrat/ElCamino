#ifndef FRAGMENT_H
#define FRAGMENT_H

#include <SDL2/SDL.h>

class Fragment
{
    public:
        virtual bool Init() = 0;
        virtual bool Exit() = 0;
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
    protected:
        SDL_Renderer* m_Ctxt;
};

#endif // FRAGMENT_H
