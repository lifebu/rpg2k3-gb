# rpg2k3-gb
![](https://img.shields.io/badge/Code-C++-informational?style=plastic&logo=cplusplus&logoColor=white&color=283443)
![](https://img.shields.io/badge/Software-Visual_Studio_Code-informational?style=plastic&logo=visualstudiocode&logoColor=white&color=283443)
![](https://img.shields.io/badge/Tool-CMake-informational?style=plastic&logo=cmake&logoColor=white&color=283443)
![](https://img.shields.io/badge/Engine-RPG_Maker_2003-informational?style=plastic&logoColor=white&color=283443)

Gameboy Emulator written in C++ for RPGMaker 2003 with custom toolchain to allow compiling and debugging.

## Table of Contents
  - [General Information](#general-information)
  - [Current State](#current-state)
  - [Technologies Used](#technologies-used)
  - [How To Run](#how-to-run)
  - [Illustrations](#illustrations)
  - [Features](#features)
  - [Sources](#sources)

## General Information
Gameboy system emulator written in C++. Custom toolchain is used to run the emulator in unmodified RPG Maker 2003 Software. To allow debugging and implementation in stages, other projects are needed. First a tool is used to load a Gameboy ROM and convert it into a special XML format. It can also generate files for running the emulator in a special RPGMaker-like runtime written in C++, an EasyRPG project, or an RPG Maker 2003 project. The Code for the actual emulator is compiled into XML by using a simple and custom C++ compiler. All of this can be controlled from a cental and easy to use Commandline interface (CLI).

## Current State
The only tool currently being worked on is GB2RPG. It loads the Gameboy file and can read each byte from it. Additionally the map file and maptree generation works.
**Warning: The generation of the XML file is currently very inefficient and stores the entire file in Memory and can take up to 2 minutes. Therefore the tool can need up to 16GB RAM. This will be fixed soon.**
This software is still very early in development.

The other tools needed will be worked on in the following order:
- CppRPGEnv: To allow C++ code to be written against a RPG Maker like interface.
- Gameboy Emulator: Write the actual emulator using the interface given by CppRPGEnv.
- Main CLI (rpg2k3-gb): To allow ease of use of the entire toolset to generate a project and test the emulator.
- CppEC: To compile the emulator code into the xml format to start testing using EasyRPG first then the actual RPG Maker second.



## Technologies Used
- CMake: >= 3.10.
- lcf2xml: To implement custom toolchain.
- Easy RPG Player: For Testing/Debugging purposes, to run final project you can either use original RPG Maker 2003 or Easy RPG Player.
- SFML: To create the simple RPG Maker runtime.

## How To Run
The project uses CMake to compile and create all the software and tools necessary. 

## Illustrations
Project still in development and no illustrations are available.

## Features
### Emulator
The exact capabilities of the emulator will be determined when the project has matured more. 
My research shows, that Gameboy Color games might not be supported either because of memory constraints or the added color putting a restraint on rendering in the RPG maker.

### Toolchain
#### GB2RPG: Gameboy 2 RPG Maker.
To play gameboy software this tool was made to read a gameboy rom (.gb file) and convert it into a format that the RPG Maker 2003 can understand and to be used by the emulator. ROM data from the cartridge is setup in mapfiles (.lmu/.emu) and are added to the project map tree (.lmt/.emt). RAM data is setup in mapfiles and the project database (.ldb/edb). To finally run the files in a project the tool creates project folders for a custom C++ runtime, EasyRPG Player or RPG Maker 2003. The runtime and the EasyRPG project can be used to debug the code for different stages.

#### CppRPGEnv: C++ RPG Maker Environment
Simplified environment to run emulator code as C++ code for debugging purposes. It mimics the API that you find for RPG Maker 2003 events and implements only what is strictly necessary for the development of the emulator. It uses SFML as a backend for 2D rendering. It allows to debug the actual emulator outside of an RPG Maker or EasyRPG project.

#### CppEC: C++ Event Compiler.
Compiles C++-code of the emulator into a xml file which is a list of Common Events. These can then be added to a database file (.lbd/.edb) by using lcf2xml. 

## Sources
**Indepth information about what was integrated from thirdparty software can be found in the thirdparty/README.md file.**

Tools:
- [lcf2xml from liblcf](https://github.com/EasyRPG/liblcf): convert RPG Maker Project Files to/from xml.
- [Easy RPG Player](https://github.com/EasyRPG/Player): Run RPG Maker Projects on many platforms.
- [tinyxml2](https://github.com/leethomason/tinyxml2): to read/write xml files in C++.
- [SFML](https://www.sfml-dev.org/): Simple runtime that allows 2D graphics, audio and networking.
- [RPG Maker 2003](https://www.rpgmakerweb.com/products/rpg-maker-2003): To run the projects on the original RPG Maker you can buy it on [Steam](https://store.steampowered.com/app/362870/RPG_Maker_2003/).

Documentation:
- [Pan Docs](https://gbdev.io/pandocs/About.html): Comprehensive Gameboy technical reference.
- [Gameboy Opcodes](https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html).
- [Gameboy SoC and Cartridge Reference](https://gekkio.fi/files/gb-docs/gbctr.pdf).
