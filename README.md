# Vox
Vox engine is an open source voxel engine that is written in C++ and OpenGL and can be used to create easy and fast voxel based games and applications. The engine is written to be highly functional and very efficient at allowing voxel game creation and provides a simple framework for creating 3d voxel games.

## Features
* GLSL shader support.
* Support for deferred or forward rendering.
* Fully dynamic and unlimited lighting system using deferred lighting model.
* Advanced graphics shaders included - SSAO, shadow mapping, dynamic lighting, FXAA.
* Full 3d math and geometry library (vector, matrix, quaternion, plane, bezier).
* Extensive camera functionality, either 3d person or 1st person.
* In-built GUI that can be easily hooked up to gameplay functioanlity. (re-skinable)
* Qubicle Binary (.qb) voxel model loading.
* Polygon model loading via ms3d and obj files.
* Keyframe and skeleton animation support.
* Basic 'player' functionality - movement, controls, animation.
* 'Voxel character' encapsulating character behaviours - idle looking, breathing, etc.
* Facial animation support for voxel characters.
* Voxel scenery and world items.
* Block/cube particle effect system.
* Modding and scripting support via LUA.
* Voxel world and terrain generation. *[coming soon!]*
* Procedural content creation. *[coming soon!]*
* In-built voxel editor for creation/editing of in-game assets. *[coming soon!]*
* Audio and music playback. *[coming soon!]*
* Gamepad and controller support. *[coming soon!]*

## License
This software is provided under the **GNU General Public License**, more information is provided in the [license file](https://github.com/AlwaysGeeky/Vox/blob/master/LICENSE.md).

## Setup
Setting up and compiling the project is a fairly simple process. Cmake can be used to build the project files for each environment and for different platforms, depending on what you are developing on. Just run Cmake on the root level of the project.

**Windows**

Visual Studio projects are included inside the ```\project``` sub-folder (VS2012, VS2013, VS2015).

**Linux**

Various project files are included inside the ```\project\linux``` sub folder.

**Mac**

// Todo //

## Running
The Vox executable needs to be run from the root directory so that it has access at the top level to the ```\media``` folder that contains all the game content files. If you want to run the game's executable from within the Visual Studio projects then you will need to set the working directy in the Debugging options to ```'..\..\'``` since the visual studio projects files reside in sub-directories above the root.

Alternatively you can run the pre-built executable ```VoxGame.exe``` that is containted within this github repo. For running the prebuilt executable on Linux you can simply run ```./VoxGame``` from within the root ```/Vox``` directory. *Please note however that there is no guarantee that this exe will contain the latest code from the repo.*

## How To Contribute
Contributions are always welcome, either reporting issues/bugs or forking the repository and then issuing pull requests when you have completed some additional coding that you feel will be beneficial to the main project. If you are interested in contributing in a more dedicated capacity, then please contact me.

## Contact
You can contact me via twitter at http://www.twitter.com/AlwaysGeeky. I am always happy to answer questions or help with any issues you might have, and please be sure to share any additional work or your creations with me, I love seeing what other people are making.

## Screenshots
![Vox](http://i.imgur.com/usPCqJt.png)
![Vox](http://i.imgur.com/mZ85dWP.png)

## Videos
