#include "window.h"

void Window::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not be initialized!\nError: " << SDL_GetError() << endl;
        exit(1);
    }

    window = SDL_CreateWindow("Shoot 'em Up!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        cout << "Window could not be created!\nError: " << SDL_GetError() << endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        cout << "Renderer could not be created!\nError: " << SDL_GetError() << endl;
        exit(1);
    }

    int imgFlag = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlag) & imgFlag))
    {
        cout << "SDL_image could not be initialized!\nError: " << IMG_GetError() << endl;
        exit(1);
    }

    surface = SDL_GetWindowSurface(window);
}

void Window::render()
{
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);
}

void Window::quit()
{
    SDL_FreeSurface(this->surface);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    IMG_Quit();
    SDL_Quit();
}
