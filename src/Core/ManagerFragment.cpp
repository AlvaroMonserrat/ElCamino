#include "ManagerFragment.h"

ManagerFragment::ManagerFragment(Fragment* fragment)
{
    m_Fragments.push_back(fragment);
    m_CurrentFragment = fragment;
}

void ManagerFragment::AddFragment(Fragment* fragment)
{
    m_Fragments.push_back(fragment);
}

Fragment* ManagerFragment::GetCurrent()
{
    return m_CurrentFragment;
}

void ManagerFragment::Init()
{
    m_CurrentFragment->Init();
}

void ManagerFragment::Update(float dt)
{
    m_CurrentFragment->Update(dt);
}

void ManagerFragment::Draw()
{
    m_CurrentFragment->Render();
}

void ManagerFragment::Clean()
{
    //Delete all fragment
    for(int i = 0; i < m_Fragments.size(); i++)
    {
        m_Fragments[i]->Exit();
    }
}

