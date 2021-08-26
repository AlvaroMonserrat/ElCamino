#include "GameFragment.h"
#include "Engine.h"
#include "MapParser.h"
#include "Ball.h"

bool GameFragment::Init()
{
    //Obtener Render principal
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    m_LevelMap = MapParser::GetInstance()->GetMaps("map");

    Properties* propsBall = new Properties("ball_idle", 100, 200, 32, 32);
    //GameObject* ball = ObjectFactory::GetInstance()->CreateObject("BALL", propsBall);
    Ball* ball = new Ball(propsBall);
    m_GameObjects.push_back(ball);
}

bool GameFragment::Exit()
{
    //Limpiar objectos de del juego
    for(unsigned int i=0; i!=m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Clean();
    }

}

void GameFragment::Update(float dt)
{
    m_LevelMap->Update();
    //Actualizar objetos del juego
    for(unsigned int i=0; i!=m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Update(dt);
    }

}

void GameFragment::Render()
{
    m_LevelMap->Render();
    //Rendizar objetos
    for(unsigned int i=0; i!=m_GameObjects.size(); i++)
    {

        m_GameObjects[i]->Draw();

    }
}
