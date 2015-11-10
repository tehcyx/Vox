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
* ~~Add blur shader.~~
* ~~Implement MSAA (or other AA) in glsl shader.~~
* ~~Convert shadow rendering calls to use renderer - remove GL from gamecode.~~
* ~~Add LUA bindings.~~
* ~~Make weapons trails time based, rather than "numpoints" based, better weapon trail alpha rendering.~~
* ~~Switch over to using glm maths lib.~~
* ~~Solution to allow for running the exe from Visual studio, because atm the working directory needs to be ../~~
* ~~Textures on GUI.~~
* ~~Frontend manager for textures and common GUI objects.~~
* ~~Allow camera rotations around world coordinates, so 'upside down' doesnt happen.~~
* ~~Add full GUI skin textures and control to change 'theme' on GUI.~~
* ~~Add limits to rotation so we dont go over and under the max/min up-axis.~~
* ~~Add different camera modes, option toggle on GUI.~~
* ~~Add player camera controls.~~
* ~~Enable cross platform compiling and support, linux, mac~~
* ~~Convert all data, media, folders to lowercase to fix Linux issues.~~
* Convert shaders over to be more unified.
* Add VLD support to debug version, allow for memory leak detection.
* Add audio and music playback.
* Add gamepad support.
* Add scenery manager.
* Create basic front-end
* Add character creator and customization from front-end.
* Add voxel editor.
* Add texture support for voxel blocks.
* Proper first person mode camera.
* When in auto-camera mode, slowly orient to behind the player, after a time.
* Implement mouse rotation camera mode for when in game mode.
* Turn cursor on/off and fix cursor in position when doing mouse rotations in game mode.
