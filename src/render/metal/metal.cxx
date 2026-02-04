#include "metal.hxx"

namespace Render::Metal
{
    // Module Status
    bool STATUS = false;

    // Init Metal
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

    // Quit Metal
    void Quit()
    {
        // Check Module Status
        if (!STATUS) return;

        // Closure
        STATUS = false;
    }
}