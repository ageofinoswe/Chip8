#ifndef RAM_H_
#define RAM_H_

#include <iostream>
#include <cstdint>
#include <fstream>

/* Random Access Memory Container*/
class Ram
{
    public:
        /* constructors */
        Ram();
        /* write a value to ram at a given index
           returns true if successful, false if out of range */
        bool setMem(const int index, const int value);
        /* read a value from ram at a given index
           returns value if successful, -1 if out of range */
        int readMem(const int index) const;
        /* print out the contents of ram */
        void memDump() const;

    private:
        /* size of ram */
        static const int MEMORY_SIZE = 4096;
        /* ram */
        uint8_t mainMemory[MEMORY_SIZE];
        /* validates if the access of the ram is valid at a given index
           returns true if valid, false if out of range */
        bool validateRange(const int index) const;
};

#endif /* RAM_H_ */