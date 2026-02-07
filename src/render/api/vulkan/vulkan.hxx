#pragma once

namespace Render::API::Vulkan
{
    // Init Vulkan: true on success, false on failure
    bool Init();

    // Quit Vulkan
    void Quit();

    // Draw Call
    void Draw();
}