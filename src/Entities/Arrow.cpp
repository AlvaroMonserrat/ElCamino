#include "Arrow.h"
#include "TextureManager.h"

Arrow::Arrow(Properties* props) : Entity(props)
{

}
void Arrow::Draw()
{
    TextureManager::GetInstance()->Draw(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, 1, 1, m_Flip);
}

void Arrow::Update(float dt)
{

}

void Arrow::Clean()
{

}

void Arrow::Update(float x, float y)
{
    m_Transform->X = x + (32 / 2);
    m_Transform->Y = y +(32 / 2) - (13 / 2);
    //, props->Y + (props->Width / 2) - (13/2)
}
