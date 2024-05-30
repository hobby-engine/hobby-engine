# Hobby Engine

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="assets/hobby-dark.png">
  <source media="(prefers-color-scheme: light)" srcset="assets/hobby-light.png">
  <img alt="Hobby Engine logo" width="256px" height="256px">
</picture>

Hobby is early in development. Use at your own risk.<br>
Hobby is a simple 2D Lua game engine. It is named after the bird known as
hobbies.

## Docs
If you want to learn Hobby for whatever reason, then check out the wonderfully
made [docs](docs/).

## Building
#### Linux (And maybe MacOS)
```
$ sh compile_libs.sh
$ cmake -S . -B bin
$ cd bin
$ make
```
#### Windows
I've done it and know it's possible, but figure it out yourself (Hint: MinGW)

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
