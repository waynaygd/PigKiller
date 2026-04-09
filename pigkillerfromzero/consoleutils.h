#pragma once

#include <iostream>
#include <limits>
#ifdef _WIN32
#include <conio.h>
#endif

inline void CP_PauseForContinue()
{
    std::cout << "Press Enter to continue...";
#ifdef _WIN32
    while (_getch() != '\r') {}
#else
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
#endif
}
