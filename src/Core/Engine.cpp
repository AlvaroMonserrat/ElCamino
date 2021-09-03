#include "Engine.h"
#include "Input.h"
#include "Timer.h"
#include "TextureManager.h"
#include "GameFragment.h"
#include "MapParser.h"

Engine* Engine::s_Instance = nullptr;

Engine::Engine()
{
    printf("El motor se ha iniciado\n");
}


bool Engine::Init()
{
    //Bandera de inicialización
    m_IsRunning = true;

    if( SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Error al iniciar SDL libraries: %s", SDL_GetError());
        m_IsRunning = false;
    }
    else
    {
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        //Crear la ventana
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }
        m_Window = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);

        if( m_Window == nullptr)
        {
            SDL_Log("La ventana no pudo ser creada: %s", SDL_GetError());
            m_IsRunning = false;
        }
        else
        {
            //Obtener Renderer
            m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if(m_Renderer == nullptr)
            {
                SDL_Log("El Renderer no pudo ser creado: %s", SDL_GetError());
                m_IsRunning = false;
            }
        }
    }

    //Cargar Texturas
    m_IsRunning = LoadTextures("assets/texture.tml");

    //Cargar Mapas
    m_IsRunning = MapParser::GetInstance()->Load();

    m_ManagerFragment = ManagerFragment(new GameFragment());
    //m_ManagerFragment.AddFragment(new GameFragment());
    m_ManagerFragment.Init();


    return m_IsRunning;
}

bool Engine::Clean()
{

    //Limpiar Gestor de Texturas
    TextureManager::GetInstance()->Clean();

    //Limpiar Input
    Input::GetInstance()->Clean();

    //Limpiar Mapa
    MapParser::GetInstance()->Clean();

    //Limpiar Fragments
    m_ManagerFragment.Clean();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    m_Renderer = nullptr;
    m_Window = nullptr;

    IMG_Quit();
    SDL_Quit();

    return true;
}

void Engine::Quit()
{
    m_IsRunning = false;
}

void Engine::Update()
{
    //Actualizar tiempo
    float dt = Timer::GetInstance()->GetDeltaTime();

    m_ManagerFragment.Update(dt);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 32, 154, 227, 255);
    SDL_RenderClear(m_Renderer);

    m_ManagerFragment.Draw();

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::LoadTextures(std::string texture_file){
    return TextureManager::GetInstance()->ParseTexture(texture_file);
}
