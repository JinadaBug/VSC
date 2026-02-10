// Logger
#include "logger/logger.hxx"

// SDL Video Module
#include <SDL3/SDL_video.h>

// Window
#include "window.hxx"

namespace Window
{
    // Module Status
    bool STATUS = false;

    // Window Flags
    inline constexpr SDL_WindowFlags Flags = SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;

    // Window Data
    Uint32            Width      = 0;
    Uint32            Height     = 0;
    const char*       Title      = "Game Engine Window";
    SDL_DisplayID     Display_ID = 0;
    SDL_DisplayMode*  Best_Mode  = nullptr;
    SDL_DisplayMode** Mode_List  = nullptr;
    int               Mode_Count = 0;
    SDL_Window*       Instance   = nullptr;

    // Init Window
    bool Window::Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Get Display ID
        Display_ID = SDL_GetPrimaryDisplay();
        if (!Display_ID)
        {
            LOG("Get Primary Display Failure");
            return false;
        }

        // Get Mode List
        Mode_List = SDL_GetFullscreenDisplayModes(Display_ID, &Mode_Count);
        if (!Mode_List)
        {
            LOG("Get Fullscreen Display Modes Failure");
            return false;
        }

        // Pick Best Mode
        Best_Mode = (Mode_List && Mode_Count > 0) ? Mode_List[0] : nullptr;
        if (!Best_Mode)
        {
            LOG("No Best Mode Exists");
            return false;
        }

        // Cache Resolution
        Width = Best_Mode->w;
        Height = Best_Mode->h;

        // Create Window Instance
        Instance = SDL_CreateWindow(Title, Width, Height, Flags);
        if (!Instance)
        {
            LOG("Window Creation Failure");
            return false;
        }

        // Set Window Fullscreen Mode
        if (!SDL_SetWindowFullscreenMode(Instance, Best_Mode))
        {
            LOG("Set Window Mode Failure");
            return false;
        }

        // Set Window Fulscreen
        if (!SDL_SetWindowFullscreen(Instance, true))
        {
            LOG("Set Window Fullscreen Failure");
            return false;
        }

        // Success
        STATUS = true;
        return true;
    }

    // Quit Window
    void Window::Quit()
    {
        // Check Module Status
        if (!STATUS) return;

        // Destroy Window
        SDL_DestroyWindow(Instance);
        Instance = nullptr;

        // Free Resources
        SDL_free(Mode_List);
        Best_Mode  = nullptr;
        Mode_List  = nullptr;
        Mode_Count = 0;
        Display_ID = 0;

        // Closure
        STATUS = false;
    }

    // Sync Window
    bool Window::Sync()
    {
        // Check Module Status
        if (!STATUS) return false;

        // Sync Window
        if (!SDL_SyncWindow(Instance)) return false;

        // Success
        return true;
    }

    // Show Window
    bool Window::Show()
    {
        // Check Module Status
        if (!STATUS) return false;

        // Show Window
        if (!SDL_ShowWindow(Instance))
        {
            LOG("Show Window Failure");
            return false;
        }

        // Success
        return true;
    }

    // Hide Window
    bool Window::Hide()
    {
        // Check Window Status
        if (!STATUS) return false;

        // Hide Window
        if (!SDL_HideWindow(Instance))
        {
            LOG("Hide Window Failure");
            return false;
        }

        // Success
        return true;
    }
}