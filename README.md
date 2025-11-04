# Project Documentation

## Overview
This project implements a simple graphics system that allows for the drawing of basic shapes such as pixels, lines, rectangles, circles, and triangles. It also supports displaying BMP images, rendering ASCII characters and Chinese characters, and animating a bouncing ball. The project is designed to run on a Linux environment using a framebuffer device.

---

## Files
- **draw.c**: Implements the graphics system's initialization, cleanup, and functions for drawing basic shapes.
- **draw.h**: Defines the interface for the graphics system, including function declarations for initialization, cleanup, and drawing basic shapes.
- **bmp.c**: Implements functions for loading and displaying BMP images.
- **bmp.h**: Defines the interface for BMP image handling.
- **char.c**: Implements functions for rendering ASCII characters and Chinese characters using a dot matrix font.
- **char.h**: Defines the interface for character rendering.
- **ball.c**: Implements the animation of a bouncing ball.
- **ball.h**: Defines the interface for the ball animation.
- **main.c**: The entry point of the program, responsible for initializing the graphics system, invoking various features, and cleaning up at the end.
- **Makefile**: Contains the compilation rules using the cross-compilation tool `loongarch64-linux-gnu-gcc` to compile the code files in the project.
- **README.md**: This documentation file that provides an overview and details about the project.

---

## Compilation
To compile the project, use the following command in the terminal:

```bash
make
```

This will generate an executable named `graphics_app`.

---

## Cleaning Up
To remove the compiled executable, run:

```
make clean
```

---

## Usage
After compiling, ensure the following files are present in the same directory as the executable:
1. **`image.bmp`**: A BMP image file used to test the BMP image display functionality.
2. **`HZK16`**: A dot matrix font file used to render Chinese characters.

Run the `graphics_app` executable to see the graphics system in action:
```
./graphics_app
```
2. Ensure the screen resolution matches the program's default resolution (1024x768) for proper display.
3. Missing `image.bmp` or `HZK16` files will result in the corresponding features not functioning correctly.