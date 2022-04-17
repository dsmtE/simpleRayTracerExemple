# simpleRayTracerExemple

Welcome !

This is a small template and exemple showing the basic usage of glm in the contexe of naive shere raytracer.

## Compiling

You need to install [CMake](https://cmake.org/download/).

To use CMake I recommend this VS Code extension : [ms-vscode.cmake-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools). You will need to setup the extension with a compiler. Here is [the tutorial](https://code.visualstudio.com/docs/cpp/cmake-linux). It is based on Linux but at the bottom of the page you will find the explanations to adapt it for [Windows](https://code.visualstudio.com/docs/cpp/config-msvc) and [Mac](https://code.visualstudio.com/docs/cpp/config-clang-mac).

Alternatively you can just create a *build* folder at the root of this project, open a terminal and run `cmake ..` ; chances are it will detect what compiler you have installed and generate the appropriate Makefile / Visual Studio solution / Xcode project.

## main.cpp

In here we initialize [*glfw*](https://www.glfw.org/docs/latest/) (the library that handles the window and user inputs), create a window and then start the app. You don't really need to modify this file, except to change your window name or initial size.

## User inputs

To learn more about the parameters you receive in the callbacks, read [glfw's documentation](https://www.glfw.org/docs/latest/input_guide.html).

## App

This is the actual root of the project, where the subclass RayTracedScene is called to render our scene in a colorBuffer.
Then, the app transfert thoses data in a texture and render it on the screen.
