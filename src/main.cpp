#include "Engine.h"
#include "Timer.h"
#include <iostream>

int main()
{
    Engine* game_engine = Engine::GetInstance();
    Timer* game_timer = Timer::GetInstance();

    game_engine->Init();

    while(game_engine->isRunning())
    {
        game_engine->Events();
        game_engine->Update();
        game_engine->Render();

        game_timer->Tick();
    }

    game_engine->Clean();
    return 0;
}
