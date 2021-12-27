
#ifndef NQUEENS_GETINTFROMCONSOLE_H
#define NQUEENS_GETINTFROMCONSOLE_H
#include <iostream>
#include <string>

class GetIntFromConsole {
private:
    std::string consoleInput;
    int number = 0;
    bool isErrorState = true;

    void convertStringToInt();
    static void requestInput();
    void getConsoleInput();

public:
    int scan();
};


#endif //NQUEENS_GETINTFROMCONSOLE_H
