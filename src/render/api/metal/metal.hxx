#pragma once

namespace Render::API::Metal
{
    // Init Metal: true on success, false on failure
    bool Init();

    // Quit Metal
    void Quit();

    // Draw Call
    void Draw();
}