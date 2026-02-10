#pragma once

// Render Module
namespace Render
{
    // Init Render: true on success, false on failure
    bool Init();

    // Quit Render
    void Quit();

    // Peek Call: true on success, false on failure
    bool Peek();

    // Copy Call: true on success, false on failure
    bool Copy();
}