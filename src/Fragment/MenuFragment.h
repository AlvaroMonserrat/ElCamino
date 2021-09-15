#ifndef MENUFRAGMENT_H
#define MENUFRAGMENT_H

#include "Fragment.h"

enum{
    START,
    OPTIONS,
    EXIT
};

class MenuGame : public Fragment
{
    public:
        virtual bool Init();
        virtual bool Exit();
        virtual void Update(float dt);
        virtual void Render();

    private:
        //std::vector<Widget*> m_Widgets;

};

#endif // MENUFRAGMENT_H
