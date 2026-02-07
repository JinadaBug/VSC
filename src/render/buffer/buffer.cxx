// Render Buffer
#include "buffer.hxx"

namespace Render::Buffer
{
    // Module Status
    bool STATUS = false;

    // Init Render Buffer
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Success
        STATUS = true;
        return true;
    }

    // Quit Render Buffer
    void Quit()
    {
        // Check Module Status
        if (!STATUS) return;

        // Closure
        STATUS = false;
    }
}