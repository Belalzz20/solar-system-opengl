# Solar System Simulation using OpenGL

A real-time 3D solar system simulation developed using C++ and OpenGL. The project visualizes the Sun, eight planets, their orbital paths, and a starfield background.

## Features

- 3D visualization of the Sun and eight planets.
- Animated planetary orbits and rotation.
- Orbital paths for each planet.
- Saturn's ring system.
- Starfield background with subtle animation.
- Interactive camera controls for rotation and zoom.
- Depth testing and 3D rendering using OpenGL.

## Technologies Used

- C++
- OpenGL
- FreeGLUT
- GLEW
- GLM
- GLSL shaders
- Visual Studio

## Project Structure

```text
solar-system-opengl/
├── Lab4.sln
├── Lab4.vcxproj
├── Source.cpp
├── Sphere.cpp
├── Sphere.h
├── InitShader.cpp
├── vshader.glsl
├── fshader.glsl
├── include/
├── lib/
├── freeglut.dll
└── glew32.dll
```

## Requirements

- Windows
- Visual Studio with the Desktop development with C++ workload
- A compatible OpenGL graphics environment
- The project dependencies and library files included in the repository

## Getting Started

1. Download or clone this repository.
2. Open `Lab4.sln` in Visual Studio.
3. Select a supported build configuration and platform.
4. Build the solution.
5. Run the application from Visual Studio.

If the project fails to build, check the configured include directories, library directories, and required linker dependencies.

## Controls

| Key | Action |
|---|---|
| `A` | Rotate the camera to the left |
| `D` | Rotate the camera to the right |
| `W` | Move the camera angle upward |
| `S` | Move the camera angle downward |
| `+` | Zoom in |
| `-` | Zoom out |
| `Esc` | Exit the application |

## Project Purpose

This project explores fundamental 3D graphics concepts, including geometric transformations, animation, orbital motion, camera navigation, and interactive rendering with OpenGL.

## Author

**Belal Hesham**

GitHub: [@Belalzz20](https://github.com/Belalzz20)
