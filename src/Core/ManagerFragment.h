#ifndef MANAGERFRAGMENT_H
#define MANAGERFRAGMENT_H

#include <vector>
#include "Fragment.h"

class ManagerFragment
{
    public:
        ManagerFragment(){};
        ManagerFragment(Fragment* fragment);

        void AddFragment(Fragment* fragment);
        //void nextFragment();
        //void prevFragment();
        void Init();
        void Update(float dt);
        void Draw();
        void Clean();
        Fragment* GetCurrent();
        void SetFragment(int TYPE);

    private:
        std::vector<Fragment*> m_Fragments;
        Fragment* m_CurrentFragment;
        //Fragment* prevFragment;
        //Fragment* nextFragment;
};

#endif // MANAGERFRAGMENT_H
