// Atomic
#include <atomic>

// Standard Thread
#include <thread>

// Render Thread
#include "thread.hxx"

// Render API
#include "render/sdlgpu/sdlgpu.hxx"

namespace Render::Thread
{
    // Module Status
    bool STATUS = false;

    // Render Thread Data
    std::thread      Thread;
    std::atomic_bool Running = false;

    // Init Render Thread
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Init The Thread
        if (!Thread.joinable())
        {
            Running.store(true, std::memory_order_relaxed);
            Thread = std::thread(Render::SDLGPU::Draw);
        }

        // Success
        STATUS = true;
        return true;
    }

    // Quit Render Thread
    void Quit()
    {
        // Check Module Status
        if (!STATUS) return;

        // Quit The Thread
        if (Thread.joinable())
        {
            Running.store(false, std::memory_order_relaxed);
            Thread.join();
        }

        // Closure
        STATUS = false;
    }
}