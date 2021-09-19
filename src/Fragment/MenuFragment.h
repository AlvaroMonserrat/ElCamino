#ifndef MENUFRAGMENT_H
#define MENUFRAGMENT_H

#include "Fragment.h"
#include "SDL2/SDL.h"
#include "Engine.h"
#include "Input.h"
#include "Button.h"
#include "Widget.h"

enum{
    START,
    OPTIONS,
    EXIT
};

class MenuFragment : public Fragment
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
