// Atomic
#include <atomic>

// Standard Thread
#include <thread>

// Render Thread
#include "thread.hxx"

// Render API
#include "render/sdlgpu/sdlgpu.hxx"

// Render Thread Module
namespace Render::Thread
{
    // Module Status
    bool STATUS = false;

    // Render Thread Data
    std::thread      Thread;
    std::atomic_bool Success = false;
    std::atomic_bool Running = false;

    // Render Worker
    void Work()
    {
        while (Running.load(std::memory_order_acquire)) Success.store(Render::SDLGPU::Draw(), std::memory_order_release);
    }

    // Init Render Thread
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Init The Thread
        if (!Thread.joinable())
        {
            Running.store(true, std::memory_order_release);
            Thread = std::thread(Work);
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
            Running.store(false, std::memory_order_release);
            Thread.join();
        }

        // Closure
        STATUS = false;
    }
}