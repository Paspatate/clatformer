# Platformer
This is a prototyping project for me to learn opengl

## Build

### Linux
You need to install glfw3 to build the game.

```bash
sudo apt install libglfw3-dev # on debian based distro
sudo pacman -S glfw # on arch based distro
```

I use premake to generate the build file. 

Example to use make as a build method.

```bash
premake5 gmake2
make -C build
```

### Windows
Does not support windows for now

