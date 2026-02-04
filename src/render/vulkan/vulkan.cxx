#include "vulkan.hxx"

namespace Render::Vulkan
{
    // Module Status
    bool STATUS = false;

    // Init Vulkan
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // FUTURE TODO: DO STUFF!
        return false;

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
}