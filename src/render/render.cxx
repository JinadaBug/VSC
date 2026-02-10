// Renderer
#include "render.hxx"

// Render Buffer
#include "buffer/buffer.hxx"

// Render Thread
#include "thread/thread.hxx"

// Render API
#include "sdlgpu/sdlgpu.hxx"

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
}