#!/usr/bin/env bash

BIN=$PWD/bin

mkdir -p $BIN

# Clone glfw
if [ ! -d "$BIN/glfw" ]; then
  git clone https://github.com/glfw/glfw.git $BIN/glfw
else
  echo "GLFW already cloned."
fi

# Compile glfw
if [ ! -f "$BIN/libglfw3.a" ]; then
  cd $BIN/glfw
  cmake -B . -S .
  make
  cd ..
  cp $BIN/glfw/src/libglfw3.a $BIN
else
  echo "GLFW already compiled."
fi

# Clone luaJIT
if [ ! -d "$BIN/luajit" ]; then
  git clone https://luajit.org/git/luajit.git $BIN/luajit
else
  echo "LuaJIT already cloned."
fi

# Compile luaJIT
if [ ! -f "$BIN/libluajit.a" ]; then
  cd $BIN/luajit
  make
  cp $BIN/luajit/src/libluajit.a $BIN
else
  echo "LuaJIT already compiled."
fi
