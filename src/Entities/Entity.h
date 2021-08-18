#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"
#include <string>

class Entity : public GameObject
{
    public:
        Entity(Properties* props): GameObject(props) {}

        virtual void Draw()=0;
        virtual void Update(float dt)=0;
        virtual void Clean()=0;
};

#endif // ENTITY_H
