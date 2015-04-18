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

This will create a build folder and call cmake.
Then you can go in the build directory an build the program.

```sh
$ cd build
$ make
```

To run the program, you must be in the bin/ directory.
```sh
$ cd bin
$ ./rubx
```

##### Windows

Simply use cmake to generate a project for your prefered IDE.
Currently, the shader directory is in bin/ and Visual Studio builds the project in bin/DEBUG or bin/RELEASE so you must manually copy the shader directory to DEBUG/ or RELEASE/
