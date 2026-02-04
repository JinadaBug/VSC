#pragma once

namespace Window
{
    // Init Window: true on success, false on failure
    bool Init();

    // Quit Window
    void Quit();

    // Sync Window: true on success, false on failure
    bool Sync();

    // Show Window: true on success, false on failure
    bool Show();

    // Hide Window: true on success, false on failure
    bool Hide();
}