// SDL Init Module
#include <SDL3/SDL_init.h>

// System
#include "system.hxx"

// System Module
namespace System
{
    // Module Status
    bool STATUS = false;

    // Init Flags
    inline constexpr SDL_InitFlags Flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC;

    // Init System
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Init Subsystems
        if (!SDL_InitSubSystem(Flags)) return false;

        // Success
        STATUS = true;
        return true;
    }

    // Quit System
    void Quit()
    {
        // Check Module Status
        if (!STATUS) return;

        // Quit Subsystems
        SDL_QuitSubSystem(Flags);

        // Closure
        STATUS = false;
    }
}