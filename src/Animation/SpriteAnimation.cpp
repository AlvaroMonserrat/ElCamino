#include "SpriteAnimation.h"
#include "TextureManager.h"
#include <iostream>

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat)
{
    m_startTime = 0;
}

void SpriteAnimation::Update(float dt)
{
    //std::cout << SDL_GetTicks() - m_startTime  << std::endl;
    //Clock aumentar
    if(!isEnded())
    {
        m_CurrentFrame = ( (SDL_GetTicks() - m_startTime) / m_Speed) % m_FrameCount;
        //std::cout << m_CurrentFrame << std::endl;
    }

    if(m_CurrentFrame == (m_FrameCount -1))
    {
        m_IsEnded = true;
    }


}

void SpriteAnimation::Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip)
{
    //std::cout << "ID: "<< m_TextureID << "m_Current: "<< m_CurrentFrame << std::endl;
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_CurrentFrame, flip);
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed)
{
    m_Speed = speed;
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_IsEnded = false;

    //Reset Clock
    //std::cout <<  "Reset" << std::endl;
    m_startTime = SDL_GetTicks();
}
