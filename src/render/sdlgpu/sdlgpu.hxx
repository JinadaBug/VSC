#pragma once

// SDL GPU API
namespace Render::SDLGPU
{
    // Init SDLGPU: true on success, false on failure
    bool Init();

    // Quit SDLGPU
    void Quit();

    // Copy Call: true on success, false on failure
    bool Copy();

    // Draw Call: true on success, false on failure
    bool Draw();
}