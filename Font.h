#ifndef FONT_H_
#define FONT_H_
#include <cstdint>

class Font
{
    public:
        // constructor
        Font();
        // gets the default font data
        const uint8_t* getDefaultFont() const;
        // size of the default font data
        static constexpr int SIZE = 80;

    private:
        // an array of the default font data
        uint8_t defaultFont[SIZE];
};

#endif