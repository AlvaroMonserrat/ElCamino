#include "MenuFragment.h"
#include "PackManager.h"

bool MenuFragment::Init()
{
    //Obtener Render principal
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    //Agregar Boton
    PackManager::GetInstance()->AddWidget(new Button("btn_start", 20, 150, 300, 200, 1), MENU);
    PackManager::GetInstance()->AddWidget(new Button("btn_options", 20, 300, 300, 200, 1), MENU);
    PackManager::GetInstance()->AddWidget(new Button("btn_exit", 20, 450, 300, 200, 1), MENU);


    return true;
}

bool MenuFragment::Exit()
{
    return true;
}

void MenuFragment::Update(float dt)
{
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_M))
    {
        Engine::GetInstance()->ChangeFragment(GAME);
        SDL_Delay(200);
    }

    if(PackManager::GetInstance()->GetButton(MENU, START)->isClicked())
    {
        SDL_Delay(200);
        Engine::GetInstance()->ChangeFragment(GAME);

    }

    if(PackManager::GetInstance()->GetButton(MENU, EXIT)->isClicked())
    {
        Engine::GetInstance()->ExitGame();
        SDL_Delay(200);
    }

    PackManager::GetInstance()->UpdateAllWidget(MENU);

}

void MenuFragment::Render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 69, 90, 100, 255);
    SDL_RenderClear(m_Ctxt);

    PackManager::GetInstance()->DrawAllWidget(MENU);
}
