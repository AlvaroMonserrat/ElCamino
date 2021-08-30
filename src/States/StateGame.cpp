#include "StateGame.h"


StateGame* StateGame::s_Instance = nullptr;

StateGame::StateGame()
{
    //ctor
}
void StateGame::setStartZone(int x, int y, int w, int h)
{
    startZone.x = x;
    startZone.y = y;
    startZone.w = w;
    startZone.h = w;
}
