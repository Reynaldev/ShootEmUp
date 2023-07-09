#include "gameobject.h"

void GameObject::Init(SDL_Renderer* renderer, string texturePath)
{
    this->texture = IMG_LoadTexture(renderer, texturePath.c_str());
    if (!this->texture)
    {
        cout << texturePath << " texture could not be loaded!\nError: " << IMG_GetError() << endl;
        exit(1);
    }
}

void GameObject::Render(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_QueryTexture(this->texture, NULL, NULL, &rect.w, &rect.h);

    SDL_RenderCopy(renderer, this->texture, NULL, &rect);
}