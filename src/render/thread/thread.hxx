#pragma once

namespace Render::Thread
{
    // Init Render Thread: true on success, false on failure
    bool Init();

    // Quit Render Thread
    void Quit();
}