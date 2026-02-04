#pragma once

namespace Render::Vulkan
{
    // Init Vulkan: true on success, false on failure
    bool Init();

    // Quit Vulkan
    void Quit();
}