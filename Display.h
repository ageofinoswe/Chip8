#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL3/SDL.h>

// 64x32 display for chip8
class Display
{
    public:
        // constructor
        Display();
        // display properties
        static constexpr int WIDTH = 64;
        static constexpr int HEIGHT = 32;
        // turn pixel on or off at (x,y) coordinate - (0,0) is top left of display
        void setPixel(const int coordX, const int coordY, bool isOn);
        // returns if a pixel is on at a specific coordinate
        bool isOn(const int coordX, const int coordY) const;
        // draws to the display what is stored in the displayBuffer
        void draw() const;
        // clear all pixels in the display
        void clearScreen();
        // destroys the SDL display window
        void destroyWindow() const;

    private:
        // SDL window and renderer
        SDL_Window *window;
        SDL_Renderer *renderer;
        // display buffer, 32 height x 64 width
        bool displayBuffer[HEIGHT][WIDTH];
        // initializes the SDL properties
        void initializeSDL();
        // iterates through each pixel in the display
        void iterateDisplay(const bool value);
};

#endif