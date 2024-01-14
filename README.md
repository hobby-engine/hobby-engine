# Hobby Engine

A game engine made to be simple. Primarily a 2D engine, though 3D is not off the table as a feature.
<br>
I want this engine to be like Love2D, in the sense that your game uses the paradigm you want, and is structured how you want.
But I want it to be like Godot, in the sense that it actually has features.
<br>
The name comes from the species of bird known as Hobbies, and the fact that this is, in fact, a hobby project.
<br>
Anyway, please, stare at the logo:

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="assets/hobby-dark.png">
  <source media="(prefers-color-scheme: light)" srcset="assets/hobby-light.png">
  <img alt="Hobby Engine logo" width="256px" height="256px">
</picture>

Hopefully you've stared at the logo for a good 20 or 30 seconds now. Now, if you want to see the other variations of the logo, because you love staring at good logos so much, check out [the assets directory](assets/).

## Building
This should hopefully work. If not, then make a PR to fix my silliness.
```bash
$ mkdir build ; cd build
$ cmake ..
$ make
```

## Features
- Rendering
- Input
- Events

### Planned Features
- 2D audio
- Render textures
- Virtual filesystem, save system
- Physics engine
- Tilemaps
- Pathfinding
- Input System
- OpenGL Rendering
- Shaders
- UI system

### Low-Priority Planned Features (Probably not gonna happen)
- Level Editor
  - Keyframe animation
- Custom language
- 3D rendering
