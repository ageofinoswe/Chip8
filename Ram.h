#ifndef RAM_H_
#define RAM_H_

#include <iostream>
#include <cstdint>
#include <fstream>

class Ram
{
    public:
        //constructor
        Ram();
        // write a value to ram at a given index
        void setMem(const int index, const uint8_t value);
        // read a value from ram at a given index
        uint8_t readMem(const int index) const;
        // print out the contents of ram
        void memDump() const;

    private:
        // size of ram, 4kB
        static constexpr int MEMORY_SIZE = 4096;
        // ram representation
        uint8_t mainMemory[MEMORY_SIZE];
        // validates is ram access is valid
        bool validateRange(const int index) const;
};

#endif /* RAM_H_ */