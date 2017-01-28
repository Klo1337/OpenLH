# OpenLH

OpenLH engine replacement for Mafia: The City of Lost Heaven.

## Pre-install
Before starting, make sure you have installed [CMake](https://cmake.org/). It will be used to generate make files for your system.
Also make sure you have installed any working compiler for your system.

## Installation

```sh
$ git clone --recursive git@github.com:MafiaUnited/OpenLH.git openlh
$ cd openlh
$ mkdir -p build && cd build
$ cmake ..
```

## Building

Then go inside build folder, there you can find either Makefile which should be used to `make` it.

Unix:

```sh
cd build
make
./server
```

Windows:
If you are using Visual Studio, proper project/solution files should be generated for your visual studio.
Run build, and enjoy.

## Used dependencies
* [libuv/libuv](https://github.com/libuv/libuv) 1.9.0 via cmake interface [Inlife/libuv-cmake](https://github.com/Inlife/libuv-cmake)
* [Inlife/RakNet](https://github.com/Inlife/RakNet) 4.081 (slightly modified version)
* [inlife/squirrel-lang](https://github.com/inlife/squirrel-lang) 3.0 stable with cmake interface

## Compilation tested on
* macos 10.12.2 with g++ 4.2.1
* ubuntu 16.04 with g++
* windows 10 with msvc 14.0

## Bugs
* Windows 10 mingw 5.3.0, problems with RakNet
- Linux client doesn't support bgfx yet.
