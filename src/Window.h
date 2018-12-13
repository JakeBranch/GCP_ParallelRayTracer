#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glm/glm.hpp>

/**
*   Class to handle drawing of pixels
*/
class Window
{
    public:
    Window();

    void drawPixel(int x, int y, glm::vec3 col);
    void display();
    void cleanUp();

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif