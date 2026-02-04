#pragma once

namespace Render::SDLGPU
{
    // Init SDLGPU: true on success, false on failure
    bool Init();

    // Quit SDLGPU
    void Quit();
}