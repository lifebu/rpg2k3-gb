#include <iostream>

// TODO: Completly rework this. Not a priority right now!

enum State {
    MAIN_MENU,
    CREATE_PROJECT
};

void printMainMenu() {
    std::cout << "Select the following options to continue:\n";
    std::cout << "1) Create RPG Maker Project\n";
    std::cout << "2) Run with C++ Environment\n";
    std::cout << "3) Run with EasyRPG Project\n";
    std::cout << "4) Run with RPG Maker 2003\n";
    std::cout << "5) Exit\n";
}

State mainMenu(State& state) {
    printMainMenu();
    int choice;
    std::cin >> choice;
    switch(choice) {
        case 1: {

        } break;
        case 2: {

        } break;
        case 3: {

        } break;
        case 4: {

        } break;
        case 5: {

        } break;
        default: {
            std::cout << "Entered invalid input number, use a number between [1,5].\n";
        } break;
    }
}

int main (int argc, char* argv[]) {
    State state = MAIN_MENU;
    bool isRunning = true;

    while(isRunning) {
        if(state == MAIN_MENU) {
            state = mainMenu(state);
        
        } else if(state == CREATE_PROJECT) {
            state = mainMenu(state);
        }
    }
}