// Platform
#include "platform/platform.hxx"

// Renderer
#include "render.hxx"

// GPU API
#include "dx12/dx12.hxx"
#include "metal/metal.hxx"
#include "vulkan/vulkan.hxx"
#include "sdlgpu/sdlgpu.hxx"

namespace Render
{
    // Module Status
    bool STATUS = false;

    // Target API
    inline constexpr bool Target_DX12   = Platform::Windows | Platform::Xbox;
    inline constexpr bool Target_Metal  = Platform::MacOS   | Platform::IOS;
    inline constexpr bool Target_Vulkan = Platform::Linux   | Platform::Android | Platform::BSD;

    // Native API Status
    bool NATIVE = true;

    // Init Render
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // On DX12 Platforms
        if constexpr(Target_DX12)
        {
            if (!DX12::Init())
            {
                DX12::Quit();
                SDLGPU::Init();
                NATIVE = false;
            }
        }

        // On Metal Platforms
        if constexpr(Target_Metal)
        {
            if (!Metal::Init())
            {
                Metal::Quit();
                SDLGPU::Init();
                NATIVE = false;
            }
        }

        // On Vulkan Platforms
        if constexpr(Target_Vulkan)
        {
            if (!Vulkan::Init())
            {
                Vulkan::Quit();
                SDLGPU::Init();
                NATIVE = false;
            }
        }

        // Success
        STATUS = true;
        return true;
    }

    // Quit Render
    void Quit()
    {
        // Check Module Status
        if (!STATUS) return;

        // Quit Fallback API
        if (!NATIVE) SDLGPU::Quit();

        // Quit DX12
        if constexpr(Target_DX12) DX12::Quit();

        // Quit Metal
        if constexpr(Target_Metal) Metal::Quit();

        // Quit Vulkan
        if constexpr(Target_Vulkan) Vulkan::Quit();

        // Closure
        STATUS = false;
    }
}