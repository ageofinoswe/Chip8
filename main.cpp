#include <iostream>
#include <string>
#include "Chip.h"

using std::string;

int main(int argc, char *argv[])
{
    // provided chip8 file
    string fileName = "IBM Logo.ch8";

    // user provided file
    if(argc > 1)
        fileName = argv[1];
    
    // begin chip8 emulation    
    Chip chip(fileName);
    chip.start(); 
    
    return 0;
}