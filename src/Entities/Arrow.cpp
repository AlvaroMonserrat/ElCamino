#include "Arrow.h"
#include "TextureManager.h"

Arrow::Arrow(Properties* props) : Entity(props)
{
    m_Center = new SDL_Point;
    m_Center->x = 0;
    m_Center->y = props->Height / 2;
    m_IsActived = false;
}
void Arrow::Draw()
{
    //std::cout << "x:"<< m_Center->x << " y:"<< m_Center->y << std::endl;
    if(m_IsActived)
        TextureManager::GetInstance()->DrawRotation(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, 1, 1, m_Angle, m_Center, m_Flip);
}

void Arrow::Update(float dt)
{

}

void Arrow::Clean()
{
    delete m_Center;
}

void Arrow::Update(float x, float y)
{
    m_Transform->X = x + (32 / 2);
    m_Transform->Y = y +(32 / 2) - (13 / 2);
    //, props->Y + (props->Width / 2) - (13/2)
}

void Arrow::UpdateAngle(float objX, float objY, int objWidth, int objHeight)
{

    //Calculo del centro del objeto
    int objCenterX = objX + (objWidth / 2);
    int objCenterY = objY + (objHeight / 2);

    m_Angle = AngleArrow(objX, objY, objWidth, objHeight);

}

double Arrow::AngleArrow(float objX, float objY, int objWidth, int objHeight)
{
    double angleDegree = 0;

    Point2D mouseXY = Input::GetInstance()->GetPoint();

    //Calculo del centro del objeto
    double objCenterX = objX + (objWidth / 2);
    double objCenterY = objY + (objHeight / 2);

    //Distancia entre el mouse y el objeto
    m_dX = mouseXY.X - objCenterX;
    m_dY = objCenterY - mouseXY.Y;

    angleDegree = atan2(m_dY, m_dX) * 180 / PI;

    if(m_dY < 0)
    {
        angleDegree += 360;
    }

    return angleDegree*-1;
}


double Arrow::ProjectionX()
{
    return cos(m_Angle * PI / 180.0);
}

double Arrow::ProjectionY()
{
    return sin(m_Angle * PI / 180.0);
}

