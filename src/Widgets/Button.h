#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <map>
#include "Widget.h"
#include "TextureManager.h"
#include "CollisionHandler.h"
#include "Input.h"

enum{
    NORMAL,
    HOOKOVER,
    PRESSED
};


class Button : public Widget
{
    public:
        Button(std::string widgetID, int x, int y, int width, int height, float scaleXY=1);
        virtual void Draw();
        virtual void Update();
        virtual void Clean();
        virtual bool isClicked();

        void Parse(std::string widgetID, std::string source);

    private:
        std::map<int, std::string> m_MapTextureID;
        std::string m_WidgetID;
        std::string m_TextureID;
        bool m_ButtonPressed = false;
        float m_Scale=1;
};

#endif // BUTTON_H
