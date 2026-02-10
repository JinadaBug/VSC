// Logger
#include "logger/logger.hxx"

// Atomic
#include <atomic>

// SDL GPU Module
#include <SDL3/SDL_gpu.h>

// SDL GPU
#include "sdlgpu.hxx"

// Window Variables
namespace Window
{
    extern Uint32      Width;
    extern Uint32      Height;
    extern SDL_Window* Instance;
}

// SDL GPU API
namespace Render::SDLGPU
{
    // Module Status
    bool STATUS = false;

    // SDL GPU Configuration
    SDL_GPUDevice*              Device           = nullptr;
    SDL_GPUPresentMode          Present_Mode     = SDL_GPU_PRESENTMODE_MAILBOX;
    SDL_GPUSwapchainComposition Swap_Composition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR_LINEAR;

    // Ready Flag
    std::atomic_bool Ready = false;

    // Render Textures
    std::atomic<SDL_GPUTexture*> Render_Target;
    std::atomic<SDL_GPUTexture*> Depth_Stencil;

    // Shader Format Flags
    inline constexpr SDL_GPUShaderFormat Flags = SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL;

    // Init SDLGPU
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Create Device
        Device = SDL_CreateGPUDevice(Flags, false, nullptr);
        if (!Device)
        {
            LOG("Create GPU Device Failure");
            return false;
        }

        // Set One Frame In Flight
        if (!SDL_SetGPUAllowedFramesInFlight(Device, 1))
        {
            LOG("Set GPU Frames In Flight Failure");
            return false;
        }

        // Claim Window For GPU Device
        if (!SDL_ClaimWindowForGPUDevice(Device, Window::Instance))
        {
            LOG("Claim Window For GPU Device Failure");
            return false;
        }

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
        if (!SDL_SetGPUSwapchainParameters(Device, Window::Instance, Swap_Composition, Present_Mode))
        {
            LOG("Set GPU Swapchain Parameters Failure");
            return false;
        }

        // Create Render Target Info
        SDL_GPUTextureCreateInfo Render_Target_Info = {};
        Render_Target_Info.type                 = SDL_GPU_TEXTURETYPE_2D;
        Render_Target_Info.format               = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
        Render_Target_Info.usage                = SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER;
        Render_Target_Info.width                = Window::Width;
        Render_Target_Info.height               = Window::Height;
        Render_Target_Info.layer_count_or_depth = 1;
        Render_Target_Info.num_levels           = 1;

        // Create Render Target
        Render_Target.store(SDL_CreateGPUTexture(Device, &Render_Target_Info), std::memory_order_release);
        if (!Render_Target.load(std::memory_order_release))
        {
            LOG("Render Target View Creation Failed");
            return false;
        }

        // Create Depth Stencil Info
        SDL_GPUTextureCreateInfo Depth_Stencil_Info = {};
        Depth_Stencil_Info.type                 = SDL_GPU_TEXTURETYPE_2D;
        Depth_Stencil_Info.format               = SDL_GPU_TEXTUREFORMAT_D32_FLOAT;
        Depth_Stencil_Info.usage                = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET;
        Depth_Stencil_Info.width                = Window::Width;
        Depth_Stencil_Info.height               = Window::Height;
        Depth_Stencil_Info.layer_count_or_depth = 1;
        Depth_Stencil_Info.num_levels           = 1;

        // Create Depth Stencil
        Depth_Stencil.store(SDL_CreateGPUTexture(Device, &Depth_Stencil_Info), std::memory_order_release);
        if (!Depth_Stencil.load(std::memory_order_release))
        {
            LOG("Depth Stencil View Creation Failed");
            return false;
        }

        // Success
        STATUS = true;
        return true;
    }

    // Quit SDLGPU
    void Quit()
    {
        // Check Module Status
        if (!STATUS) return;

        // Clear Data
        Ready.store(false, std::memory_order_release);

        // Release Window From GPU Device
        SDL_ReleaseWindowFromGPUDevice(Device, Window::Instance);

        // Destroy Device
        SDL_DestroyGPUDevice(Device);

        // Closure
        STATUS = false;
    }

    // Copy Call
    bool Copy()
    {
        // Check Module Status
        if (!STATUS) return false;

        // If Texture Is Not Ready - Skip
        if (!Ready.load(std::memory_order_acquire)) return true;

        // Acquire Copy Command Buffer
        SDL_GPUCommandBuffer* Copy_Buffer = SDL_AcquireGPUCommandBuffer(Device);
        if (!Copy_Buffer)
        {
            LOG("Acquire Copy Command Buffer Failure");
            return false;
        }

        // Acquire Swapchain
        Uint32          Swap_Width   = 0;
        Uint32          Swap_Height  = 0;
        SDL_GPUTexture* Swap_Texture = nullptr;
        if (!SDL_AcquireGPUSwapchainTexture(Copy_Buffer, Window::Instance, &Swap_Texture, &Swap_Width, &Swap_Height))
        {
            LOG("Acquire Swapchain Texture Failure");
            return false;
        }

        // Copy Swapchain
        if (Swap_Texture)
        {
            SDL_GPUBlitRegion Internal = {};
            Internal.texture           = Render_Target.load(std::memory_order_acquire);
            Internal.w                 = Window::Width;
            Internal.h                 = Window::Height;

            SDL_GPUBlitRegion External = {};
            External.texture           = Swap_Texture;
            External.w                 = Swap_Width;
            External.h                 = Swap_Height;

            SDL_GPUBlitInfo Copy_Info = {};
            Copy_Info.source          = Internal;
            Copy_Info.destination     = External;
            Copy_Info.filter          = SDL_GPU_FILTER_LINEAR;

            // Copy Swapchain Texture
            SDL_BlitGPUTexture(Copy_Buffer, &Copy_Info);
        }

        // Submit Draw Command Buffer
        if (!SDL_SubmitGPUCommandBuffer(Copy_Buffer))
        {
            LOG("Submit Copy Command Buffer Failure");
            return false;
        }

        // Success
        return true;
    }

    // Draw Call
    bool Draw()
    {
        // Check Module Status
        if (!STATUS) return false;

        // Set Busy Flag - Textures Are Not Ready
        Ready.store(false, std::memory_order_release);

        // Acquire Draw Command Buffer
        SDL_GPUCommandBuffer* Draw_Buffer = SDL_AcquireGPUCommandBuffer(Device);
        if (!Draw_Buffer)
        {
            LOG("Acquire Draw Command Buffer Failure");
            return false;
        }

        // Render Target Attachment
        SDL_GPUColorTargetInfo Color_Target_Info = {};
        Color_Target_Info.texture     = Render_Target.load(std::memory_order_acquire);
        Color_Target_Info.clear_color = { 0.0f, 0.0f, 0.0f, 1.0f };
        Color_Target_Info.load_op     = SDL_GPU_LOADOP_CLEAR;
        Color_Target_Info.store_op    = SDL_GPU_STOREOP_STORE;

        // Depth Stencil Attachment
        SDL_GPUDepthStencilTargetInfo Depth_Target_Info = {};
        Depth_Target_Info.texture          = Depth_Stencil.load(std::memory_order_acquire);
        Depth_Target_Info.clear_depth      = 1.0f;
        Depth_Target_Info.clear_stencil    = 0;
        Depth_Target_Info.load_op          = SDL_GPU_LOADOP_CLEAR;
        Depth_Target_Info.store_op         = SDL_GPU_STOREOP_DONT_CARE;
        Depth_Target_Info.stencil_load_op  = SDL_GPU_LOADOP_DONT_CARE;
        Depth_Target_Info.stencil_store_op = SDL_GPU_STOREOP_DONT_CARE;
        Depth_Target_Info.cycle            = false;

        // Begin Render Pass
        SDL_GPURenderPass* Pass = SDL_BeginGPURenderPass(Draw_Buffer, &Color_Target_Info, 1, &Depth_Target_Info);

        // DO STUFF

        // End Render Pass
        SDL_EndGPURenderPass(Pass);

        // Submit Draw Command Buffer
        if (!SDL_SubmitGPUCommandBuffer(Draw_Buffer))
        {
            LOG("Submit Draw Command Buffer Failure");
            return false;
        }

        // Set Busy Flag - Textures Are Not Ready
        Ready.store(true, std::memory_order_release);

        // Success
        return true;
    }
}