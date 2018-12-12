#include "Window.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800

#include <iostream>
#include <exception>

Window::Window()
{
    window = SDL_CreateWindow("Ray Tracer - Job Pooling",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 
        SDL_WINDOW_RESIZABLE
    );

    if(!window)
    {
        std::cout << "SDL failed to create window" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer)
    {
        std::cout << "SDL failed to create renderer" << std::endl;
    }
}

void Window::drawPixel(int x, int y, glm::vec3 col)
{
    SDL_SetRenderDrawColor(renderer, col.x, col.y, col.z, 255);

    SDL_RenderDrawPoint(renderer, x, y);
}

void Window::display()
{
    SDL_RenderPresent(renderer);
}

void Window::cleanUp()
{
    SDL_DestroyWindow(window);
	SDL_Quit();
}