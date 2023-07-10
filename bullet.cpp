#include "bullet.h"

void Bullet::move()
{
    this->y += this->speedY;
}

void Bullet::destroy()
{
    SDL_DestroyTexture(this->texture);
}