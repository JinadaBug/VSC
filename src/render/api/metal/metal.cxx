// Metal
#include "metal.hxx"

namespace Render::API::Metal
{
    // Module Status
    bool STATUS = false;

    // Init Metal
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Success
        STATUS = true;
        return true;
    }

    // Quit Metal
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