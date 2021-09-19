#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ManagerFragment.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

enum{MENU, GAME};


class Engine
{
    public:

        static Engine* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
        }

        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline bool isRunning(){ return m_IsRunning; }
        inline void ExitGame(){ m_IsRunning = false; }

        inline SDL_Renderer* GetRenderer(){ return m_Renderer; }

        void ChangeFragment(int fragment);



    private:
        Engine();
        bool LoadTextures(std::string texture_file);

        static Engine* s_Instance;
        bool m_IsRunning;

        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        SDL_Surface* m_SurfaceScreen;

        ManagerFragment m_ManagerFragment;

};

#endif // ENGINE_H
