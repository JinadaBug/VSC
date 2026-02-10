// SDL GPU Module
#include <SDL3/SDL_gpu.h>

// SDLGPU
#include "sdlgpu.hxx"

// Window Variables
namespace Window
{
    extern SDL_Window* Instance;
}

namespace Render::SDLGPU
{
    // Module Status
    bool STATUS = false;

    // SDLGPU Data
    SDL_GPUDevice*              Device           = nullptr;
    SDL_GPUPresentMode          Present_Mode     = SDL_GPU_PRESENTMODE_MAILBOX;
    SDL_GPUSwapchainComposition Swap_Composition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR_LINEAR;

    // Shader Format Flags
    inline constexpr SDL_GPUShaderFormat Flags = SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL;

    // Init SDLGPU
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Create Device
        Device = SDL_CreateGPUDevice(Flags, false, nullptr);
        if (!Device) return false;

        // Set One Frame In Flight
        if (!SDL_SetGPUAllowedFramesInFlight(Device, 1)) return false;

        // Claim Window For GPU Device
        if (!SDL_ClaimWindowForGPUDevice(Device, Window::Instance)) return false;

        // Check For Present Mode Support
        if (!SDL_WindowSupportsGPUPresentMode(Device, Window::Instance, Present_Mode))
        {
            Present_Mode = SDL_GPU_PRESENTMODE_VSYNC;
        }

        // Check Swapchain Composition Support
        if (!SDL_WindowSupportsGPUSwapchainComposition(Device, Window::Instance, Swap_Composition))
        {
            Swap_Composition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;
        }

        // Apply Parameters To Swapchain
        if (!SDL_SetGPUSwapchainParameters(Device, Window::Instance, Swap_Composition, Present_Mode)) return false;

        // Success
        STATUS = true;
        return true;
    }

    // Quit SDLGPU
    void Quit()
    {
        // Check Module Status
        if (!STATUS) return;

        // Release Window From GPU Device
        SDL_ReleaseWindowFromGPUDevice(Device, Window::Instance);

        // Destroy Device
        SDL_DestroyGPUDevice(Device);

        // Closure
        STATUS = false;
    }

    // Draw Call
    void Draw()
    {}
}