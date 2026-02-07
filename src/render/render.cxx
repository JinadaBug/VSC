// Platform
#include "platform/platform.hxx"

// Renderer
#include "render.hxx"

// Render Buffer
#include "buffer/buffer.hxx"

// Render Thread
#include "thread/thread.hxx"

// GPU API
#include "api/dx12/dx12.hxx"
#include "api/metal/metal.hxx"
#include "api/vulkan/vulkan.hxx"

namespace Render
{
    // Module Status
    bool STATUS = false;

    // Init Render
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Init Render API
        if constexpr(Target::DX12)   if (!API::DX12::Init())   return false;
        if constexpr(Target::Metal)  if (!API::Metal::Init())  return false;
        if constexpr(Target::Vulkan) if (!API::Vulkan::Init()) return false;

        // Init Render Buffer
        if (!Buffer::Init()) return false;

        // Init Render Thread
        if (!Thread::Init()) return false;

        // Success
        STATUS = true;
        return true;
    }

    // Quit Render
    void Quit()
    {
        // Check Module Status
        if (!STATUS) return;

        // Quit Render Thread
        Thread::Quit();

        // Quit Render Buffer
        Buffer::Quit();

        // Quit Render API
        if constexpr(Target::DX12)   API::DX12::Quit();
        if constexpr(Target::Metal)  API::Metal::Quit();
        if constexpr(Target::Vulkan) API::Vulkan::Quit();

        // Closure
        STATUS = false;
    }
}