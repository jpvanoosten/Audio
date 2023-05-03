# Audio

A super minimalistic C++ audio library.

## Features

Should work on most platforms, but I've only tested it on Windows.

The `Audio::Sound` class can be used to play one-shot sound effects and can also be used to stream background music to minimize memory use.

The `Audio::Waveform` class can be used to play waveform sounds. See [MarioCoin.hpp](example/MarioCoin.hpp) and [MarioCoin.cpp](example/MarioCoin.cpp) for an example of creating a complex sound effect using Waveforms.

## Installation

This project comes with both a Visual Studio 2022 solution and project file and a `CMakeLists.txt` file for use with CMake.

### Visual Studio 2022

Open the `Audio.sln` file in the root directory of this repository. You should see two projects in the solution:

1. Audio (Static library): This project generates the `Audio.lib` file that you must link to in your own project.
2. example (Exectuable): This is an example showing how to work with the Audio library. You can inspect the project settings of this project to see how to integrate the `Audio.lib` file into your own projects.

Running the example project in Visual Studio should play a narration and show a few examples of working with `Waveform`s.

### CMake

You should have (at least) CMake 3.23.0 installed (and added to your `PATH` environment variable in Windows). If you don't have CMake, please download it from [cmake.org](https://cmake.org/download/). Make sure you download the installer for your platform (don't download the source distributions).

To generate the Visual Studio solution and project files, run the [GenerateProjectFiles.bat](GenerateProjectFiles.bat) batch file on Windows. This script uses [vswhere](https://github.com/microsoft/vswhere) to detect the latest version of Visual Studio you have installed and will generate the solution project files for the version of Visual Studio you have installed.

Alternatively, you can open the Audio folder directly in the CMake GUI to generate the solution and project files.

![CMake GUI](docs/images/CMakeGUI.png)

There is a preset (use the preset drop-down menu in the CMake GUI) for Visual Studio 2019 and 2022 that you can use to generate the solution and project files.

In the CMake GUI, use the **Configure**, **Generate**, and **Open Project** buttons to generate and open the Visual Studio project files.

## Build

