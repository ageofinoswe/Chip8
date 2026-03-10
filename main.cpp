#include <iostream>
#include <string>
#include "Chip.h"

using std::string;
using std::stoi;

int main(int argc, char *argv[])
{
    // default file
    string dir = "./ROMS/";
    string defaultFileName = "IBM Logo";
    string extension = ".ch8";
    string fileName = dir + defaultFileName + extension;

    // user provided file
    if(argc == 2)
    {
        fileName = dir + argv[1] + extension;
        Chip chip(fileName);
        chip.start();
    }

    // user provided file, opcode configs
    else if(argc == 8)
    {
        fileName = dir + argv[1] + extension;
        int shiftImpl = 1;
        int jumpOffsetImpl = 1;
        int storeLoadImpl = 1;

        for(int i = 2 ; i < argc ; i++)
        {
            string arg = argv[i];

            if(arg == "--shift")
            {
                shiftImpl = stoi(argv[++i]);
            }
            else if(arg == "--jump")
            {
                jumpOffsetImpl = stoi(argv[++i]);
            }
            else if(arg == "--memory")
            {
                storeLoadImpl = stoi(argv[++i]);
            }
        }
        Chip chip(fileName, shiftImpl, jumpOffsetImpl, storeLoadImpl);
        chip.start();
    }

    // run default file
    else
    {
        Chip chip(fileName);
        chip.start();
    }

    return 0;
}