#ifndef GAMEFRAGMENT_H
#define GAMEFRAGMENT_H

#include <vector>
#include "Fragment.h"
#include "GameObject.h"
#include "GameMap.h"

class GameFragment : public Fragment
{
    public:
        virtual bool Init();
        virtual bool Exit();
        virtual void Update(float dt);
        virtual void Render();

    private:
        GameMap* m_LevelMap;
        std::vector<GameObject*> m_GameObjects;
        int m_time;
};

#endif // GAMEFRAGMENT_H
