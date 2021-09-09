#ifndef ARROW_H
#define ARROW_H

#include "Entity.h"
#include "Input.h"
#include <math.h>       /* atan */

#define PI 3.14159265

class Arrow : public Entity
{
    public:
        Arrow(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

        inline void SetVisivility(bool visivility){m_IsActived = visivility;};
        double ProjectionX();
        double ProjectionY();

        void Update(float x, float y);

        void UpdateAngle(float objX, float objY, int objWidth, int objHeight);

    private:
        bool m_IsActived;
        double m_Angle = 0;
        double m_dX;
        double m_dY;
        SDL_Point* m_Center;
        double AngleArrow(float objX, float objY, int objWidth, int objHeight);
};

#endif // ARROW_H
