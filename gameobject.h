#pragma once

#include "main.h"

class GameObject
{
public:
    double x = 0, y = 0;
    double w = 0, h = 0;

    SDL_Texture *texture;

    void Init(SDL_Renderer *renderer, string texturePath);
    void Render(SDL_Renderer *renderer, double x, double y, double w, double h);
};