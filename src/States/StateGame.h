#ifndef STATEGAME_H
#define STATEGAME_H

#include "SDL2/SDL.h"

class StateGame
{
    public:
        static StateGame* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new StateGame();
        }

        inline SDL_Rect getStartZone(){ return startZone;};

        void setStartZone(int x, int y, int w, int h);

    private:
        StateGame();
        static StateGame* s_Instance;

        //Punto de inicio de la Bola
        SDL_Rect startZone;

        //Punto de llegada.
        SDL_Rect endZone;
};

#endif // STATEGAME_H
