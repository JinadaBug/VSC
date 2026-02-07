#pragma once

namespace Render::API::DX12
{
    // Init DX12: true on success, false on failure
    bool Init();

    // Quit DX12
    void Quit();

    // Draw Call
    void Draw();
}