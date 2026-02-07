// DX12
#include "dx12.hxx"

namespace Render::API::DX12
{
    // Module Status
    bool STATUS = false;

    // Init DX12
    bool Init()
    {
        // Check Module Status
        if (STATUS) return true;

        // Success
        STATUS = true;
        return true;
    }

    // Quit DX12
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