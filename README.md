# Hobby Engine

## !! WARNING !! Very early in development

A game engine made to be simple. Primarily a 2D engine, though 3D is not off
the table as a feature.
<br>
This engine should do all the hard/annoying stuff for you. Things like
rendering, audio, input, object processing, physics. All the easy stuff should
be left to the user.
<br>
The name comes from the species of bird known as Hobbies, and the fact that 
this is, in fact, a hobby project.
<br>
Anyway, please, stare at the logo:

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="assets/hobby-dark.png">
  <source media="(prefers-color-scheme: light)" srcset="assets/hobby-light.png">
  <img alt="Hobby Engine logo" width="256px" height="256px">
</picture>

## Docs
If you want to learn Hobby for whatever reason, then check out the wonderfully
made [the docs](docs/).

## Building
#### Linux (And maybe MacOS)
```
$ sh compile_libs.sh
$ cmake -S . -B bin
$ cd bin
$ make
```
#### Windows
Not supported (yet)

### Features
- Basic rendering
- Lua scripting
- Textures
- Input
- Events

### Planned Features
- Shaders
- Text and font loading
- 2D audio
- Render textures
- Virtual filesystem, save system
- Physics engine
- Tilemaps
- Pathfinding
- UI system
- Editor

### Low-Priority Planned Features (Probably not gonna happen)
- 3D rendering
