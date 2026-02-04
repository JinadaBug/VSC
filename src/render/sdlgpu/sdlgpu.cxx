// SDL GPU Module
#include <SDL3/SDL_gpu.h>

// Platform
#include "platform/platform.hxx"

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

    // Target API
    inline constexpr bool Target_DX12   = Platform::Windows | Platform::Xbox;
    inline constexpr bool Target_Metal  = Platform::MacOS   | Platform::IOS;
    inline constexpr bool Target_Vulkan = Platform::Linux   | Platform::Android | Platform::BSD;

    // Get Driver Name: DX12, Metal or Vulkan
    consteval const char* Get_Driver_Name()
    {
        if constexpr (Target_DX12)   return "direct3d12";
        if constexpr (Target_Metal)  return "metal";
        if constexpr (Target_Vulkan) return "vulkan";
        return nullptr;
    }

    // Get Shader Format: DXIL, SPIR-V or MSL
    consteval SDL_GPUShaderFormat Get_Shader_Format()
    {
        if constexpr (Target_DX12)   return SDL_GPU_SHADERFORMAT_DXIL;
        if constexpr (Target_Metal)  return SDL_GPU_SHADERFORMAT_MSL;
        if constexpr (Target_Vulkan) return SDL_GPU_SHADERFORMAT_SPIRV;
        return SDL_GPU_SHADERFORMAT_INVALID;
    }

    // Device Configuration
    inline constexpr bool                Debug_Mode    = false;
    inline constexpr const char*         Driver_Name   = Get_Driver_Name();
    inline constexpr SDL_GPUShaderFormat Shader_Format = Get_Shader_Format();

    // Static Format Check
    static_assert(Shader_Format != SDL_GPU_SHADERFORMAT_INVALID, "No valid shader format for this target!");

    // SDLGPU Data
    SDL_GPUDevice*              Device           = nullptr;
    SDL_GPUPresentMode          Present_Mode     = SDL_GPU_PRESENTMODE_VSYNC;
    SDL_GPUSwapchainComposition Swap_Composition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;

    // Init SDLGPU
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Create Device
        Device = SDL_CreateGPUDevice(Shader_Format, Debug_Mode, Driver_Name);
        if (!Device) return false;

        // Claim Window For GPU Device
        if (!SDL_ClaimWindowForGPUDevice(Device, Window::Instance)) return false;

        // Present Mode List
        SDL_GPUPresentMode Present_Mode_List[] =
        {
            SDL_GPU_PRESENTMODE_MAILBOX,
            SDL_GPU_PRESENTMODE_IMMEDIATE,
            SDL_GPU_PRESENTMODE_VSYNC,
        };

        // Result Flag
        bool Result = false;

        // Check Present Mode Support
        for (SDL_GPUPresentMode Mode : Present_Mode_List)
        {
            if (!SDL_WindowSupportsGPUPresentMode(Device, Window::Instance, Mode)) continue;

            Present_Mode = Mode;
            Result = true;
            break;
        }

        // Check If Support Succeeded
        if (!Result) return false;

        // Swapchain Composition List
        SDL_GPUSwapchainComposition Swap_Composition_List[] =
        {
            SDL_GPU_SWAPCHAINCOMPOSITION_HDR_EXTENDED_LINEAR,
            SDL_GPU_SWAPCHAINCOMPOSITION_HDR10_ST2084,
            SDL_GPU_SWAPCHAINCOMPOSITION_SDR_LINEAR,
            SDL_GPU_SWAPCHAINCOMPOSITION_SDR
        };

        // Check Swapchain Composition Support
        for (SDL_GPUSwapchainComposition Composition : Swap_Composition_List)
        {
            if (!SDL_WindowSupportsGPUSwapchainComposition(Device, Window::Instance, Composition)) continue;

            Swap_Composition = Composition;
            Result = true;
            break;
        }

        // Check If Support Succeded
        if (!Result) return false;

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
}