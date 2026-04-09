#pragma once

#include <iostream>
#include <limits>

inline void CP_PauseForContinue()
{
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
