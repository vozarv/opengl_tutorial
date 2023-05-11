
## CMRC install
https://github.com/vector-of-bool/cmrc


## 
sudo apt-get install libglew-dev
sudo apt-get install libsdl2-dev
sudo apt-get install libgl-dev
sudo apt-get install libglm-dev
sudo apt-get install libglfw3-dev

## Assimp
https://github.com/assimp/assimp/blob/master/Build.md

## Download objects
https://sketchfab.com/3d-models/
User: a@gmail.com
Password: 12345678

## TODO

Spotlight still doesn't work properly - Solved: the FragPos variable in the vertex shader was incorrectly multiplied with the view matrix
Material specular texture map cannot load - Solved: Needed to specify the position with "updateUniform("material.specular", 1);"
The loaded texture is shifted on objects - Solved: The Cube texture coords were in wrong order
Windows compatibility (GLEW, GLFW3, SDL2, GLM)
WASD should move horizontally - Solved: GetHorizontalForward() function
Scene object 
Light handling object
Blending objects should be drawn based on distance from the camera
Mirror effect

# Windows

Install clang in Visual Studio Installer
Install vcpkg (optionally: add it to PATH)
Run the following command: vcpkg install opengl glfw3 sdl2 glm glew --triplet=x64-windows

Add the vcpkg toolchain file path to your project:

./.vscode/settings.json
{
  "cmake.configureSettings": {
    "VCPKG_TARGET_TRIPLET": "x64-windows",
    "CMAKE_TOOLCHAIN_FILE": "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
  }
}

