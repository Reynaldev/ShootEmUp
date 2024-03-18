#pragma once

#include "main.h"

class GameObject
{
private:
    bool enabled = true;
public:
    float x = 0, y = 0;
    float w = 0, h = 0;

    SDL_Texture *texture;
    SDL_Rect rect;

    void init(SDL_Renderer *renderer, string texturePath);
    void render(SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    bool collideWith(SDL_Rect other);

    void setActive(bool isActive);
    bool isActive();
};