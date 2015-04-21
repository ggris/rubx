# Rubx

OpenGL4 Rubik's cube game development project

### Installation

The project is built using cmake. The *data* folder is copied into the bin/ folder when running cmake.
The *data* folder MUST be next to the executable. Otherwise, the shaders and textures can't be loaded.

##### Dependencies

- glew

##### Unix

In the project root directory type :
```sh
$ make
```

This will create a build folder, call cmake, make and if the build is ok run the program.

If you only wish to quickly launch the program without rebuilding, type :

```sh
$ make run
```


##### Windows

Simply use cmake to generate a project for your prefered IDE.
Currently, the shader directory is in bin/ and Visual Studio builds the project in bin/DEBUG or bin/RELEASE so you must manually copy the shader directory to DEBUG/ or RELEASE/
