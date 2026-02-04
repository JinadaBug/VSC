--- My Personal Repository ---

I mostly try to create a game engine and need to keep track of the stuff for it...

Engine development started back in August 2024, and currently I am focused on implementing these features in it:
- Rollback
- Modern 3D Pipeline (Bindless Textures, Dynamic Rendering)
- Japanese style ECS architecture and efficiency
- Modular approach
- No inheritance at all
- No heap at all
- No includes in my headers - only in implementation files
- CXX/HXX (Because it's stylish!)

Feel free to comment on my atrocity!

Libraries used:
- Vulkan 1.4
- SDL3
- Metal (Eventually it will be there)
- DX12 (specifically I will use D3DX12.h helper to set that, need to target DX12.2)
- ASIO standalone (For async networking)
- CGLTF (For cooking assets)
- CGLM (For vector math and matrix math)
- Lua for scripting

Tools that I will use for game development:
- Blender (3D Work)
- Gimp (2D work)
- Audacity (Audio work, maybe also Reaper or Cakewalk, only if professional mixing will be necessary)

Shader languages that will be used (Possibly via SDL_shadercross or native shader compilers):
- HLSL for authoring
- DXIL for DX12 binaries
- SPIR-V for Vulkan binaries
- MSL for Metal binaries (If I get there...)

Target platforms:
- Windows PC
- Linux PC
- macOS
- FreeBSD
- Xbox consoles
- PS consoles
- Android Mobile
- iOS Mobile

Why I am making this? Because I despise the workflow in other game engines, they're overbloated for no reason
Also I deepen my knowledge in systems programming as well, and build making

Build System Used:
- Custom Build System. I use Lua to create the list of all CXX files to compile and feed it to a native compiler
This allows me to control precisely the build with one single CTRL+SHIFT+B
I did leverage features of Visual Studio Code and its tasks to create this

Language Used:
- C++ 2020, it is the most fresh and most widely supported standard...
I'd love to move to the newest one but I need coverage on other platforms