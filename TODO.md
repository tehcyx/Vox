# TODO List

* ~~Create VoxGame VoxWindow and VoxApplication classes.~~
* ~~Refactor windows functionality into discrete files and using the VoxWindow class.~~
* ~~Add camera controls and movement to mouse and keyboard controls.~~
* ~~Window and renderer resize functionality.~~
* ~~Add proper license.~~
* ~~Add Shader support to renderer.~~
* ~~Add frame buffer support to renderer.~~
* ~~Add selection of shaders to toggle different render modes for testing.~~
* ~~Add ability to camera class to rotate around point (rotate position around view).~~
* ~~Deferred lighting support.~~
* ~~Lighting effects.~~
* ~~Particle effects.~~
* ~~Add weapon trails.~~
* ~~Remove any GL calls from VoxGame - Add InitZeroTexture() functionality to renderer.~~
* ~~Use Cmake for build management.~~
* ~~Add fullscreen support and toggle.~~
* ~~Enable x64 build configurations.~~
* ~~Phong lighting shader.~~
* ~~Add basic lighting to scene - OpenGL lighting.~~
* ~~Add pre-built release exe to root of git, so people can run exe without compiling - VoxGame.exe~~
* ~~Better SSAO shader.~~
  * ~~Make deferred lighting and SSAO optional toggles separate.~~
  * ~~Allow for phong shading and deferred lighting together.~~
* ~~Shadow shader.~~
* ~~Decouple shadow rendering from SSAO shader.~~
* ~~Decouple dynamic lighting from SSAO shader.~~
* ~~Better readme file.~~
* ~~Split up VoxGame file into VoxRender, VoxUpdate, VoxSetup(?), etc.~~
* ~~App player class and put voxel character functionality in player class.~~
* ~~Add ability to switch voxel character model.~~
* ~~Rebuild vs2013 libs using non-dll version of linking~~
* ~~Fix up cmake for the different visual studio versions and also for the different lib linking.~~
* ~~Weapon trails controlled by the animation file.~~
* ~~Create vs2012 libs and VS2012 project files~~
* Switch over to using glm maths lib.
* Enable cross platform compiling and support, linux, mac
* Solution to allow for running the exe from Visual studio, because atm the working directory needs to be ../
* Convert shaders over to be more unified.
* Add blur shader.
* Implement MSAA (or other AA) in glsl shader.
* Add audio and music playback.
* Convert shadow rendering calls to use renderer - remove GL from gamecode.
* Add LUA bindings.
