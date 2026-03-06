#include "Display.h"

// public
Display::Display()
    : displayBuffer{}
{
    initializeSDL();
};

void Display::setPixel(const int coordX, const int coordY, bool isOn)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    displayBuffer[coordY][coordX] = isOn;
}

bool Display::isOn(const int coordX, const int coordY) const
{
    return displayBuffer[coordY][coordX];
}

void Display::draw() const
{
    for(int row = 0 ; row < HEIGHT ; row++)
    {
        for(int col = 0 ; col < WIDTH ; col++)
        {
            if(displayBuffer[row][col])
            {
                SDL_RenderPoint(renderer, col, row);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void Display::clearScreen()
{
    iterateDisplay(false);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Display::destroyWindow() const
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// private
void Display::initializeSDL()
{
    const int WINDOW_SCALE = 20;
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    }
    
    if(!SDL_CreateWindowAndRenderer("CHIP-8", WIDTH * WINDOW_SCALE, HEIGHT * WINDOW_SCALE, SDL_WINDOW_OPENGL, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    }
    
    SDL_SetRenderLogicalPresentation(renderer, WIDTH, HEIGHT, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
}

void Display::iterateDisplay(const bool value)
{
    for(int row = 0 ; row < HEIGHT ; row++)
    {        
        for(int col = 0 ; col < WIDTH ; col++)
        {
            displayBuffer[row][col] = value;
        }
    }
}