#pragma once

#include "main.h"

class Text
{
public:
    int x = 0, y = 0;
    int w = 0, h = 0;

    SDL_Texture* texture = NULL;
    TTF_Font* font = NULL;
    SDL_Rect rect;

    void create(int size, string path);
    void display(SDL_Renderer* renderer, SDL_Color color, string text);
    void render(SDL_Renderer* renderer, double x, double y, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void destroy();
};