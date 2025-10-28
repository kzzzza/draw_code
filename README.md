# Project Documentation

## Overview
This project implements a simple graphics system that allows for the drawing of basic shapes such as pixels, lines, rectangles, circles, and triangles. It is designed to run on a Linux environment using a framebuffer device.

## Files
- **draw.c**: Implements the graphics system's initialization, cleanup, and functions for drawing basic shapes.
- **draw.h**: Defines the interface for the graphics system, including function declarations for initialization, cleanup, and drawing basic shapes, as well as data structures like Point and Rectangle.
- **main.c**: The entry point of the program, responsible for initializing the graphics system, obtaining screen resolution, drawing basic shapes, and cleaning up the graphics system at the end.
- **Makefile**: Contains the compilation rules using the cross-compilation tool `loongarch64-linux-gnu-gcc` to compile the code files in the project.
- **README.md**: This documentation file that provides an overview and details about the project.

## Compilation
To compile the project, use the following command in the terminal:
```
make
```
This will generate an executable named `graphics_app`.

## Cleaning Up
To remove the compiled executable, run:
```
make clean
```

## Usage
After compiling, run the `graphics_app` executable to see the graphics system in action. The program will initialize the graphics system, draw a variety of shapes, and then clean up before exiting.