// Logger
#include "logger/logger.hxx"

// SDL Callbacks API
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include "program.hxx"

// Launch Program
SDL_AppResult SDL_AppInit(void**, int, char**)
{
    if (!System::Init()) return SDL_APP_FAILURE;
    if (!Window::Init()) return SDL_APP_FAILURE;
    if (!Render::Init()) return SDL_APP_FAILURE;

    if (!Window::Sync()) return SDL_APP_FAILURE;
    if (!Window::Show()) return SDL_APP_FAILURE;
    return SDL_APP_CONTINUE;
}

// Dispatch Events
SDL_AppResult SDL_AppEvent(void*, SDL_Event *event)
{
    // Desktop Quit Event
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

    // Mobile Lifetime
    // if (event->type == SDL_EVENT_TERMINATING) return SDL_APP_SUCCESS;
    // if (event->type == SDL_EVENT_WILL_ENTER_BACKGROUND)
    // if (event->type == SDL_EVENT_DID_ENTER_BACKGROUND)
    // if (event->type == SDL_EVENT_WILL_ENTER_FOREGROUND)
    // if (event->type == SDL_EVENT_DID_ENTER_FOREGROUND)

    // Dispatch Events

    return SDL_APP_CONTINUE;
}

// Iterate Logic
SDL_AppResult SDL_AppIterate(void*)
{
    if (!Render::Peek())
    {
        LOG("Program Failure: Draw Call Level");
        return SDL_APP_FAILURE;
    }

    if (!Render::Copy())
    {
        LOG("Program Failure: Swap Copy Level");
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

// Clean Resources
void SDL_AppQuit(void*, SDL_AppResult result)
{
    if (result == SDL_APP_FAILURE) LOG("Program Failure");

    Window::Hide();

    Render::Quit();
    Window::Quit();
    System::Quit();
}