/*
 * Author: myapit
 * Purpose: terminal application with menu
 *
 */

#include <iostream>
#include <iomanip>
#include <string>

#include "linux_programming/termcolor.hpp"


void terminal_header()
{
    std::cout << termcolor::red << std::setfill('=') << std::setw(100) << termcolor::reset << std::endl; 
    //std::cout << 
    std::cout << std::setfill(' ') << std::setw(30) << termcolor::red <<"██╗    ██╗ █████╗ ██████╗ ██╗███████╗ "  << termcolor::reset << std::endl
              << std::setfill(' ') << std::setw(30) << termcolor::red <<"██║    ██║██╔══██╗██╔══██╗██║██╔════╝ "  << termcolor::reset << std::endl
              << std::setfill(' ') << std::setw(30) << termcolor::red <<"██║ █╗ ██║███████║██████╔╝██║███████╗ "  << termcolor::reset << std::endl
              << std::setfill(' ') << std::setw(30) << termcolor::red <<"██║███╗██║██╔══██║██╔══██╗██║╚════██║ "  << termcolor::reset << std::endl
              << std::setfill(' ') << std::setw(30) << termcolor::red <<"╚███╔███╔╝██║  ██║██║  ██║██║███████║ "  << termcolor::reset << std::endl
              << std::setfill(' ') << std::setw(30) << termcolor::red <<" ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝  V 1.0"  << termcolor::reset << std::endl
              << termcolor::reset;
    std::cout << std::setfill(' ') << std::setw(23) << termcolor::red << "Web Application Registration System Managemnt Tools" << termcolor::reset << std::endl; 
    std::cout << termcolor::red << std::setfill('=') << std::setw(100) << termcolor::reset << std::endl; 
}

int main(int argc, char *argv[])
{
    std::cout.flush();
    std::cout << "\033[2J\033[1;1H";
    terminal_header();
    std::cin.get();
    return 0;
}

