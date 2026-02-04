#pragma once
#include <SDL3/SDL_platform_defines.h>

namespace Platform
{
    inline constexpr bool Windows =
    #if defined(SDL_PLATFORM_WIN32)
        true;
    #else
        false;
    #endif

    inline constexpr bool BSD = 
    #if defined(SDL_PLATFORM_FREEBSD)
        true;
    #else
        false;
    #endif

    inline constexpr bool Linux =
    #if defined(SDL_PLATFORM_LINUX)
        true;
    #else
        false;
    #endif

    inline constexpr bool MacOS =
    #if defined(SDL_PLATFORM_MACOS)
        true;
    #else
        false;
    #endif

    inline constexpr bool IOS =
    #if defined(SDL_PLATFORM_IOS)
        true;
    #else
        false;
    #endif

    inline constexpr bool Android =
    #if defined(SDL_PLATFORM_ANDROID)
        true;
    #else
        false;
    #endif

    inline constexpr bool Xbox =
    #if defined(SDL_PLATFORM_XBOXSERIES)
        true;
    #else
        false;
    #endif

    inline constexpr bool PS5 = 
    #if defined(SDL_PLATFORM_PS5)
        true;
    #else
        false;
    #endif
}