#include "GameFragment.h"
#include "Engine.h"
#include "MapParser.h"
#include "Ball.h"
#include "StateGame.h"

bool GameFragment::Init()
{
    //Obtener Render principal
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    m_LevelMap = MapParser::GetInstance()->GetMaps("map");

    SDL_Rect startZone = StateGame::GetInstance()->getStartZone();

    Properties* propsBall = new Properties("ball_idle", startZone.x, startZone.y, 32, 32);
    //GameObject* ball = ObjectFactory::GetInstance()->CreateObject("BALL", propsBall);

    Ball* ball = new Ball(propsBall);

    m_GameObjects.push_back(ball);

    std::cout << "INIT GAME: esperar 2 segundos" << std::endl;
    m_time = 0;

    return true;
}

bool GameFragment::Exit()
{
    //Limpiar objectos de del juego
    for(unsigned int i=0; i!=m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Clean();
    }

    //Limpiar Mapa
    return true;

}

void GameFragment::Update(float dt)
{
    //ESPERAR

    m_LevelMap->Update();
    //Actualizar objetos del juego
    for(unsigned int i=0; i!=m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Update(dt);
    }


}

void GameFragment::Render()
{

    SDL_SetRenderDrawColor(m_Ctxt, 180, 140, 180, 255);
    SDL_RenderClear(m_Ctxt);
    m_LevelMap->Render();
    //Rendizar objetos
    for(unsigned int i=0; i!=m_GameObjects.size(); i++)
    {

        m_GameObjects[i]->Draw();

    }


}
