#pragma once

// SDL GPU API
namespace Render::SDLGPU
{
    // Init SDLGPU: true on success, false on failure
    bool Init();

    // Quit SDLGPU
    void Quit();

    // Draw Call
    void Draw();
}