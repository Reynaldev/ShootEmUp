#pragma once

#ifndef gameobject.h
#include "main.h"
#endif

class GameObject
{
public:
    int x = 0, y = 0;
    int w = 0, h = 0;

    SDL_Texture *texture;

    void Init(SDL_Renderer *renderer, string texturePath);
    void Render(SDL_Renderer *renderer, int x, int y, int w, int h);
};