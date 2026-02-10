#pragma once
// #define RELEASE // Uncomment when ready

// SDL Log
#include <SDL3/SDL_log.h>

#if defined(RELEASE)
    #define LOG(message) ((void)0)
#else
    /**
     * @brief Logs a message to the SDL console including file, line, and the last SDL Error
     */
    #define LOG(message) SDL_Log("[%s:%d] ERROR: %s | SDL_Error: %s", __FILE__, __LINE__, message, SDL_GetError())
#endif