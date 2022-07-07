#include "ProjectGenerator.h"

#include "GBFile.h"

#include <string>
#include <filesystem>

// public
void ProjectGenerator::genProjectFolder(std::vector<GBFile>& gbFiles) {
    createProjectData();
    genFolders();
}

// private
void ProjectGenerator::createProjectData() {
    // call lcf2xml in the project/rpg2k3 folder with the .xml files in project/

    // copy proprietary data from templates/project to project/rpg2k3
    // TODO: should probably do something with the errors, but that's okay for now (could use exceptions here!)
    std::error_code err;
    std::filesystem::copy("templates/project/Gameboy_Emulator.r3proj", "project/rpg2k3/Gameboy_Emulator.r3proj", err);
    std::filesystem::copy("templates/project/RPG_RT.exe", "project/rpg2k3/RPG_RT.exe", err);
    std::filesystem::copy("templates/project/RPG_RT.ini", "project/rpg2k3/RPG_RT.ini", err);
    std::filesystem::copy("templates/project/ultimate_rt_eb.dll", "project/rpg2k3/ultimate_rt_eb.dll", err);

    // TODO: copy easyrpg executable into the project folder
}

void ProjectGenerator::genFolders() {
    // TODO: should probably do something with the errors, but that's okay for now (could use exceptions here!)
    std::error_code err;
    std::filesystem::create_directories("project/rpg2k3/Backdrop", err);
    std::filesystem::create_directories("project/rpg2k3/Battle", err);
    std::filesystem::create_directories("project/rpg2k3/Battle2", err);
    std::filesystem::create_directories("project/rpg2k3/BattleCharSet", err);
    std::filesystem::create_directories("project/rpg2k3/BattleWeapon", err);
    std::filesystem::create_directories("project/rpg2k3/CharSet", err);
    std::filesystem::create_directories("project/rpg2k3/ChipSet", err);
    std::filesystem::create_directories("project/rpg2k3/FaceSet", err);
    std::filesystem::create_directories("project/rpg2k3/Frame", err);
    std::filesystem::create_directories("project/rpg2k3/GameOver", err);
    std::filesystem::create_directories("project/rpg2k3/Monster", err);
    std::filesystem::create_directories("project/rpg2k3/Movie", err);
    std::filesystem::create_directories("project/rpg2k3/Music", err);
    std::filesystem::create_directories("project/rpg2k3/Panorama", err);
    std::filesystem::create_directories("project/rpg2k3/Picture", err);
    std::filesystem::create_directories("project/rpg2k3/Sound", err);
    std::filesystem::create_directories("project/rpg2k3/System", err);
    std::filesystem::create_directories("project/rpg2k3/System2", err);
    std::filesystem::create_directories("project/rpg2k3/Title", err);
}