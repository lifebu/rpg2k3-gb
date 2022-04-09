# rpg2k3-gb
![](https://img.shields.io/badge/Code-C-informational?style=plastic&logo=c&logoColor=white&color=283443)
![](https://img.shields.io/badge/Software-Visual_Studio_Code-informational?style=plastic&logo=visualstudiocode&logoColor=white&color=283443)
![](https://img.shields.io/badge/Tool-CMake-informational?style=plastic&logo=cmake&logoColor=white&color=283443)
![](https://img.shields.io/badge/Engine-RPG_Maker_2003-informational?style=plastic&logoColor=white&color=283443)
Gameboy Emulator written in C++ for RPGMaker 2003.

## Table of Contents
  - [General Information](#general-information)
  - [Technologies Used](#technologies-used)
  - [How To Run](#how-to-run)
  - [Illustrations](#illustrations)
  - [Features](#features)
  - [Sources](#sources)

## General Information
Gameboy system emulator written in C. Custom Toolchain is used to run emulator in unmodified RPG Maker 2003 Software.

### Toolchain
#### CEC: Common Event Compiler.
Compiles C-code of the emulator into a .ldb file of an RPG Maker 2003 project. The database file includes the common events and actual code of the emulator in the format the RPG Maker expects. The code is compiled into .xml format and then lcf2xml is used to compile the .ldb file.

#### GB2MDBR: Gameboy 2 Map/Database ROM/RAM.
To play gameboy software this tool was made to read a gameboy rom (.gb file) and convert it into a format that the RPG Maker 2003 can understand and to be used by the emulator. ROM data from the cartridge is setup in mapfiles (.lmu) and are added to the project map tree (.lmt). RAM data is setup in mapfiles and the project database (.ldb).

#### CRPGENV: C-RPG Maker Environment
Simplified Environment to run emulator code as C-Code for debugging purposes. Platform that implements simple interface which features simple 2D rendering. It resembles the command interface of RPG Maker 2003 Events and implements only what is necessary for the gameboy emulator to run. Allows to debug the emulator without using RPG Maker 2003 or Easy RPG Player.

## Technologies Used
- CMake: >= 3.10.
- lcf2xml: To implement custom toolchain.
- Easy RPG Player: For Testing/Debugging purposes, to run final project you can either use original RPG Maker 2003 or Easy RPG Player (recommended!).


## How To Run
### RPG Maker Project Files.
You can run the generated project with EasyRPG Player. But if you want to run the emulator with an original RPG Maker 2003, this software requires RPG Maker project files. The files cannot be added to this project for legal reasons. RPG Maker 2003 can be purchased from [Steam](https://store.steampowered.com/app/362870/RPG_Maker_2003/). The user needs to create an empty project in RPG Maker 2003 and add the following files to the `rpg2k3/project` folder:
- RPG_RT.exe, RPG_RT.ini, *.r3proj, ultimate_rt_eb.dll

## Illustrations

## Features

## Sources
Tools:
- [lcf2xml from liblcf](https://github.com/EasyRPG/liblcf): convert RPG Maker Project Files to/from xml.
- [Easy RPG Player](https://github.com/EasyRPG/Player): Run RPG Maker Projects on many platforms.

Documentation:
- [Pan Docs](https://gbdev.io/pandocs/About.html): Comprehensive Gameboy technical reference.
- [Gameboy Opcodes](https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html).
- [Gameboy SoC and Cartridge Reference](https://gekkio.fi/files/gb-docs/gbctr.pdf).
