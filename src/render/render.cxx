// Atomic
#include <atomic>

// Renderer
#include "render.hxx"

// Render Buffer
#include "buffer/buffer.hxx"

// Render Thread
#include "thread/thread.hxx"

// Render API
#include "sdlgpu/sdlgpu.hxx"

namespace Render::Thread
{
    extern std::atomic_bool Success;
}

// Render Module
namespace Render
{
    // Module Status
    bool STATUS = false;

    // Init Render
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Init SDL GPU
        if (!SDLGPU::Init()) return false;

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

        // Quit SDL GPU
        SDLGPU::Quit();

        // Closure
        STATUS = false;
    }

    // Peek Call
    bool Peek()
    {
        // Check Module Status
        if (!STATUS) return false;

        // Check Render Thread Success
        return Render::Thread::Success.load(std::memory_order_acquire);
    }

    // Copy Call
    bool Copy()
    {
        // Check Module Status
        if (!STATUS) return false;

        // Copy Swapchain Texture
        return Render::SDLGPU::Copy();
    }
}