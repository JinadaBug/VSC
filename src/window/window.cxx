// SDL Video Module
#include <SDL3/SDL_video.h>

// Platform
#include "platform/platform.hxx"

// Window
#include "window.hxx"

namespace Window
{
    // Module Status
    bool STATUS = false;

    // Window Flags
    inline constexpr SDL_WindowFlags Window_Metal  = Target::Metal  ? SDL_WINDOW_METAL  : 0;
    inline constexpr SDL_WindowFlags Window_Vulkan = Target::Vulkan ? SDL_WINDOW_VULKAN : 0;
    inline constexpr SDL_WindowFlags Flags = 
        SDL_WINDOW_HIDDEN |
        SDL_WINDOW_HIGH_PIXEL_DENSITY |
        Window_Metal |
        Window_Vulkan;

    // Window Data
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
        if (!Display_ID) return false;

        // Get Mode List
        Mode_List = SDL_GetFullscreenDisplayModes(Display_ID, &Mode_Count);
        if (!Mode_List) return false;

        // Pick Best Mode
        Best_Mode = (Mode_List && Mode_Count > 0) ? Mode_List[0] : nullptr;
        if (!Best_Mode) return false;

        // Create Window Instance
        Instance = SDL_CreateWindow(Title, Best_Mode->w, Best_Mode->h, Flags);
        if (!Instance) return false;

        // Set Window Fullscreen Mode
        if (!SDL_SetWindowFullscreenMode(Instance, Best_Mode)) return false;

        // Set Window Fulscreen
        if (!SDL_SetWindowFullscreen(Instance, true)) return false;

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
        return SDL_SyncWindow(Instance) ? true : false;
    }

    // Show Window
    bool Window::Show()
    {
        // Check Module Status
        if (!STATUS) return false;

        // Show Window
        return SDL_ShowWindow(Instance) ? true : false;
    }

    // Hide Window
    bool Window::Hide()
    {
        // Check Window Status
        if (!STATUS) return false;

        // Hide Window
        return SDL_HideWindow(Instance) ? true : false;
    }
}