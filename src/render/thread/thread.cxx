// Atomic
#include <atomic>

// Standard Thread
#include <thread>

// Platform
#include "platform/platform.hxx"

// Render Thread
#include "thread.hxx"

// Render API
#include "render/api/dx12/dx12.hxx"
#include "render/api/metal/metal.hxx"
#include "render/api/vulkan/vulkan.hxx"

namespace Render::Thread
{
    // Module Status
    bool STATUS = false;

    // Render Thread Data
    std::thread      Thread;
    std::atomic_bool Running   = false;

    // Render Work
    void Work()
    {
        if constexpr (Target::DX12)   while (Running.load(std::memory_order_relaxed)) API::DX12::Draw();
        if constexpr (Target::Metal)  while (Running.load(std::memory_order_relaxed)) API::Metal::Draw();
        if constexpr (Target::Vulkan) while (Running.load(std::memory_order_relaxed)) API::Vulkan::Draw();
    }

    // Init Render Thread
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Init The Thread
        if (!Thread.joinable())
        {
            Running.store(true, std::memory_order_relaxed);
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
            Running.store(false, std::memory_order_relaxed);
            Thread.join();
        }

        // Closure
        STATUS = false;
    }
}