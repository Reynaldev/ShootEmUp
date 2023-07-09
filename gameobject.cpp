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

void GameObject::render(SDL_Renderer *renderer, double x, double y, double w, double h)
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

bool GameObject::collideWith(GameObject other)
{
    // This object
    double left = this->x;
    double right = this->x + this->w;
    double top = this->y;
    double bottom = this->y + this->h;

    // Other object
    double otherLeft = other.x;
    double otherRight = other.x + other.w;
    double otherTop = other.y;
    double otherBottom = other.y + other.h;

    if (otherLeft <= right ||
        otherRight >= left ||
        otherTop <= bottom ||
        otherBottom >= top)
    {
        return true;
    }

    return false;
}