#include "GetIntFromConsole.h"

void GetIntFromConsole::convertStringToInt() {
    try{
        number = std::stoi(consoleInput);
        if(number < 4 || number > 10000000) throw std::runtime_error("Invalid input.");
        isErrorState = false;
    }catch (std::out_of_range &e){ std::cout << "Number is to large." << std::endl;
    }catch(...){ std::cout << "Invalid input." << std::endl; }
}

void GetIntFromConsole::requestInput() {
    std::cout << "Enter number between 4 and 10000000 to specify size of Board." << std::endl;
    std::cout << "If board is less or equal to 16x16, algorithm will be printed, which may take a while." << std::endl;
    std::cout << ": ";
}

void GetIntFromConsole::getConsoleInput() {
    std::cin >> consoleInput;
}

int GetIntFromConsole::scan() {
    while(isErrorState){
        requestInput();
        getConsoleInput();
        convertStringToInt();
    }
    system("cls");
    return number;
}


