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

    // default configs (these opcodes are ambiguous and have different implementations; accepts 1 or 2)
    // certain configs may work for one game, but not another
    int shiftImpl = 1;
    int jumpOffsetImpl = 1;
    int storeLoadMemImpl = 1;

    // user provided file
    if(argc == 2)
    {
        if(strcmp(argv[1], "AnimalRace") == 0)
        {
            shiftImpl = 1;
            jumpOffsetImpl = 1;
            storeLoadMemImpl = 2;
        }
        if(strcmp(argv[1], "Blinky") == 0 || strcmp(argv[1], "SpaceInvaders") == 0)
        {
            shiftImpl = 2;
        }
        fileName = dir + argv[1] + extension;
        Chip chip(fileName, shiftImpl, jumpOffsetImpl, storeLoadMemImpl);
        chip.start();
    }

    // user provided file, opcode configs
    else if(argc > 8)
    {
        fileName = dir + argv[1] + extension;

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
                storeLoadMemImpl = stoi(argv[++i]);
            }
        }
        Chip chip(fileName, shiftImpl, jumpOffsetImpl, storeLoadMemImpl);
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