// Vulkan
#include "vulkan.hxx"

namespace Render::API::Vulkan
{
    // Module Status
    bool STATUS = false;

    // Init Vulkan
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Success
        STATUS = true;
        return true;
    }

    // Quit Vulkan
    void Quit()
    {
        // Check Module Status
        if (!STATUS) return;

        // Closure
        STATUS = false;
    }

    // Draw Call
    void Draw()
    {
    }
}