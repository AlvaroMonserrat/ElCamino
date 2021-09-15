#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"

class Button : Widget
{
    public:
        Button();
        virtual void Draw();
        virtual void Update();
        virtual void Clean();
        virtual bool isClicked();

    private:
};

#endif // BUTTON_H
