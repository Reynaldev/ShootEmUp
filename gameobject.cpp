#include "gameobject.h"

void GameObject::init(SDL_Renderer* renderer, string texturePath)
{
    this->texture = IMG_LoadTexture(renderer, texturePath.c_str());
    if (!this->texture)
    {
        cout << texturePath << " texture could not be loaded!\nError: " << IMG_GetError() << endl;
        exit(1);
    }
}

void GameObject::render(SDL_Renderer* renderer, float x, float y, float w, float h, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;
    SDL_QueryTexture(this->texture, NULL, NULL, &this->rect.w, &this->rect.h);

    SDL_RenderCopyEx(renderer, this->texture, clip, &this->rect, angle, center, flip);
}

bool GameObject::collideWith(SDL_Rect other)
{
    // This object
    double left = this->rect.x;
    double right = this->rect.x + this->rect.w;
    double top = this->rect.y;
    double bottom = this->rect.y + this->rect.h;

    // Other object
    double otherLeft = other.x;
    double otherRight = other.x + other.w;
    double otherTop = other.y;
    double otherBottom = other.y + other.h;

    // Check if other object is not collided
    if (left >= otherRight ||
        right <= otherLeft ||
        top >= otherBottom ||
        bottom <= otherTop)
    {
        return false;
    }

    return true;
}