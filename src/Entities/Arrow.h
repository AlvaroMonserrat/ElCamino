#ifndef ARROW_H
#define ARROW_H

#include "Entity.h"

class Arrow : public Entity
{
    public:
        Arrow(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

        void Update(float x, float y);

    private:
        bool m_IsActived;
};

#endif // ARROW_H
